.section .init
.globl _start
_start:     # define entrypoint to avoid warning
# We start in supervisor mode (svc32)

# Disable interrupts
#cpsid i

# Initialize stack
ldr sp, =stack_top

# Call nucleus (kernel) main
b nmain

stack_top:
    .space 1024
