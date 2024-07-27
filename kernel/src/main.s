.section .init
.globl _start
_start:     # define entrypoint to avoid warning

# Enable LED to see at least something is working
ldr r0,=0x20200000
mov r1,#1
lsl r1,#18
str r1,[r0,#4]
mov r1,#1
lsl r1,#16
str r1,[r0,#40]

# Call kernel main
b kmain
