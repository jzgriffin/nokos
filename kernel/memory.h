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

#ifndef MEMORY_H
#define MEMORY_H

#define KERNEL_BASE 0xC0000000 // Base of the kernel virtual address
#define KERNEL_ADDR 0x00100000 // Offset of the kernel from its base
#define KERNEL_STACK_SIZE 4096 // Size of the kernel stack

// Kernel physical-virtual address conversion
#define V2P(a) ((a) - KERNEL_BASE) // Convert a virtual address to physical
#define P2V(a) ((a) + KERNEL_BASE) // Convert a physical address to virtual

#ifndef __ASSEMBLER__

// Indices of GDT entries
enum {
    GDT_NULL,
    GDT_KERNEL_CODE,
    GDT_KERNEL_DATA,
};

void initialize_gdt();

#endif // __ASSEMBLER__

#endif // MEMORY_H
