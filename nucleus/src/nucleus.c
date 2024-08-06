#include <stdbool.h>

#include "fb.h"
#include "nucleus.h"
#include "mem.h"
#include "string.h"

__attribute__((section(".data")))
volatile int ErrCode = 0;

char* kernel_log[KERNEL_LOG_SIZE];
int log_idx = 0;

bool fb_initialized = false;

static void log_init() {
    for (int i = 0; i < KERNEL_LOG_SIZE; i++) {
        kernel_log[i] = NULL;
    }
}

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
    // Copy message
   /* size_t len = strlen(msg) + 1;
    char* msg_cpy = nuc_malloc(len, 0);
    strncpy(msg_cpy, msg, len);

    // Free old message if existing
    if (kernel_log[log_idx] != NULL) {
        nuc_free(kernel_log[log_idx]);
    }*/

    kernel_log[log_idx] = msg;
    log_idx = (log_idx + 1) % KERNEL_LOG_SIZE;

    if (fb_initialized) {
        update_screen();
    }
}

/*
 * Main entry point of the kernel.
 */
void nuc_main(void) {
    log_init();
    mem_init();

    print("BaerOS\nBuild ");
    print(__DATE__);
    print("\n\n");

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

    print("Entering endless loop. No init task.\n");

    for (;;) {

    }
}
