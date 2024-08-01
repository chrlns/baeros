//#define NULL 0
#include <stddef.h>

#define MBOX_CHANNEL_POWER       0
#define MBOX_CHANNEL_FRAMEBUFFER 1
#define MBOX_CHANNEL_LEDS        4

#define MAILBOX_BASE    0x7E00B880 // 0x2000B880
#define MAILBOX_READ    (MAILBOX_BASE + 0x00)
#define MAILBOX_STATUS  (MAILBOX_BASE + 0x18)
#define MAILBOX_WRITE   (MAILBOX_BASE + 0x20)

#define MAILBOX_FULL (1 << 31)
#define MAILBOX_EMPTY (1 << 30)

// This define is valid if L2 cache is enabled, otherwise 0xC0000000
#define MEM_NONCACHE_OFFSET 0x40000000

// The lower 4 bits of data are discarded
#define	MBOX_MSG(chan, data)    (((data) & ~0xf) | ((chan) & 0xf))
#define	MBOX_CHAN(msg)          ((msg) & 0xf)

struct __attribute__((packed, aligned(16))) fb_info {
    unsigned int physicalWidth;   // #0 Physical Width
    unsigned int physicalHeight;  // #4 Physical Height
    unsigned int virtualWidth;    // #8 Virtual Width
    unsigned int virtualHeight;   // #12 Virtual Height
    unsigned int pitch;           // #16 GPU - Pitch
    unsigned int bitDepth;        // #20 Bit Depth
    unsigned int x;               // #24 X offset
    unsigned int y;               // #28 Y offset
    unsigned char* address;       // #32 Address of the framebuffer
    unsigned int size;            // #36 Size of the framebuffer
};

extern void cpu_data_memory_barrier(void);
