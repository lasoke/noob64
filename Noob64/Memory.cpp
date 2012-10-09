#include "StdAfx.h"

//****************************************************************************
//** CONSTRUCTORS					                                        **
//****************************************************************************

// MEMORY
MEMORY::MEMORY()
{
	rdram = new RDRAM();
	rdram_regs = new RDRAM_REGS();
}

// MEMORY SEGMENT
MEM_SEG::MEM_SEG() :
	ptr(0)
{
}

// RDRAM
RDRAM::RDRAM()
{
	for (int i = 0; i < size; i++)
		data[i] = 0;
	ptr = data;
}

// RDRAM REGISTERS
RDRAM_REGS::RDRAM_REGS()
{
	data.config = 0;
	data.device_id = 0;
	data.delay = 0;
	data.mode = 0;
	data.ref_interval = 0;
	data.ref_row = 0;
	data.ras_interval = 0;
	data.min_interval = 0;
	data.addr_select = 0;
	data.device_manuf = 0;
	int length = sizeof(data.unknown); 
	for (int i = 0; i < length; i++)
		data.unknown[0] = 0;
	ptr = &data;
}



//****************************************************************************
//** DUMP METHODS					                                        **
//****************************************************************************

//

void RDRAM::dump(void) const
{
	cout << "*** RDRAM ***" << endl;

	for (unsigned int i = 0; i < 32; i += sizeof(word))
	{
		word line = binary_to_type<word>(data + i);
		// print address
		char addr[8];
		itoa(i, addr, 16);
		cout << format_number(string(8 - strlen(addr), '0') + addr, ' ', 2) << " : ";
		// print data
		char mem[64];
		itoa(line, mem, 2);
		cout << format_number(string(sizeof(word) * 8 - strlen(mem), '0') + mem, ' ', 8) << endl;
	}

	cout << "*** END OF RDRAM ***"<< endl;
}

void RDRAM_REGS::dump(void) const
{
	/*
	cout << "*** RDRAM REGISTERS ***" << endl;
	cout << "	config = "			<< config		<< endl;
	cout << "	device_id = "		<< device_id	<< endl;
	cout << "	delay = "			<< delay		<< endl;
	cout << "	mode = "			<< mode			<< endl;
	cout << "	ref_interval = "	<< ref_interval << endl;
	cout << "	ref_row = "			<< ref_row		<< endl;
	cout << "	ras_interval = "	<< ras_interval << endl;
	cout << "	min_interval = "	<< min_interval << endl;
	cout << "	addr_select = "		<< addr_select	<< endl;
	cout << "	device_manuf = "	<< device_manuf << endl;
	cout << "*** END OF RDRAM REGISTERS ***"<< endl;
	*/
}

