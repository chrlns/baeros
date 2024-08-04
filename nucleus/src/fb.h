#define FRAMEBUFFER_WIDTH 640
#define FRAMEBUFFER_HEIGHT 480

#define CHAR_PIXEL_WIDTH 8
#define CHAR_PIXEL_HEIGHT 16

int screen_init(void);
void screen_clear(void);
void screen_random(void);

void screen_draw_char(char c, int x, int y);
int screen_draw_str(char* str, int x, int y);