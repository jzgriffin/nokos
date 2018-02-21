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
OBJCOPY := $(TOOLCHAIN)objcopy
GDB := $(TOOLCHAIN)gdb
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
kernel.SYMBOL := $(patsubst %.elf,%.sym,$(kernel.OUTPUT))
kernel.LINKER := $(patsubst %.elf,%.ld,$(kernel.OUTPUT))
kernel.SOURCE := \
    kernel/i686.S \
    kernel/main.c \
    kernel/memory.c \
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
	$(RM) $(kernel.OUTPUT) $(kernel.SYMBOL)
$(kernel.OUTPUT): $(kernel.OBJECT) $(kernel.LINKER)
	$(CC) $(CFLAGS) $(kernel.CFLAGS) $(kernel.LDFLAGS) \
		-o $@ $(kernel.OBJECT)
ifneq ($(BUILD),release)
	$(OBJCOPY) --only-keep-debug $(kernel.OUTPUT) $(kernel.SYMBOL)
	$(OBJCOPY) --strip-debug $(kernel.OUTPUT)
endif
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $(kernel.CFLAGS) -MMD -MP -MT $@ -o $@ -c $<
kernel/%.o: kernel/%.S
	$(CC) $(CFLAGS) $(kernel.CFLAGS) -MMD -MP -MT $@ -o $@ -c $<
-include $(kernel.DEPEND)

.PHONY: run run-console run-gdb run-gdb-console stop gdb
run: all-kernel
	$(QEMU) -kernel $(kernel.OUTPUT)
run-console: all-kernel
	$(QEMU) -nographic -kernel $(kernel.OUTPUT)
run-gdb: all-kernel
	$(QEMU) -S -s -kernel $(kernel.OUTPUT)
run-gdb-console: all-kernel
	$(QEMU) -nographic -S -s -kernel $(kernel.OUTPUT)
stop:
	kill $(shell pgrep $(QEMU))
gdb:
	$(GDB) -q
