// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

// x86::internal::__read_msr [ fastcall ] : ( id : uint32_t ) -> ( uint64_t )

.global __read_msr
.type   __read_msr, STT_FUNC
__read_msr:
	rdmsr
	ret

// x86::internal::__write_msr_32 [ fastcall ] : ( id : uint32_t, value : uint32_t )

.global __write_msr_32
.type   __write_msr_32, STT_FUNC
__write_msr_32:
	mov %edx, %eax
	xor %edx, %edx
	wrmsr
	ret

// x86::internal::__write_msr_64 [ fastcall ] : ( id : uint32_t, value : uint64_t )

.global __write_msr_64
.type   __write_msr_64, STT_FUNC
__write_msr_64:
	mov 4(%esp), %eax
	mov 8(%esp), %edx
	wrmsr
	ret
