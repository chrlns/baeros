#include "fb.h"
#include "nucleus.h"

__attribute__((section(".data")))
volatile int ErrCode = 0;

void print(const char* msg) {
    screen_draw_str((char*)msg, 0, 0);
}

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

    print("BaerOS\n");

    if (ErrCode != 0) {
        return;
    }

    for (;;) {
        //screen_random();
        /*for (volatile unsigned int i = 0; i < (1 << 31); i++) {

        }*/
    }
}
