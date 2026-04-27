# ===========================================================
# Name:    CS483
# Section: CS 483 — Operating Systems
# Project: Keyboard Logger Lab (PEX)
# Purpose: Build the hello_printk kernel module against the
#          running kernel's header tree.
#
#          Usage:
#              make           # build hello_printk.ko
#              make clean     # remove build artifacts
#
#          Prerequisites:
#              sudo apt install build-essential \
#                               linux-headers-$(uname -r)
# ===========================================================

# Module object the kernel build system should produce.
# The kernel Kbuild system converts hello_printk.o -> hello_printk.ko
obj-m := hello_printk.o

# Location of the running kernel's build tree. Resolved once at
# make time so this Makefile follows the student through kernel
# upgrades without edits.
KDIR := /lib/modules/$(shell uname -r)/build

# Directory holding our source — where Kbuild should place
# intermediate and final objects.
PWD := $(shell pwd)

# Default target: delegate to the kernel build system.
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Remove every artifact the kernel build system produced.
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean