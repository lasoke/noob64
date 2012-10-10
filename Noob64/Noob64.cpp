// Noob64.cpp : main project file.

#include "stdafx.h"
#include <time.h>

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

	MEMORY*		memory	= new MEMORY();
	RomLoader*	rom		= new RomLoader();
	R4300i*		cpu		= new R4300i(*memory);
	
	/*
	srand((unsigned int) time(NULL));
	while (true)
	{
		int t = rand() % 4;
		int a = RDRAM_REGS::begining + (rand() % (RDRAM_REGS::end - RDRAM_REGS::begining)) + ((rand() % 0x10) << 16);
		//int a = RDRAM_REGS::end;
		long long d = -1;
		long long r = -1;
		
		if (t == 0)
		{
			d = rand() % BYTE_MAX;
			memory->write<byte>((byte) d, a);
			r = memory->read<byte>(a);
		}
		else if (t == 1)
		{
			d = rand() % HWORD_MAX;
			memory->write<hword>((hword) d, a);
			r = memory->read<hword>(a);
		}
		else if (t == 2)
		{
			d = rand() % WORD_MAX;
			memory->write<word>((word) d, a);
			r = memory->read<word>(a);
		}
		else if (t == 3)
		{
			d = rand() % DWORD_MAX;
			memory->write<dword>(d, a);
			r = memory->read<dword>(a);
		}

		if (r != d)
		{
			cout << "FAILED: t=" << t << "\tr=0x" << hex << r << "\td=0x" << hex << d << "\ta=0x" << hex << a << endl;
			break;
		}
		cout << "PASSED: t=" << t << " a=0x" << hex << a << endl;
		//getchar();
	}

	memory->rdram->dump_range(0x000F0ACB, 0x000F0BFF);
	*/

	cpu->boot(rom->getBootCode());
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
