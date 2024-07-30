.section .init
.globl _start
_start:     # define entrypoint to avoid warning
# We start in supervisor mode (svc32)

# Enable LED to see at least something is working
ldr r0,=0x20200000
mov r1,#1
lsl r1,#18
str r1,[r0,#4]
mov r1,#1
lsl r1,#16
str r1,[r0,#40]

# Disable interrupts
cpsid i

# Initialize stack
ldr sp, =stack_top

# Call kernel main
b kmain

stack_top:
    .space 1024
