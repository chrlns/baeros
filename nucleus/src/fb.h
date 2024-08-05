#include <stdbool.h>

#define FRAMEBUFFER_WIDTH 640
#define FRAMEBUFFER_HEIGHT 480

#define CHAR_PIXEL_WIDTH 8
#define CHAR_PIXEL_HEIGHT 16

#define min(a,b) ((a > b) ? (b) : (a))

int fb_init(void);
void screen_clear(void);
void screen_random(void);

void screen_draw_char(char c, int x, int y);
bool screen_draw_str(char* str);