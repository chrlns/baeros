# BærOS
BaerOS (or in its unicode spelling BærOS) aims to be a simple operating system
for the Raspberry PI SBC. Its main purpose is to support the education of 
computer science students.

## Prerequisites

For cross-compiling on Debian-based Linux-Systems:

    $ apt install gcc-arm-none-eabi gdb-multiarch

## Compile kernel (for target ARMv6 like Raspberry Pi 1)
    $ cd nucleus
    $ make TARGET=armv6

Copy baeros.img together with the contents of misc/sd/ on a FAT32 formatted
SD/SDHC card and use it to boot your Raspberry Pi (currently only Model 1B+ known
to work). 

## Debug Kernel

Note: currently, kernel debugging is not possible as BaerOS is not compatible
with QEMU yet (raspi support in QEMU seems incomplete).

  * Start QEMU with -s -S flags (qemu.sh)
  * Start gdb with arm-none-eabi-gdb

Within gdb:

    target remote localhost:1234
    file nucleus/nucleus.img
    break kmain
    continue

## Links
Useful links for operating system development especially for the Raspi.
  * https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/index.html
  * https://www.glennklockwood.com/embedded/bmc2835-gpio.html
  * https://elinux.org/BCM2835_datasheet_errata
  * https://github.com/raspberrypi/firmware/wiki/Mailboxes
  * https://github.com/Zeke-OS/zeke/blob/master/kern/hal/bcm2835/bcm2835_mailbox.c
  * https://github.com/werner-matthias/aihPOS/blob/master/kernel/src/debug/framebuffer.rs
  * https://wiki.osdev.org/Raspberry_Pi_Bare_Bones
  * https://elinux.org/RPi_Framebuffer
  * https://github.com/bztsrc/raspi3-tutorial/tree/master
  * https://www.raspberrypi.com/documentation/computers/config_txt.html
  * https://stackoverflow.com/questions/26564178/reading-from-uart-rxd-of-the-raspberry-pi-in-assembly
  * https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html
  * http://www.mathematik.uni-oldenburg.de/personen/tdm/VortragsAbstracts/Schmale/SRT-Division-korrigiert.pdf
  * https://azeria-labs.com/writing-arm-assembly-part-1/
  * https://www.valvers.com/open-software/raspberry-pi/bare-metal-programming-in-c-card/
