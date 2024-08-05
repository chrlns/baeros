qemu-system-arm -machine raspi1ap \
                -kernel nucleus/baeros.img \
                -m 512 \
                -serial stdio \
                -d in_asm,cpu_reset
