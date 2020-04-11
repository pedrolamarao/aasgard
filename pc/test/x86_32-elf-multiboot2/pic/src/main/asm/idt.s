.att_syntax

//! extern "C" std::uint32_t volatile _test_result

.extern _test_result

//! x86 interrupt service routine

.global __interrupt_service_routine
.type   __interrupt_service_routine, STT_FUNC
__interrupt_service_routine:
    movl $0, _test_result
	iret
