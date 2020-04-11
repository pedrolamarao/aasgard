.att_syntax

.text

//! x86 interrupt service routine

.global __interrupt_service_routine
.type   __interrupt_service_routine, STT_FUNC
__interrupt_service_routine:
    movb $0, _test_result
	iret
