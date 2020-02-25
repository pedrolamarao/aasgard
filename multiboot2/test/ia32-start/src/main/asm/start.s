.att_syntax

.text

.set STACK_SIZE , 0x4000
.comm stack , STACK_SIZE

//! @brief ELF default entry point
//!
//! @param %eax  Multiboot2 information magic number
//! @param %ebx  Multiboot2 information list address

.global _start
.type   _start, STT_FUNC
.func   _start, _start
_start:
    movl $(stack + STACK_SIZE), %esp
    push $0
    popf
    movb $0, _test_result(,1)
.Lloop:
    hlt
    jmp .Lloop
.endfunc

//! @brief Test result

.global _test_result
.type   _test_result, STT_OBJECT
_test_result:
    .byte 0xFF
