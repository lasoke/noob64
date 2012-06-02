// Noob64.cpp : main project file.

#include "stdafx.h"

using namespace Noob64;

FILE *stream;

void inline enableConsole()
{
    errno_t err;
	AllocConsole();
	err = freopen_s(&stream, "conin$","r", stdin);
	err = freopen_s(&stream, "conout$","w", stdout);
	err = freopen_s(&stream, "conout$","w", stderr);
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	enableConsole();

	RDRAM*		ram = new RDRAM();
	R4300i*		cpu = new R4300i(*ram);
	RomLoader*	rom = new RomLoader();

	char		addr[8];
	int			instr_s = sizeof(word);

	for (int i = 0; i < BOOT_CODE_SIZE; i++)
	{
#if defined DEBUG
			memset(addr, 0, 8);
			_itoa_s(0x40 + i * instr_s, addr, 8, 16);
			cout << endl << format_number(string(8 - strlen(addr), '0') + addr, ' ', 2) << " : ";
#endif
		cpu->decode(rom->getInstruction(i));
	}

	/*
	ram->write<word>(4294967295, 1);
	ram->write<word>(0, 2);
	ram->read<hword>(3);
	ram->debug(true, 0, 9);

	Instruction* instr1 = new Instruction(0xf0f0f0f0);
	Instruction* instr2 = new Instruction(0x0f0f0f0f);
	*instr1 == instr2->getInstr();
	cout << instr1->getInstr() << endl;
	*/
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
