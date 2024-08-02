#include "nucleus.h"

#define MAILBOX_BASE    0x2000B880
#define MAILBOX_READ    (MAILBOX_BASE + 0x00)
#define MAILBOX_STATUS  (MAILBOX_BASE + 0x18)
#define MAILBOX_WRITE   (MAILBOX_BASE + 0x20)

#define MAILBOX_FULL (1 << 31)
#define MAILBOX_EMPTY (1 << 30)

// The lower 4 bits of data are discarded
#define	MBOX_MSG(chan, data)    (((data) & ~0xf) | ((chan) & 0xf))
#define	MBOX_CHAN(msg)          ((msg) & 0xf)

void mailbox_write(unsigned int message, unsigned int channel) {
    volatile unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    volatile unsigned int* write = (unsigned int*)MAILBOX_WRITE;
    
    // Wait until status field has 0 in the top bit
    while((*status & MAILBOX_FULL) != 0) {
        cpu_data_memory_barrier();
    }
    
    cpu_data_memory_barrier();
    
    // Write channel (into lower 4bit) and message (into upper 28bit)
    *write = MBOX_MSG(channel, message);
}

unsigned int mailbox_read(unsigned int channel) {
    volatile unsigned int* status = (unsigned int*)MAILBOX_STATUS;
    volatile unsigned int* read = (unsigned int*)MAILBOX_READ;
    unsigned int data;
    
    do {
        // Wait until status field has 0 in the 30th bit
        while((*status & MAILBOX_EMPTY) != 0) {
            cpu_data_memory_barrier();
        }
    
        // Read the message + mailbox
        data = *read;
        cpu_data_memory_barrier();
    } while(MBOX_CHAN(data) != channel); // Check if the message is for the correct 
                                         // channel, if not try again
    
    return data >> 4; // The top 28 bit remain as message
}