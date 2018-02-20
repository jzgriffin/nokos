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

#ifndef I686_H
#define I686_H

#ifndef __ASSEMBLER__
#include <stdint.h>
#endif // __ASSEMBLER__

// Intel 242691 figure 3-7: Format of EFLAGS register
#define EFLAGS_CF   (1 <<  0)
#define EFLAGS_PF   (1 <<  2)
#define EFLAGS_AF   (1 <<  4)
#define EFLAGS_ZF   (1 <<  6)
#define EFLAGS_SF   (1 <<  7)
#define EFLAGS_TF   (1 <<  8)
#define EFLAGS_IF   (1 <<  9)
#define EFLAGS_DF   (1 << 10)
#define EFLAGS_OF   (1 << 11)
#define EFLAGS_IOPL (1 << 12)
#define EFLAGS_NT   (1 << 14)
#define EFLAGS_RF   (1 << 16)
#define EFLAGS_VM   (1 << 17)
#define EFLAGS_AC   (1 << 18)
#define EFLAGS_VIF  (1 << 19)
#define EFLAGS_VIP  (1 << 20)
#define EFLAGS_ID   (1 << 21)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t CF       :  1; // Carry flag
    uint32_t rsv1     :  1; // Reserved (set to 1)
    uint32_t PF       :  1; // Parity flag
    uint32_t rsv3     :  1; // Reserved (set to 0)
    uint32_t AF       :  1; // Auxiliary carry flag
    uint32_t rsv5     :  1; // Reserved (set to 0)
    uint32_t ZF       :  1; // Zero flag
    uint32_t SF       :  1; // Sign flag
    uint32_t TF       :  1; // Trap flag
    uint32_t IF       :  1; // Interrupt enable flag
    uint32_t DF       :  1; // Direction flag
    uint32_t OF       :  1; // Overflow flag
    uint32_t IOPL     :  2; // I/O privilege level
    uint32_t NT       :  1; // Nested task flag
    uint32_t rsv15    :  1; // Reserved (set to 0)
    uint32_t RF       :  1; // Resume flag
    uint32_t VM       :  1; // Virtual 8086 mode
    uint32_t AC       :  1; // Alignment check
    uint32_t VIF      :  1; // Virtual interrupt flag
    uint32_t VIP      :  1; // Virtual interrupt pending
    uint32_t ID       :  1; // Identification flag
    uint32_t rsv31_22 : 10; // Reserved (set to 0)
} eflags_t;
#endif // __ASSEMBLER__

// Intel 242692 figure 2-5: Format of CR4 register
#define CR4_VME (1 << 0)
#define CR4_PVI (1 << 1)
#define CR4_TSD (1 << 2)
#define CR4_DE  (1 << 3)
#define CR4_PSE (1 << 4)
#define CR4_PAE (1 << 5)
#define CR4_MCE (1 << 6)
#define CR4_PGE (1 << 7)
#define CR4_PCE (1 << 8)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t VME     :  1; // Virtual-8086 mode extensions
    uint32_t PVI     :  1; // Protected-mode virtual interrupts
    uint32_t TSD     :  1; // Time stamp disable
    uint32_t DE      :  1; // Debugging extensions
    uint32_t PSE     :  1; // Page size extensions
    uint32_t PAE     :  1; // Physical address extension
    uint32_t MCE     :  1; // Machine check enable
    uint32_t PGE     :  1; // Page global enable
    uint32_t PCE     :  1; // Performance-monitoring counter enable
    uint32_t rsv31_9 : 23; // Reserved (set to 0)
} cr4_t;
#endif // __ASSEMBLER__

// Intel 242692 figure 2-5: Format of CR3 register
#define CR3_PWT (1 << 3)
#define CR3_PCD (1 << 4)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t rsv2_0  :  3; // Reserved (set to 0)
    uint32_t PWT     :  1; // Page-level write transparent
    uint32_t PCD     :  1; // Page-level cache disable
    uint32_t rsv11_5 :  7; // Reserved (set to 0)
    uint32_t PDB     : 20; // Page directory base
} cr3_t;
#endif // __ASSEMBLER__

// Intel 242692 figure 2-5: Format of CR2 register
#define CR3_PFLA (1 << 0)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t PFLA : 32; // Page fault linear address
} cr2_t;
#endif // __ASSEMBLER__

// Intel 242692 figure 2-5: Format of CR0 register
#define CR0_PE (1 <<  0)
#define CR0_MP (1 <<  1)
#define CR0_EM (1 <<  2)
#define CR0_TS (1 <<  3)
#define CR0_ET (1 <<  4)
#define CR0_NE (1 <<  5)
#define CR0_WP (1 << 16)
#define CR0_AM (1 << 18)
#define CR0_NW (1 << 29)
#define CR0_CD (1 << 30)
#define CR0_PG (1 << 31)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t PE       :  1; // Protection enable
    uint32_t MP       :  1; // Monitor coprocessor
    uint32_t EM       :  1; // Emulation
    uint32_t TS       :  1; // Task switched
    uint32_t ET       :  1; // Extension type
    uint32_t NE       :  1; // Numeric error
    uint32_t rsv15_6  : 10; // Reserved (set to 0)
    uint32_t WP       :  1; // Write protect
    uint32_t rsv17    :  1; // Reserved (set to 0)
    uint32_t AM       :  1; // Alignment mask
    uint32_t rsv28_19 : 10; // Reserved (set to 0)
    uint32_t NW       :  1; // Not write-through
    uint32_t CD       :  1; // Cache disable
    uint32_t PG       :  1; // Paging
} cr0_t;
#endif // __ASSEMBLER__

// Intel 242692 figure 3-8: Format of segment descriptor entry
#define SDE_LIMIT15_0  (1 <<  0)
#define SDE_BASE15_0   (1 << 16)
#define SDE_BASE23_16  (1 << 32)
#define SDE_TYPE       (1 << 40)
#define SDE_S          (1 << 44)
#define SDE_DPL        (1 << 45)
#define SDE_P          (1 << 47)
#define SDE_LIMIT19_16 (1 << 48)
#define SDE_AVL20      (1 << 52)
#define SDE_DB         (1 << 54)
#define SDE_G          (1 << 55)
#define SDE_BASE31_24  (1 << 56)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t limit15_0  : 16; // Segment limit bits 15:0
    uint32_t base15_0   : 16; // Base address bits 15:0
    uint32_t base23_16  :  8; // Base address bits 23:16
    uint32_t type       :  4; // Type
    uint32_t S          :  1; // Descriptor type flag
    uint32_t DPL        :  2; // Descriptor privilege level
    uint32_t P          :  1; // Segment present flag (set to 1)
    uint32_t limit19_16 :  4; // Segment limit bits 19:16
    uint32_t avl20      :  1; // Available
    uint32_t rsv21      :  1; // Reserved (set to 0)
    uint32_t DB         :  1; // Default operation/stack size flag
    uint32_t G          :  1; // Granularity flag
    uint32_t base31_24  :  8; // Base address bits 31:24
} sde_t;
#endif // __ASSEMBLER__

// Intel 242692 table 3-1: Values of application (code and data) segment types
#define STA_X (1 << 3) // Code/executable
#define STA_A (1 << 0) // Accessed
// If not STA_X
#define STA_E (1 << 2) // Expand-down
#define STA_W (1 << 1) // Writeable
// If STA_X
#define STA_C (1 << 2) // Conforming
#define STA_R (1 << 1) // Readable

// Intel 242692 table 3-2: Values of system segment types
#define STS_TSS16A  1 // 16-bit TSS (available)
#define STS_LDT     2 // LDT
#define STS_TSS16B  3 // 16-bit TSS (busy)
#define STS_CG16    4 // 16-bit call gate
#define STS_TG      5 // Task gate
#define STS_IG16    6 // 16-bit interrupt gate
#define STS_TG16    7 // 16-bit trap gate
#define STS_TSS32A  9 // 32-bit TSS (available)
#define STS_TSS32B 11 // 32-bit TSS (busy)
#define STS_CG32   12 // 32-bit call gate
#define STS_IG32   14 // 32-bit interrupt gate
#define STS_TG32   15 // 32-bit trap gate

// Values of descriptor privilege levels
#define DPL_KERNEL 0
#define DPL_USER   3

// Format of absent segment descriptor entry (Intel 242692 figure 3-9)
#define SDE_ABSENT_AVL31_0  (1 <<  0)
#define SDE_ABSENT_AVL39_32 (1 << 32)
#define SDE_ABSENT_TYPE     (1 << 40)
#define SDE_ABSENT_S        (1 << 44)
#define SDE_ABSENT_DPL      (1 << 45)
#define SDE_ABSENT_P        (1 << 47)
#define SDE_ABSENT_AVL63_48 (1 << 48)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t avl31_0  : 32; // Available bits 31:0
    uint32_t avl39_32 :  8; // Available bits 39:32
    uint32_t type     :  4; // Type
    uint32_t S        :  1; // Descriptor type flag
    uint32_t DPL      :  2; // Descriptor privilege level
    uint32_t P        :  1; // Segment present flag (set to 0)
    uint32_t avl63_48 : 16; // Available bits 63:48
} sde_absent_t;
#endif // __ASSEMBLER__

// Intel 242692 figures 3-14a & 3-15: Format of page-directory entries
#define PDE_P       (1 <<  0)
#define PDE_RW      (1 <<  1)
#define PDE_US      (1 <<  2)
#define PDE_PWT     (1 <<  3)
#define PDE_PCD     (1 <<  4)
#define PDE_A       (1 <<  5)
#define PDE_D       (1 <<  6)
#define PDE_PS      (1 <<  7)
#define PDE_G       (1 <<  8)
#define PDE_AVL11_9 (1 <<  9)
#define PDE_PTBA    (1 << 12)
#define PDE_PBA     (1 << 22)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t P       : 1; // Present flag
    uint32_t RW      : 1; // Read/write flag
    uint32_t US      : 1; // User/supervisor flag
    uint32_t PWT     : 1; // Page-level write-through flag
    uint32_t PCD     : 1; // Page-level cache disabled flag
    uint32_t A       : 1; // Accessed flag
    uint32_t D       : 1; // Dirty flag (when PS = 1)
    uint32_t PS      : 1; // Page size flag
    uint32_t G       : 1; // Global page flag
    uint32_t avl11_9 : 3; // Available bits 11:9
    union {
        struct {
            uint32_t rsv21_12 : 10; // Reserved (set to 0)
            uint32_t PBA      : 10; // Page base address (when PS = 1)
        };
        uint32_t PTBA : 20; // Page-table base address (when PS = 0)
    };
} pde_t;
#endif // __ASSEMBLER__

// Intel 242692 figure 3-14b: Format of page-table entries
#define PTE_P       (1 <<  0)
#define PTE_RW      (1 <<  1)
#define PTE_US      (1 <<  2)
#define PTE_PWT     (1 <<  3)
#define PTE_PCD     (1 <<  4)
#define PTE_A       (1 <<  5)
#define PTE_D       (1 <<  6)
#define PTE_G       (1 <<  8)
#define PTE_AVL11_9 (1 <<  9)
#define PTE_PBA     (1 << 12)
#ifndef __ASSEMBLER__
typedef struct {
    uint32_t P       :  1; // Present flag
    uint32_t RW      :  1; // Read/write flag
    uint32_t US      :  1; // User/supervisor flag
    uint32_t PWT     :  1; // Page-level write-through flag
    uint32_t PCD     :  1; // Page-level cache disabled flag
    uint32_t A       :  1; // Accessed flag
    uint32_t D       :  1; // Dirty flag (when PS = 1)
    uint32_t rsv7    :  1; // Reserved (set to 0)
    uint32_t G       :  1; // Global page flag
    uint32_t avl11_9 :  3; // Available bits 11:9
    uint32_t PBA     : 20; // Page base address
} pte_t;
#endif // __ASSEMBLER__

// Paging parameters
#define PAGE_SIZE_4K 0x01000 // Size of a 4 KiB page in bytes
#define PAGE_SIZE_4M 0x40000 // Size of a 4 MiB page in bytes
#define PDT_ALIGN 0x1000 // Alignment of page directory tables
#define PDT_SIZE   0x400 // Number of entries per page directory
#define PDX_SIZE   0x3FF // Size of a page directory index in a linear address
#define PDX_OFFSET    22 // Offset of page directory index in a linear address
#define PTT_ALIGN 0x1000 // Alignment of page tables
#define PTT_SIZE   0x400 // Number of entries per page table
#define PTX_SIZE   0x3FF // Size of a page table index in a linear address
#define PTX_OFFSET    12 // Offset of page table index in a linear address

// Paging macros
// Get page directory index from virtual address
#define PDX(va) (((va) >> PDX_OFFSET) & PDX_SIZE)
// Get page table index from virtual address
#define PTX(va) (((va) >> PTX_OFFSET) & PTX_SIZE)
// Get virtual address from page directory index, page table index, and offset
#define VA(d, t, o) (((d) << PDX_OFFSET) | ((t) << PTX_OFFSET) | (o))

#endif // I686_H
