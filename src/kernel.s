.section .rodata
__stack_top:
    .skip 0x20000
__stack_bottom:

.section .text.boot
.global _kissEntry
.type _kissEntry, @function
_kstart:
    mv ra, zero
    mv fp, zero

    la sp, __stack_bottom
    jal _kissEntry
