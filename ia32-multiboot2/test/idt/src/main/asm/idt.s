.att_syntax

.text

//! x86 interrupt service routine

.global __interrupt_service_routine
.type   __interrupt_service_routine, STT_FUNC
.func   __interrupt_service_routine
__interrupt_service_routine:
	iret
.endfunc
