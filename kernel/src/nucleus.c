#define MAILBOX_READ 0x2000B880
#define MAILBOX_STATUS 0x2000B898
#define MAILBOX_WRITE 0x2000B8A0

extern int mailbox_base(void);


void mailbox_write(unsigned int mailbox, unsigned int message) {
    unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    unsigned int* write = (unsigned int*)MAILBOX_WRITE;
    
    // Wait until status field has 0 in the top bit
    while((*status & 0x80000000) != 0);
    
    // Write mailbox (into lower 4bit) and message (into upper 28bit)
    *write = (mailbox >> 28) | (message << 4);
}

unsigned int mailbox_read(unsigned int mailbox) {
    unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    unsigned int* read = (unsigned int*)MAILBOX_READ;
    
    // Wait until status field has 0 in the 30th bit
    while((*status & 0x40000000) != 0);
    
    // Read the message
    unsigned int data = *read;
    
    // Check if the message is for the correct mailbox, if not try again
    unsigned int mailbox_actual = (data >> 28);
    if (mailbox_actual != mailbox) {
    
    }
    
    return message;
}

/*
 *  Initializes the screen. That means that we setup the mailbox system between
 *  the video processor and the CPU.
 */
int screen_init(void) {
    int base = mailbox_base();
    return 0;
}

void kmain(void) {
    screen_init();

    for (;;);
}
