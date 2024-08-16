BærOS Documentation                                                  {#mainpage}
==================

[TOC]

BærOS in a nutshell                                        {#baeros-in-a-nutshell}
==================
BærOS is an open-source Unix-like operating system project, designed to be a playground for 
computer science students (and teachers!). 
Target platform for BærOS are cheap single board computer (SBC) like the
[Raspberry Pi](https://www.raspberrypi.com/).

Currently, BærOS is in a very early stage, not much more than a bootloader and a Hello World 
kernel (called `nucleus`).

Contribute to BærOS                                        {#contribute-to-baeros}
==================
BærOS is developed under the open source license MIT and welcomes any contributions especially from students:
 - Download and contribute your code on
   [GitHub](https://github.com/chrlns/baeros).
 - Mailinglist/Forums will be eventually be created...

The quickest start                                        {#the-quickest-start}
==================
You can run BærOS currently on Raspberry Pi Model 1 only, more devices will be added from time to time. 
You can compile and run it using the following terminal statements:

~~~~~~~{.sh}
# Assumption: git and gcc-arm-none-eabi is installed
git clone https://github.com/chrlns/baeros.git
cd baeros/nucleus                              
make TARGET=armv6

# Format a SD card with FAT32
# Copy contents of baeros/misc/sd to SD card
mv nucleus.img /path/to/sd/BAEROS.IMG

# Put SD card in your pi and boot it
~~~~~~~

Structure                                                          {#structure}
=========

Here follows a introductory description of BaerOS structure as soon it has one.



Further information                                      {#further-information}
===================

Follow the Mastodon tag #baeros for news.

