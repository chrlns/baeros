#include "mbox.h"
#include "nucleus.h"

extern volatile int ErrCode;

struct __attribute__((packed, aligned(16))) fb_info {
    unsigned int physicalWidth;   // #0 Physical Width
    unsigned int physicalHeight;  // #4 Physical Height
    unsigned int virtualWidth;    // #8 Virtual Width
    unsigned int virtualHeight;   // #12 Virtual Height
    volatile unsigned int pitch;           // #16 GPU - Pitch
    unsigned int bitDepth;        // #20 Bit Depth
    unsigned int x;               // #24 X offset
    unsigned int y;               // #28 Y offset
    volatile unsigned char* address;       // #32 Address of the framebuffer
    volatile unsigned int size;            // #36 Size of the framebuffer
};

__attribute__((aligned(16), section(".data")))
static volatile struct fb_info FrameBufferInfo = {
    .physicalWidth = 640,
    .physicalHeight = 480,
    .virtualWidth = 640,
    .virtualHeight = 480,
    .pitch = 0,
    .bitDepth = 24,
    .x = 0,
    .y = 0,
    .address = NULL,
    .size = 0  
};

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
    cpu_data_memory_barrier();
    volatile unsigned char* buf = FrameBufferInfo.address;
    
    if (buf == NULL) {
        ErrCode = 2;
        return;
    }
    
    /*if (FrameBufferInfo.size == 0) {
        ErrCode = 3;
        return;
    }*/
    
    
    for (int y = 0; y < FrameBufferInfo.physicalHeight; y++) {
        for (int x = 0; x < FrameBufferInfo.physicalWidth; x++) {
            int offset = (y * FrameBufferInfo.physicalWidth + x) * 3;
            buf[offset] = 0x0F;     // R
            buf[offset + 1] = 0x22; // G
            buf[offset + 2] = 0xAA; // B
        }
    }
    cpu_data_memory_barrier();
}