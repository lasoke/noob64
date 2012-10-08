#include "StdAfx.h"

ExceptionHandler::ExceptionHandler(void)
{
}

void ExceptionHandler::interruption(void)
{
	cerr << "Interruption" << endl;
}

void ExceptionHandler::trap(void)
{
	cerr << "Trap" << endl;
}

void ExceptionHandler::syscall(void)
{
	cerr << "Syscall" << endl;
}

void ExceptionHandler::unknownInstruction(word i)
{
	char mem[64];
	_itoa_s(i, mem, 64, 2);
	cerr << endl << "Unknown instruction: " << format_number(string(32 - strlen(mem), '0') + mem, ' ', 4) << endl;
	getchar();
	exit(0);
}
