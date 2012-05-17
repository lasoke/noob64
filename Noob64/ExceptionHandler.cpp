#include "StdAfx.h"
#include "ExceptionHandler.h"


ExceptionHandler::ExceptionHandler()
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
