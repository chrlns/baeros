#include <nucleus.h>

#define MAILBOX_READ 0x2000B880
#define MAILBOX_STATUS 0x2000B898
#define MAILBOX_WRITE 0x2000B8A0

#define MEM_NONCACHE_OFFSET 0x40000000

struct fb_info FrameBufferInfo = {
    .physicalWidth = 1024,
    .physicalHeight = 768,
    .virtualWidth = 1024,
    .virtualHeight = 768,
    .bitDepth = 16  
};

int ErrCode = 0;

void mailbox_write(unsigned int message, unsigned int mailbox) {
    unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    unsigned int* write = (unsigned int*)MAILBOX_WRITE;
    
    // Wait until status field has 0 in the top bit
    while((*status & 0x80000000) != 0);
    
    // Write mailbox (into lower 4bit) and message (into upper 28bit)
    *write = (mailbox >> 28) | (message << 4);
}

unsigned int mailbox_read(unsigned int mailbox) {
    unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    unsigned int* read = (unsigned int*)MAILBOX_READ;
    unsigned int data;
    
    do {
        // Wait until status field has 0 in the 30th bit
        while((*status & 0x40000000) != 0);
    
        // Read the message + mailbox
        data = *read;
        
    } while((data | 0xF) != mailbox); // Check if the message is for the correct 
                                      // mailbox, if not try again
    
    return data >> 4; // The top 28 bit remain as message
}

/*
 *  Initializes the screen. That means that we setup the mailbox system between
 *  the video processor and the CPU.
 */
int screen_init(void) {
    
    // Write the FrameBufferInfo address to mailbox 1
    mailbox_write((unsigned int)&FrameBufferInfo + MEM_NONCACHE_OFFSET, 1);
    
    return mailbox_read(1);
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
