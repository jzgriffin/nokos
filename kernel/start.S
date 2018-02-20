// Nokos
// Copyright (c) Jeremiah Z. Griffin <nokurn@gmail.com>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE NEGLIGENCE OR OTHER TORTIOUS ACTION,
// ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
// SOFTWARE.

#include "config.h"

// Multiboot header
// The linker will ensure that the .multiboot section is placed in a location
// that a multiboot loader will expect
.set MULTIBOOT_MAGIC, 0x1BADB002
.set MULTIBOOT_FLAGS, 0 // The kernel does not rely on multiboot information
.section .multiboot
.align 4
.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAGS
.long -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

// Entry point
.section .text
.global _start
_start:
    // Set up the kernel stack
    movl    $(stack + KERNEL_STACK_SIZE), %esp
    // Use an indirect jump to enter the kernel proper
    // Indirect jumps are always long jumps and will set CS accordingly
    mov     $main, %eax
    jmp     *%eax

// Kernel stack
// The .comm directive creates a symbol in the COMMON section, which is merged
// with the .bss section when -fno-common is used.  The alignment will be the
// largest power of two less than or equal to STACK_SIZE, up to a maximum of
// 16.  The kernel stack is larger than 16, so the stack will automatically be
// aligned at 16 bytes, which is acceptable.
.comm stack, KERNEL_STACK_SIZE
