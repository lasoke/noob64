#include "StdAfx.h"
#include "ExceptionHandler.h"

void R4300i::handle_exception(void)
{
	disable_interrupts();
	save_context();
	//EPC <- delay_slot ? address of the branch instruction immediately preceding the delay slot : address of the instruction that causes the exception

}

void R4300i::disable_interrupts(void)
{
	// TODO
}

/*
	The handler saves the context of the processor,
	including the contents of the program counter,
	the current operating mode (User or	Supervisor),
	and the status of the interrupts (enabled or disabled).
	This context is saved so it can be restored when
	the exception has been serviced.
*/
void R4300i::save_context(void)
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