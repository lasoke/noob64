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

	dword			vector_offset;
	ExceptionType	type = OTHER;//= getExceptionType(e);
	int				FaultingCopNumber = 0;//= getCoprocessorNumber();

	if (!(Status & STATUS_EXL))
	{
		EPC = delay_slot ? pc - 4 : pc;
		Cause = set_bit(Cause, CAUSE_BD, delay_slot ? true : false);
		if (type == TLB_REFILL)
			vector_offset = 0x000;
		else if (type == /* Interrupt */ OTHER /* ? */  && Cause & 0x10)
			vector_offset = 0x200;
		else
			vector_offset = 0x180;
	}
	else
		vector_offset = 0x180;

	//Cause.CE <- FaultingCoprocessorNumber;
	Cause = set_bit(Cause, CAUSE_CE, false);
	Cause |= (FaultingCopNumber << 28);
	//

	//Cause.ExcCode <- ExceptionType;
	Cause = set_bit(Cause, CAUSE_ExcCode, false);
	Cause |= (type << 2);
	//

	Status = set_bit(Status, STATUS_EXL, true);
	pc = vector_offset + (Status & STATUS_BEV) ? 0xBFC00200 : 0x80000000;

	// execute exception:
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


/*
void R4300i::unknown_instruction(word i)
{
	char mem[64];
	_itoa_s(i, mem, 64, 2);
	cerr << endl << "Unknown instruction: " << format_number(string(32 - strlen(mem), '0') + mem, ' ', 4) << endl;
	getchar();
	exit(0);
}
*/