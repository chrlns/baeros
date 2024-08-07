#include <stdbool.h>

#define COLOR_BLÅBÆR_R 29
#define COLOR_BLÅBÆR_G 45
#define COLOR_BLÅBÆR_B 68

#define FRAMEBUFFER_WIDTH 640
#define FRAMEBUFFER_HEIGHT 480

#define CHAR_PIXEL_WIDTH 8
#define CHAR_PIXEL_HEIGHT 16

#define min(a,b) ((a < b) ? (a) : (b))

int fb_init(void);
volatile void* fb_address();
void screen_clear(void);
void screen_random(void);

void screen_draw_char(char c, int x, int y);
bool screen_draw_str(const char* str);