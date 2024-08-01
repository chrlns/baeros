# baeros
BærOS

## Prerequisites

   $ apt install gcc-arm-none-eabi gdb-multiarch

## Debug Kernel

  * Start QEMU with -s -S flags (qemu.sh)
  * Start gdb with arm-none-eabi-gdb
        * target remote localhost:1234
        * file kernel/kernel.img
        * break kmain
        * continue

## Links
  * https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/index.html
  * https://www.glennklockwood.com/embedded/bmc2835-gpio.html
  * https://elinux.org/BCM2835_datasheet_errata
  * https://github.com/raspberrypi/firmware/wiki/Mailboxes
  * https://wiki.osdev.org/Raspberry_Pi_Bare_Bones
  * https://elinux.org/RPi_Framebuffer
