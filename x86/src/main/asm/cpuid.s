// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

// x86::internal::__has_cpuid [ fastcall ] : ( ) -> ( bool )

.global __has_cpuid
.type   __has_cpuid, STT_FUNC
__has_cpuid:
	pushf
	pop %ebx
    btc $21, %ebx
    push %ebx
    popf
    pushf
    pop %ecx
    xor %eax, %eax
    cmp %ebx, %ecx
    sete %al
	ret

// x86::internal::__read_cpuid [ fastcall ] : ( uint32_t id, uint32_t extra, cpuid & result ) -> ()

.global __read_cpuid
.type   __read_cpuid, STT_FUNC
__read_cpuid:
	mov %ecx, %eax
	mov %edx, %ecx
	cpuid
	mov 4(%esp), %edi
	mov %eax, (%edi)
	mov %ebx, 4(%edi)
	mov %ecx, 8(%edi)
	mov %edx, 12(%edi)
	ret
