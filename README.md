# BærOS
BaerOS (or in its unicode spelling BærOS) aims to be a simple operating system
for the Raspberry PI SBC. Its main purpose is to support the education of 
computer science students.

## Prerequisites

For cross-compiling:
  $ apt install gcc-arm-none-eabi gdb-multiarch

## Compile kernel
  nucleus $ make

Copy baeros.img together with the contents of misc/sd/ on a FAT32 formatted
SD/SDHC card and use it to boot your Raspberry Pi (currently only Model 1B+ known
to work). 

## Debug Kernel

Note: currently, kernel debugging is not possible as BaerOS is not compatible
with QEMU yet (raspi support in QEMU seems incomplete).

  * Start QEMU with -s -S flags (qemu.sh)
  * Start gdb with arm-none-eabi-gdb
        * target remote localhost:1234
        * file kernel/kernel.img
        * break kmain
        * continue

## Links
Useful links for operating system development especially for the Raspi.
  * https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/index.html
  * https://www.glennklockwood.com/embedded/bmc2835-gpio.html
  * https://elinux.org/BCM2835_datasheet_errata
  * https://github.com/raspberrypi/firmware/wiki/Mailboxes
  * https://wiki.osdev.org/Raspberry_Pi_Bare_Bones
  * https://elinux.org/RPi_Framebuffer
