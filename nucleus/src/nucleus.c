#include <stdbool.h>

#include "fb.h"
#include "nucleus.h"

__attribute__((section(".data")))
volatile int ErrCode = 0;

char* kernel_log[KERNEL_LOG_SIZE] = { "BaerOS" };
int log_idx = 0;

bool fb_initialized = false;

/*
 * Clears the screen and redraws the current kernel log.
 */
void update_screen(void) {
    screen_clear();

    for (int i = 0; i < CONSOLE_ROWS; i++) {
        int idx = (log_idx - (CONSOLE_ROWS - i)); 
        if (idx < 0) {
            idx += KERNEL_LOG_SIZE; // wrap around
        }
        char* msg = kernel_log[idx];
        screen_draw_str(msg);
    }
}

void print(const char* msg) {
    kernel_log[log_idx] = (char*)msg;
    log_idx = (log_idx + 1) % KERNEL_LOG_SIZE;
    if (fb_initialized) {
        update_screen();
    }
}

void nmain(void) {
    print("BaerOS\n\n");
    print(__DATE__);
    print("\n");
    print("Created by Christian Lins. Source is MIT licensed.\n");

    // Virtual addresses in kernel mode will range between 0xC0000000 and 0xEFFFFFFF
    
    // Virtual addresses in user mode (i.e. seen by processes running) will range
    // between 0x00000000 and 0xBFFFFFFF
    print("Initializing framebuffer...");
    if (screen_init() != 0) {
        // Could not init framebuffer
        ErrCode = 1;
    } else {
        fb_initialized = true;
        screen_clear();
    }
    print("OK\n");

    if (ErrCode != 0) {
        return;
    }

    print("Entering endless loop. No init task.");

    for (;;) {
        //screen_random();
        /*for (volatile unsigned int i = 0; i < (1 << 31); i++) {

        }*/
    }
}
