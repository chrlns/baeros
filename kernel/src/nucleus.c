#include <nucleus.h>

#define	MBOX_MSG(chan, data)    (((data) & ~0xf) | ((chan) & 0xf))
#define	MBOX_CHAN(msg)          ((msg) & 0xf)
#define	MBOX_DATA(msg)          ((msg) & ~0xf)

struct fb_info FrameBufferInfo = {
    .physicalWidth = 1024,
    .physicalHeight = 768,
    .virtualWidth = 1024,
    .virtualHeight = 768,
    .bitDepth = 16  
};

int ErrCode = 0;

void mailbox_write(unsigned int message, unsigned int channel) {
    unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    unsigned int* write = (unsigned int*)MAILBOX_WRITE;
    
    // Wait until status field has 0 in the top bit
    while((*status & 0x80000000) != 0);
    
    // Write channel (into lower 4bit) and message (into upper 28bit)
    *write = MBOX_MSG(channel, message);
}

unsigned int mailbox_read(unsigned int channel) {
    unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    unsigned int* read = (unsigned int*)MAILBOX_READ;
    unsigned int data;
    
    do {
        // Wait until status field has 0 in the 30th bit
        while((*status & 0x40000000) != 0);
    
        // Read the message + mailbox
        data = *read;
        
    } while(MBOX_CHAN(data) != channel); // Check if the message is for the correct 
                                      // channel, if not try again
    
    return MBOX_DATA(data); // The top 28 bit remain as message
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

void kmain(void) {

    // Virtual addresses in kernel mode will range between 0xC0000000 and 0xEFFFFFFF
    
    // Virtual addresses in user mode (i.e. seen by processes running) will range
    // between 0x00000000 and 0xBFFFFFFF

    if (screen_init() != 0) {
        // Could not init framebuffer
        ErrCode = -1;
    }

    if (ErrCode != 0) {
        return;
    }

    for (;;);
}
