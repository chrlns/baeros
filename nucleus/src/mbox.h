
#define MBOX_CHANNEL_POWER       0
#define MBOX_CHANNEL_FRAMEBUFFER 1
#define MBOX_CHANNEL_LEDS        4

void mailbox_write(unsigned int message, unsigned int channel);
unsigned int mailbox_read(unsigned int channel);