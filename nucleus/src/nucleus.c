#include "fb.h"
#include "nucleus.h"

__attribute__((section(".data")))
volatile int ErrCode = 0;

void nmain(void) {
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

    for (;;) {
        ErrCode = 8;
    }
}
