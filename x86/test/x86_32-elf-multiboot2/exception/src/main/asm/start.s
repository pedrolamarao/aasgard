// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

.set STACK_SIZE , 0x4000
.comm stack , STACK_SIZE

.global _start
.type   _start, STT_FUNC
_start:
        movl    $(stack + STACK_SIZE), %esp
        pushl   $0
        popf
        pushl   %ebx
        pushl   %eax
        call    main
loop:   hlt
        jmp     loop
