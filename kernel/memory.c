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

#include "memory.h"
#include "i686.h"

static sde_t gdt[] = {
    [GDT_NULL] = SDE_NULL(),
    [GDT_KERNEL_CODE] = SDE(0xFFFFFFFF, 0, 1, STA_X | STA_R, DPL_KERNEL),
    [GDT_KERNEL_DATA] = SDE(0xFFFFFFFF, 0, 1, STA_W, DPL_KERNEL),
};

void initialize_gdt()
{
    lgdt(gdt, sizeof gdt);
}
