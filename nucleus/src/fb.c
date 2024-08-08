#include <stdint.h>

#include "chars_pixels.h"
#include "mbox.h"
#include "nucleus.h"
#include "fb.h"

extern volatile int ErrCode;

struct __attribute__((packed, aligned(16))) fb_info {
    unsigned int physicalWidth;   // #0 Physical Width
    unsigned int physicalHeight;  // #4 Physical Height
    unsigned int virtualWidth;    // #8 Virtual Width
    unsigned int virtualHeight;   // #12 Virtual Height
    volatile unsigned int pitch;  // #16 GPU - Pitch, offset between rows
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
    .bitDepth = FRAMEBUFFER_DEPTH * 8,
    .x = 0,
    .y = 0,
    .address = NULL,
    .size = 0  
};

static unsigned char rnd = 17;
static int cursor_x = 1;
static int cursor_y = 1;

/*
 *  Initializes the framebuffer. That means that we setup the mailbox system
 *  between the video processor and the CPU.
 */
int fb_init(void) {
    
    // Write the FrameBufferInfo address to mailbox 1
    mailbox_write((unsigned int)&FrameBufferInfo + MEM_NONCACHE_OFFSET, MBOX_CHANNEL_FRAMEBUFFER);
    
    // Read the answer (status code)
    return mailbox_read(MBOX_CHANNEL_FRAMEBUFFER);
}

volatile void* fb_address() {
    return FrameBufferInfo.address;
}

static void cursor_reset() {
    cursor_x = 1;
    cursor_y = 1;
}

/* Clears the framebuffer with the background color. */
void screen_clear(void) {
    // Do nothing if framebuffer is not initialized (yet)
    if (FrameBufferInfo.address == NULL) {
        return;
    }
    
    // We use the framebuffer address as int pointer
    volatile uint32_t* buf = (uint32_t*)FrameBufferInfo.address;

    // This a 4-byte-word containing one pixel color
    const uint32_t pattern =  
        (COLOR_BLÅBÆR_R << 0) | 
        (COLOR_BLÅBÆR_G << 8) | 
        (COLOR_BLÅBÆR_B << 16);

    // Fill the complete framebuffer area with this pixel pattern.
    // Should be faster than drawing single colors because we use
    // 4-byte-aligned memory access.
    for (int i = 0; i < FRAMEBUFFER_HEIGHT * FRAMEBUFFER_WIDTH; i++) {
        *buf++ = pattern;
    }

    cursor_reset();

    cpu_data_memory_barrier();
}

void screen_random(void) {
    cpu_data_memory_barrier();
    volatile unsigned char* buf = FrameBufferInfo.address;
    

    for (int y = 0; y < FrameBufferInfo.physicalHeight; y++) {
        for (int x = 0; x < FrameBufferInfo.physicalWidth; x++) {
            int offset = (y * FrameBufferInfo.physicalWidth + x) * FRAMEBUFFER_DEPTH;
            buf[offset] = 0x0F + rnd;     // R
            buf[offset + 1] = 0x22 ^ rnd; // G
            buf[offset + 2] = 0xAA - rnd; // B
        }
    }
    rnd++;
    cpu_data_memory_barrier();    
}



/*
 * Draws the given ASCII-similar character on the framebuffer at the given
 * pixel position.
 */
void screen_draw_char(char c, int x, int y) {
    if (c == 0 || c == '\n')
        return;

    // The right place on the screen
    int fb_offset_base = (y * FrameBufferInfo.physicalWidth + x) * FRAMEBUFFER_DEPTH;

    // The offset within the char bitmap pixel array
    int ch_offset = c * CHAR_PIXEL_HEIGHT * CHAR_PIXEL_WIDTH;

    for (int h = 0; h < CHAR_PIXEL_HEIGHT; h++) {
        // Scroll to next line
        int fb_offset = fb_offset_base + h * FrameBufferInfo.physicalWidth * FRAMEBUFFER_DEPTH;

        for (int w = 0; w < CHAR_PIXEL_WIDTH; w++) {
            int offset = (h * CHAR_PIXEL_WIDTH + w);

            char pixel = 0xFF - chars_pixels[ch_offset + offset];
            if (pixel <= 0x80) {
                continue; // if transparent
            }

            // Set all three color channels to white
            FrameBufferInfo.address[fb_offset + w * FRAMEBUFFER_DEPTH + 0] = pixel;
            FrameBufferInfo.address[fb_offset + w * FRAMEBUFFER_DEPTH + 1] = pixel;
            FrameBufferInfo.address[fb_offset + w * FRAMEBUFFER_DEPTH + 2] = pixel;
            //cpu_data_memory_barrier(); 
        }
    }
}

static void cursor_newline() {
    cursor_x = 1;
    cursor_y = min(cursor_y + 1, (FRAMEBUFFER_HEIGHT / CHAR_PIXEL_HEIGHT) - 2);
}

/*
 * Draws the given string character by character onto the framebuffer.
 * The position is determined by current cursor position.
 * Returns true if an row overflow occurred, meaning the cursor is at the 
 * bottom.
 */
bool screen_draw_str(const char* str) {
    //cpu_data_memory_barrier(); // Barrier to make sure we can read FrameBufferInfo.address?
    if (str == NULL || FrameBufferInfo.address == NULL) {
        return false;
    }

    // Determine screen positions from cursor position and add one character 
    // padding if cursor position is left or top.
    int ox = cursor_x * CHAR_PIXEL_WIDTH;
    int oy = cursor_y * CHAR_PIXEL_HEIGHT;

    while (*str != '\0') {
        if (*str == '\n') {
            // If we find a newline char we skip drawing and move to next line
            cursor_newline();
            ox = CHAR_PIXEL_WIDTH;
            oy += CHAR_PIXEL_HEIGHT;
        } else {
            screen_draw_char(*str, ox, oy);
            cursor_x++;

            ox += CHAR_PIXEL_WIDTH;
            if (ox >= FrameBufferInfo.physicalWidth - 2 * CHAR_PIXEL_WIDTH) {
                cursor_newline();
                ox = CHAR_PIXEL_WIDTH;
                oy += CHAR_PIXEL_HEIGHT;
            }
        }

        str++; // go to next character
    }

    return cursor_y == (FRAMEBUFFER_HEIGHT / CHAR_PIXEL_HEIGHT) - 2;
}