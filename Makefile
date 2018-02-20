# Nokos
# Copyright (c) Jeremiah Z. Griffin <nokurn@gmail.com>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE NEGLIGENCE OR OTHER TORTIOUS ACTION,
# ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
# SOFTWARE.

TOOLCHAIN := i686-elf-
CC := $(TOOLCHAIN)gcc
QEMU := qemu-system-i386

CFLAGS += -std=gnu11 -Wall -Wextra
ifeq ($(BUILD),release)
    CFLAGS += -O3 -DNDEBUG
else
    CFLAGS += -g -DNDEBUG
endif

.PHONY: all clean distclean
all: all-kernel
clean: clean-kernel
distclean: distclean-kernel

kernel.OUTPUT := kernel/kernel.elf
kernel.LINKER := kernel/kernel.ld
kernel.SOURCE := \
    kernel/main.c \
    kernel/start.S
kernel.OBJECT := $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(kernel.SOURCE)))
kernel.DEPEND := $(patsubst %.o,%.d,$(kernel.OBJECT))
kernel.CFLAGS := -ffreestanding -fno-common
kernel.LDFLAGS := -T $(kernel.LINKER) -nostdlib -lgcc
.PHONY: all-kernel clean-kernel distclean-kernel
all-kernel: $(kernel.OUTPUT)
clean-kernel:
	$(RM) $(kernel.OBJECT)
	$(RM) $(kernel.DEPEND)
distclean-kernel: clean-kernel
	$(RM) $(kernel.OUTPUT)
$(kernel.OUTPUT): $(kernel.OBJECT) $(kernel.LINKER)
	$(CC) $(CFLAGS) $(kernel.CFLAGS) $(kernel.LDFLAGS) \
		-o $@ $(kernel.OBJECT)
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $(kernel.CFLAGS) -MMD -MP -MT $@ -o $@ -c $<
kernel/%.o: kernel/%.S
	$(CC) $(CFLAGS) $(kernel.CFLAGS) -MMD -MP -MT $@ -o $@ -c $<
-include $(kernel.DEPEND)

.PHONY: run
run: all-kernel
	$(QEMU) -kernel $(kernel.OUTPUT)
