// Noob64.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include <windows.h>


using namespace Noob64;

void inline enableConsole()
{
	AllocConsole();
	freopen("conin$","r", stdin);
	freopen("conout$","w", stdout);
	freopen("conout$","w", stderr);
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	enableConsole();

	RDRAM* ram = new RDRAM();
	/*
	ram->write<word>(4294967295, 1);
	ram->write<word>(0, 2);
	ram->read<hword>(3);
	ram->debug(true, 0, 9);
	*/
	Instruction* instr1 = new Instruction(0xf0f0f0f0);
	Instruction* instr2 = new Instruction(0x0f0f0f0f);
	*instr1 == instr2->getInstr();
	cout << instr1->getInstr() << endl;
	getchar();
	
	/*
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	*/

	return 0;
}
