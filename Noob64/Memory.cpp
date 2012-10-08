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
		rdram[i] = 0;
	ptr = rdram;
}

// RDRAM REGISTERS
RDRAM_REGS::RDRAM_REGS() :
	config_reg(0),
	device_id_reg(0),
	delay_reg(0),
	mode_reg(0),
	ref_interval_reg(0),
	ref_row_reg(0),
	ras_interval_reg(0),
	min_interval_reg(0),
	addr_select_reg(0),
	device_manuf_reg(0)
{
	// IMPORTANT: ptr has to point on the first data of the segment!
	ptr = &config_reg;
}



//****************************************************************************
//** DUMP METHODS					                                        **
//****************************************************************************

void RDRAM::dump(/*word start, word end*/) const
{
	cout << "*** RDRAM ***" << endl;
//	for (unsigned int i = start; i < end; i += sizeof(word))
//		read<word>(i);
	cout << "*** END OF RDRAM ***"<< endl;
}

void RDRAM_REGS::dump(void) const
{
	cout << "*** RDRAM REGISTERS ***" << endl;
	cout << "	config_reg = "			<< config_reg		<< endl;
	cout << "	device_id_reg = "		<< device_id_reg	<< endl;
	cout << "	delay_reg = "			<< delay_reg		<< endl;
	cout << "	mode_reg = "			<< mode_reg			<< endl;
	cout << "	ref_interval_reg = "	<< ref_interval_reg << endl;
	cout << "	ref_row_reg = "			<< ref_row_reg		<< endl;
	cout << "	ras_interval_reg = "	<< ras_interval_reg << endl;
	cout << "	min_interval_reg = "	<< min_interval_reg << endl;
	cout << "	addr_select_reg = "		<< addr_select_reg	<< endl;
	cout << "	device_manuf_reg = "	<< device_manuf_reg << endl;
	cout << "*** END OF RDRAM REGISTERS ***"<< endl;
}

