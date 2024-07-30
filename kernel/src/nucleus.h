#define MBOX_CHANNEL_POWER       0
#define MBOX_CHANNEL_FRAMEBUFFER 1
#define MBOX_CHANNEL_LEDS        4

#define MAILBOX_READ 0x2000B880
#define MAILBOX_STATUS 0x2000B898
#define MAILBOX_WRITE 0x2000B8A0

#define MEM_NONCACHE_OFFSET 0x40000000

struct __attribute__((aligned(4))) fb_info {
    unsigned int physicalWidth;   // #0 Physical Width
    unsigned int physicalHeight;  // #4 Physical Height
    unsigned int virtualWidth;    // #8 Virtual Width
    unsigned int virtualHeight;   // #12 Virtual Height
    unsigned int pitch;           // #16 GPU - Pitch
    unsigned int bitDepth;        // #20 Bit Depth
    unsigned int x;               // #24 X
    unsigned int y;               // #28 Y
    unsigned int gpuPointer;      // #32 GPU - Pointer
    unsigned int gpuSize;         // #36 GPU - Size
};

