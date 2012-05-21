#include "StdAfx.h"
#include "ExceptionHandler.h"


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
	itoa(i, mem, 2);
	cerr << "	Unknown instruction: " << format_number(string(32 - strlen(mem), '0') + mem, ' ', 4) << endl;
	getchar();
	exit(0);
}
