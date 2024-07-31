#include <nucleus.h>

static volatile struct fb_info FrameBufferInfo = {
    .physicalWidth = 800,
    .physicalHeight = 600,
    .virtualWidth = 800,
    .virtualHeight = 600,
    .pitch = 0,
    .bitDepth = 24,
    .address = NULL,
    .size = 0  
};

static int ErrCode = 0;

void mailbox_write(unsigned int message, unsigned int channel) {
    volatile unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    volatile unsigned int* write = (unsigned int*)MAILBOX_WRITE;
    
    // Wait until status field has 0 in the top bit
    while((*status & MAILBOX_FULL) != 0) {
        cpu_data_memory_barrier();
    }
    
    cpu_data_memory_barrier();
    
    // Write channel (into lower 4bit) and message (into upper 28bit)
    *write = MBOX_MSG(channel, message);
}

unsigned int mailbox_read(unsigned int channel) {
    volatile unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    volatile unsigned int* read = (unsigned int*)MAILBOX_READ;
    unsigned int data;
    
    do {
        // Wait until status field has 0 in the 30th bit
        while((*status & MAILBOX_EMPTY) != 0) {
            cpu_data_memory_barrier();
        }
    
        // Read the message + mailbox
        data = *read;
        cpu_data_memory_barrier();
    } while(MBOX_CHAN(data) != channel); // Check if the message is for the correct 
                                         // channel, if not try again
    
    return data >> 4; // The top 28 bit remain as message
}

/*
 *  Initializes the screen. That means that we setup the mailbox system between
 *  the video processor and the CPU.
 */
int screen_init(void) {
    
    // Write the FrameBufferInfo address to mailbox 1
    mailbox_write((unsigned int)&FrameBufferInfo + MEM_NONCACHE_OFFSET, MBOX_CHANNEL_FRAMEBUFFER);
    
    return mailbox_read(MBOX_CHANNEL_FRAMEBUFFER);
}

void screen_clear(void) {
    volatile unsigned char* buf = FrameBufferInfo.address;
    if (buf == NULL) {
        ErrCode = 2;
        return;
    }
    
    if (FrameBufferInfo.size == 0) {
        ErrCode = 3;
        return;
    }
    
    for (int y = 0; y < FrameBufferInfo.physicalHeight; y++) {
        for (int x = 0; x < FrameBufferInfo.physicalWidth; x++) {
            int offset = (y * FrameBufferInfo.physicalWidth + x) * 3;
            buf[offset] = 0xFF;     // R
            buf[offset + 1] = 0x33; // G
            buf[offset + 2] = 0xFF; // B
        }
    }
}

void kmain(void) {

    // Virtual addresses in kernel mode will range between 0xC0000000 and 0xEFFFFFFF
    
    // Virtual addresses in user mode (i.e. seen by processes running) will range
    // between 0x00000000 and 0xBFFFFFFF

    if (screen_init() != 0) {
        // Could not init framebuffer
        ErrCode = 1;
    } else {
        screen_clear();
    }

    if (ErrCode != 0) {
        return;
    }

    for (;;);
}
