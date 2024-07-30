qemu-system-arm -machine raspi1ap \
                -kernel kernel/kernel.img \
                -m 512 \
                -serial stdio \
                -d in_asm,cpu_reset
