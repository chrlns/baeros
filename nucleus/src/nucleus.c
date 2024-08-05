#include <stdbool.h>

#include "fb.h"
#include "nucleus.h"
#include "mem.h"

__attribute__((section(".data")))
volatile int ErrCode = 0;

char* kernel_log[KERNEL_LOG_SIZE] = { NULL };
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

/*
 * Main entry point of the kernel.
 */
void nuc_main(void) {
    print("BaerOS\n\n");
    print(__DATE__);
    print("\n");
    print("Created by Christian Lins. Source is MIT licensed.\n");

    // Sometimes the first framebuffer initialization fails, so we'll try
    // several times before giving up. Perhaps a timing issue?
    for (int i = 1; i <= 3; i++) {
        print("Initializing framebuffer...");
        if (fb_init() != 0) {
            // Could not init framebuffer
            ErrCode = 1;
            print("Failed!\n");
        } else {
            fb_initialized = true;
            screen_clear();
            print("OK\n");
            break;
        }
    }

    if (ErrCode != 0) {
        return;
    }
    
    print("Initializing small heap...");
    mem_init();
    print("OK\n");

    void* buf = nuc_malloc(24, 0);
    if (buf == NULL) {
        print("nuc_malloc failed\n");
    } else {
        nuc_free(buf);
        print("buffer freed\n");
    }

    print("Entering endless loop. No init task.");

    for (;;) {

    }
}
