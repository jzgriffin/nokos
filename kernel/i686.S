/* Nokos
 * Copyright (c) Jeremiah Z. Griffin <nokurn@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

.global lgdt
.type lgdt, @function
lgdt:
    push    %ebp
    mov     %esp, %ebp
    subl    $6, %esp
    push    %eax

    // 8(%ebp): Pointer to GDT
    // 12(%ebp): Size of GDT in bytes

    // GDTR47..16: Base address
    // GDTR15..0: Limit

    movl    12(%ebp), %eax
    dec     %eax
    movw    %ax, -6(%ebp)
    movl    8(%ebp), %eax
    movl    %eax, -4(%ebp)
    lgdt    -6(%ebp)

    pop     %eax
    mov     %ebp, %esp
    pop     %ebp
    ret
.size lgdt, . - lgdt
