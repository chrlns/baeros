.section .init
.globl _start
_start:     # define entrypoint to avoid warning
# We start in supervisor mode (svc32)

# Disable interrupts
#cpsid i

# Initialize stack
ldr sp, =stack_top

# Set SCTLR.U = 1 to disable legacy ARMv5 unaligned-word-behaviour
# See https://gitlab.com/qemu-project/qemu/-/issues/1878
mrc	p15, 0, r0, c1, c0, 0   @ read SCTLR
bic	r0, r0, #2              @ A (no unaligned access fault)
orr	r0, #1 << 22            @ U (v6 unaligned access model)
mcr	p15, 0, r0, c1, c0, 0   @ write SCTLR

# Call nucleus (kernel) main
b nuc_main

# Some space for the stack
.section data
stack_top:
    .space 1024

# Some space for a simple and very small heap
.section data
.globl small_heap
small_heap:
    .space 4096
