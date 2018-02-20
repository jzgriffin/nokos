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

#include "i686.h"
#include "memory.h"

// Multiboot header
// The linker will ensure that the .multiboot section is placed in a location
// that a multiboot loader will expect
.set MULTIBOOT_ALIGN, 4
.set MULTIBOOT_MAGIC, 0x1BADB002
.set MULTIBOOT_FLAGS, 0 // The kernel does not rely on multiboot information
.section .multiboot
.align MULTIBOOT_ALIGN
.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAGS
.long -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

// Entry point
.section .text
.global entry
entry:
    // Enable page size extension for 4 MiB pages
    movl    %cr4, %eax
    orl     $(CR4_PSE), %eax
    movl    %eax, %cr4
    // Use the entry page directory
    movl    $(V2P(entry_pdt)), %eax
    movl    %eax, %cr3
    // Enable paging
    movl    %cr0, %eax
    orl     $(CR0_PG | CR0_WP), %eax
    movl    %eax, %cr0
    // Use an indirect jump to continue at the relocated address of the kernel
    leal    continue, %eax
    jmp     *%eax
continue:
    // Unmap the page containing the starting location of the kernel
    movl    $0, entry_pdt + 0
    invlpg  0
    // Set up the kernel stack
    movl    $(stack + KERNEL_STACK_SIZE), %esp
    // Enter the kernel proper
    jmp     main
.global _start
_start = V2P(entry)

// Entry page directory table
// Create a complete page directory table with only two present PDEs: for the
// current page of the kernel (page 0) and the destination page of the kernel,
// using 4 MiB pages.  The PDEs for the kernel map to the first 4 MiB of
// physical memory in read/write mode.
.section .data
.align PDT_ALIGN
entry_pdt:
.set KERNEL_PDX, PDX(KERNEL_BASE)
.set KERNEL_PDE, (0x00000 << PDX_OFFSET) | PDE_PS | PDE_RW | PDE_P
.set NULL_PDE, 0
.long KERNEL_PDE // PDE for current kernel page
.rept KERNEL_PDX - 1
    .long NULL_PDE // Pad intermediate PDEs
.endr
.long KERNEL_PDE // PDE for destination kernel page
.rept PDT_SIZE - KERNEL_PDX - 1
    .long NULL_PDE // Pad remaining PDEs
.endr

// Kernel stack
// The .comm directive creates a symbol in the COMMON section, which is merged
// with the .bss section when -fno-common is used.  The alignment will be the
// largest power of two less than or equal to STACK_SIZE, up to a maximum of
// 16.  The kernel stack is larger than 16, so the stack will automatically be
// aligned at 16 bytes, which is acceptable.
.comm stack, KERNEL_STACK_SIZE
