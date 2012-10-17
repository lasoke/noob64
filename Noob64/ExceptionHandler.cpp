#include "StdAfx.h"
#include "ExceptionHandler.h"

/*
	The handler saves the context of the processor,
	including the contents of the program counter,
	the current operating mode (User or	Supervisor),
	and the status of the interrupts (enabled or disabled).
	This context is saved so it can be restored when
	the exception has been serviced.
*/

// TEMPORARY
void R4300i::handle_exception()
{

}

void R4300i::handle_exception(Exception e)
{
	disable_interrupts();
	save_context();

	ExceptionType	type = OTHER;//= getExceptionType(e);
	int				FaultingCopNumber = 0;//= getCoprocessorNumber();

	if (!(Status & STATUS_EXL))
	{
		EPC = delay_slot ? pc - 4 : pc;
		Cause = set_bit(Cause, CAUSE_BD, delay_slot ? true : false);

		if (type == RESET_NMI)
			pc = vectors[RESET_NMI].getVector(Status);
		else if (type == TLB_REFILL)
			pc = vectors[TLB_REFILL].getVector(Status);
		else if (type == XTLB_REFILL)
			pc = vectors[XTLB_REFILL].getVector(Status);
		else if (OTHER)
			pc = vectors[OTHER].getVector(Status);
	}
	else
		pc = vectors[OTHER].getVector(Status);

	//Cause.CE <- FaultingCoprocessorNumber;
	Cause = set_bit(Cause, CAUSE_CE, false);
	Cause |= (FaultingCopNumber << 28);
	//

	//Cause.ExcCode <- ExceptionType;
	Cause = set_bit(Cause, CAUSE_ExcCode, false);
	Cause |= (type << 2);
	//

	Status = set_bit(Status, STATUS_EXL, true);

	// decode(pc);

	restore_context();
	enable_interrupts();
	pc = EPC;
}

void R4300i::disable_interrupts(void)
{
	// TODO
}

void R4300i::enable_interrupts(void)
{
	// TODO
}

void R4300i::save_context(void)
{
	// TODO
}

void R4300i::restore_context(void)
{
	// TODO
}
