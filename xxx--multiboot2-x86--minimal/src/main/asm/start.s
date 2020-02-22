.att_syntax

.text

.set STACK_SIZE , 0x4000
.comm stack , STACK_SIZE

//! @brief C++ entry point

// extern "C"
// void [[gnu::fastcall]] main ( std::uint32_t magic, multiboot2::information_list & mbi )

.extern main

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

    mov %eax,%ecx
    mov %ebx,%edx
    call main

.Lloop:
    hlt
    jmp .Lloop

.endfunc
