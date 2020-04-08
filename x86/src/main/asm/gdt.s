// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

// TODO: this should be placed in the .recycle section

.Lgdtr:
	.short 0
    .long 0

// x86::internal::__load_global_descriptor_table [ fastcall ] : ( base : dword , limit : word ) -> ()

.global __load_global_descriptor_table
.type   __load_global_descriptor_table, STT_FUNC
__load_global_descriptor_table:
	mov %ecx, .Lgdtr + 2
	mov %dx, .Lgdtr
	lgdt .Lgdtr
	ret

// x86::internal::__store_global_descriptor_table [ fastcall ] : ( base : ptr<dword> , limit : ptr<word> ) -> ()

.global __store_global_descriptor_table
.type   __store_global_descriptor_table, STT_FUNC
__store_global_descriptor_table:
	movl 4(%esp), %eax
	sgdt (%eax)
	ret

// x86::internal::__reload_segment_registers [ fastcall ] : ( code : word , data : word ) -> ()

.global __reload_segment_registers
.type   __reload_segment_registers, STT_FUNC
__reload_segment_registers:
	push %ecx
	mov $reload, %eax
	push %eax
	lret
reload:
	mov %dx, %ds
	mov %dx, %es
	mov %dx, %fs
	mov %dx, %gs
	mov %dx, %ss
	ret
