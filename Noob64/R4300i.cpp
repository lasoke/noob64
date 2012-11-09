/*
 * Noob64 - A Nintendo 64 emulator.
 *
 * (c) Copyright 2012 Quentin Metzler and 
 * Romain Richard.
 *
 * Permission to use, copy, modify and distribute Noob64 in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Noob64 is freeware for PERSONAL USE only. Commercial users should
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#include "StdAfx.h"
#include "R4300i.h"

R4300i::R4300i(MEMORY *mem) : memory(mem)
{
	timers = new Timers();
}

void R4300i::reset()
{
	for (int i = 0; i < 32; i++)
	{
		r[i]				= (dword) 0;
		f[i]				= (dword) 0;
		cop0[i]				= (word)  0;
		// --------------tlb------------------------
		tlb_e[i].mask		= 0;
		tlb_e[i].vpn2		= 0;
		tlb_e[i].g			= 0;
		tlb_e[i].asid		= 0;
		tlb_e[i].pfn_even	= 0;
		tlb_e[i].c_even		= 0;
		tlb_e[i].d_even		= 0;
		tlb_e[i].v_even		= 0;
		tlb_e[i].pfn_odd	= 0;
		tlb_e[i].c_odd		= 0;
		tlb_e[i].d_odd		= 0;
		tlb_e[i].v_odd		= 0;
		tlb_e[i].r			= 0;
		//tlb_e[i].check_parity_mask=0x1000;

		tlb_e[i].start_even = 0;
		tlb_e[i].end_even	= 0;
		tlb_e[i].phys_even	= 0;
		tlb_e[i].start_odd	= 0;
		tlb_e[i].end_odd	= 0;
		tlb_e[i].phys_odd	= 0;
	}

	for (int i = 0; i < 0x100000; i++)
	{ 
		tlb_lut_r[i] = 0;
		tlb_lut_w[i] = 0;
	}

	pc			= 0;
	hi			= 0;
	lo			= 0;
	fcr0		= 0;
	fcr31		= 0x01000800;
	ll			= false;
	delay_slot	= false;
	running		= true;
	cic_chip	= 0;

	interrupt_detected	= false;
	current_coprocessor = CPU;
	
	timers->CurrentTimerType = -1;
	timers->Timer = 0;
	for (int i = 0; i < MaxTimers; ++i) 
		timers->Active[i]= FALSE;
	timers->ChangeTimer(ViTimer,5000, Compare, Count); 
	timers->ChangeCompareTimer(Compare, Count);
}

void R4300i::init_crc()
{
	// PIF ROM Initialization
	r[2]	= 0xFFFFFFFFD1731BE9;
	r[3]	= 0xFFFFFFFFD1731BE9;
	r[4]	= 0x0000000000001BE9;
	r[5]	= 0xFFFFFFFFF45231E5;
	r[6]	= 0xFFFFFFFFA4001F0C;
	r[7]	= 0xFFFFFFFFA4001F08;
	r[8]	= 0x00000000000000C0;
	r[10]	= 0x0000000000000040;
	r[11]	= 0xFFFFFFFFA4000040;
	r[12]	= 0xFFFFFFFFD1330BC3;
	r[13]	= 0xFFFFFFFFD1330BC3;
	r[14]	= 0x0000000025613A26;
	r[15]	= 0x000000002EA04317;
	r[20]	= 0x0000000000000001;//rom_info.tv_sys
	r[22]	= 0x000000000000003F;//rom_info.cic
	r[23]	= 0x0000000000000001;
	r[25]	= 0xFFFFFFFFD73F2993;
	r[29]	= 0xFFFFFFFFA4001FF0;
	r[31]	= 0xFFFFFFFFA4001554;
	
	Config	= 0x0006E463;
	Status	= 0x34000000;
	PRevID	= 0x00000B00;
	Random	= 0x0000001F;
	/*
	Count		= 0x00005000;
	Cause		= 0x0000005C;
	Context		= 0x007FFFF0;
	EPC			= 0xFFFFFFFF;
	BadVAddr	= 0xFFFFFFFF;
	ErrorEPC	= 0xFFFFFFFF;
	*/
	memory->write<word>(0x02020202, 0x04300004); // MI_VERSION_REG		<- 0x02020202
	memory->write<word>(0x00000041, 0x04040010); // SP_STATUS_REG		<- 0x00000041
	memory->write<word>(0x00000088, 0x0410000C); // DPC_STATUS_REG		<- 0x00000088
	memory->write<word>(0x00000040, 0x04600014); // PI_BSD_DOM1_LAT_REG <- 0x00000040
	memory->write<word>(0x00000012, 0x04600018); // PI_BSD_DOM1_PWD_REG <- 0x00000012
	memory->write<word>(0x00000007, 0x0460001C); // PI_BSD_DOM1_PGS_REG <- 0x00000007
	memory->write<word>(0x00000003, 0x04600020); // PI_BSD_DOM1_RLS_REG <- 0x00000003

	fcr0 = 0x511;

	sdword CRC = 0;
	
	/**
	* The PIF ROM then copies the first 0x1000 bytes from the cartridge 
	* (located at 0xb000 0000) to memory address 0xA400 0000.
	* Next the PIF ROM sets the PC to 0xA400 0040. Note that this skips 
	* the first 0x40 bytes of the program because that is where the 
	* cartridge header is stored.
	*/

	// PIF ROM copies first 0x1000 bytes of ROM to first 0x1000 bytes of SP_MEM
	for(int i = 0; i < 0x1000; i++)
		memory->write<byte>(*(memory->rom)[i], SP_REGS::begining + i);
	pc = 0xA4000040;

	memory->write<word>(0xBDA807FC, 0x04001004);
	memory->write<word>(0x3C0DBFC0, 0x04001000);
	memory->write<word>(0x25AD07C0, 0x04001008);
	memory->write<word>(0x31080080, 0x0400100C);
	memory->write<word>(0x5500FFFC, 0x04001010);
	memory->write<word>(0x3C0DBFC0, 0x04001014);
	memory->write<word>(0x8DA80024, 0x04001018);
	memory->write<word>(0x3C0BB000, 0x0400101C);
	memory->write<word>(0x6886A9C1, 0x04001F94);
	memory->write<word>(0x915F5B7E, 0x04001F90);

	/*
	for (int i = 0x40 / 4; i < 0x1000 / 4; i++)
		CRC += ((word *) memory->sp_regs.ptr)[i];
	switch(CRC) {
	case 0x000000D0027FDF31:
	case 0x000000CFFB631223:
		cic_chip = 1;
		break;
	case 0x000000D057C85244:
		cic_chip = 2;
		break;
	case 0x000000D6497E414B:
		cic_chip = 3;
		break;
	case 0x0000011A49F60E96:
		cic_chip = 5;
		break;
	case 0x000000D6D5BE5580:
		cic_chip = 6;
		break;
	default:
		cic_chip = 2;
	}

	switch(rom->getCountry() & 0xFF)
	{
	case 0x44:
	case 0x46:
	case 0x49:
	case 0x50:
	case 0x53:
	case 0x55:
	case 0x58:
	case 0x59:
		switch (cic_chip) {
		case 2:
			r[5] = 0xFFFFFFFFC0F1D859;
			r[14]= 0x000000002DE108EA;
			break;
		case 3:
			r[5] = 0xFFFFFFFFD4646273;
			r[14]= 0x000000001AF99984;
			break;
		case 5:
			memory->write<word>(0x04001004, 0xBDA807FC);
			r[5] = 0xFFFFFFFFDECAAAD1;
			r[14]= 0x000000000CF85C13;
			r[24]= 0x0000000000000002;
			break;
		case 6:
			r[5] = 0xFFFFFFFFB04DC903;
			r[14]= 0x000000001AF99984;
			r[24]= 0x0000000000000002;
			break;
		}
		r[23]= 0x0000000000000006;
		r[31]= 0xFFFFFFFFA4001554;
		break;
	case 0x37:
	case 0x41:
	case 0x45:
	case 0x4A:
	default:
		switch (cic_chip) {
		case 2:
			r[5] = 0xFFFFFFFFC95973D5;
			r[14]= 0x000000002449A366;
			break;
		case 3:
			r[5] = 0xFFFFFFFF95315A28;
			r[14]= 0x000000005BACA1DF;
			break;
		case 5:
			memory->write<word>(0x04001004, 0xBDA807FC);
			r[5] = 0x000000005493FB9A;
			r[14]= 0xFFFFFFFFC2C20384;
			break;
		case 6:
			r[5] = 0xFFFFFFFFE067221F;
			r[14]= 0x000000005CD2B70F;
			break;
		}
		r[20]= 0x0000000000000001;
		r[24]= 0x0000000000000003;
		r[31]= 0xFFFFFFFFA4001550;
	}
	switch (cic_chip) {
	case 1:
		r[22]= 0x000000000000003F;
		break;
	case 2:
		r[1] = 0x0000000000000001;
		r[2] = 0x000000000EBDA536;
		r[3] = 0x000000000EBDA536;
		r[4] = 0x000000000000A536;
		r[12]= 0xFFFFFFFFED10D0B3;
		r[13]= 0x000000001402A4CC;
		r[15]= 0x000000003103E121;
		r[22]= 0x000000000000003F;
		r[25]= 0xFFFFFFFF9DEBB54F;
		break;
	case 3:
		r[1] = 0x0000000000000001;
		r[2] = 0x0000000049A5EE96;
		r[3] = 0x0000000049A5EE96;
		r[4] = 0x000000000000EE96;
		r[12]= 0xFFFFFFFFCE9DFBF7;
		r[13]= 0xFFFFFFFFCE9DFBF7;
		r[15]= 0x0000000018B63D28;
		r[22]= 0x0000000000000078;
		r[25]= 0xFFFFFFFF825B21C9;
		break;
	case 5:
		memory->write<word>(0x04001000, 0x3C0DBFC0);
		memory->write<word>(0x04001008, 0x25AD07C0);
		memory->write<word>(0x0400100C, 0x31080080);
		memory->write<word>(0x04001010, 0x5500FFFC);
		memory->write<word>(0x04001014, 0x3C0DBFC0);
		memory->write<word>(0x04001018, 0x8DA80024);
		memory->write<word>(0x0400101C, 0x3C0BB000);
		r[2] = 0xFFFFFFFFF58B0FBF;
		r[3] = 0xFFFFFFFFF58B0FBF;
		r[4] = 0x0000000000000FBF;
		r[12]= 0xFFFFFFFF9651F81E;
		r[13]= 0x000000002D42AAC5;
		r[15]= 0x0000000056584D60;
		r[22]= 0x0000000000000091;
		r[25]= 0xFFFFFFFFCDCE565F;
		break;
	case 6:
		r[2] = 0xFFFFFFFFA95930A4;
		r[3] = 0xFFFFFFFFA95930A4;
		r[4] = 0x00000000000030A4;
		r[12]= 0xFFFFFFFFBCB59510;
		r[13]= 0xFFFFFFFFBCB59510;
		r[15]= 0x000000007A3C07F4;
		r[22]= 0x0000000000000085;
		r[25]= 0x00000000465E3F72;
		break;
	}
	*/
}

void R4300i::RefreshScreen()
{
	static word OLD_VI_V_SYNC_REG = 0, VI_INTR_TIME = 500000;

	if (OLD_VI_V_SYNC_REG != memory->vi_regs.getVsync())
	{
		if (memory->vi_regs.getVsync() == 0)
		{
			VI_INTR_TIME = 500000;
		} 
		else 
		{
			VI_INTR_TIME = (memory->vi_regs.getVsync() + 1) * 1500;
			if ((memory->vi_regs.getVsync() % 1) != 0)
				VI_INTR_TIME -= 38;
		}
	}
	timers->ChangeTimer(ViTimer, timers->Timer + timers->NextTimer[ViTimer] + VI_INTR_TIME, Compare, Count);
	
	if ((VI_STATUS_REG & 0x10) != 0)
		ViFieldNumber = (ViFieldNumber == 0) ? 1 : 0;
	else
		ViFieldNumber = 0;
	
	memory->gfx->updateScreen();
}

void R4300i::init()
{
	int i = 0;
	reset();
	init_crc();

	while (running)
	{
		if (memory->check_intr)
		{
			check_interrupt();
			memory->check_intr = false;
			if (interrupt_detected)
			{
				trigger_intr_exception();
				interrupt_detected = false;
			}
		}
		++Count;
		if ((pc & 0xFFFFFFFF) == 0x80322DF0)
			++i;
		decode(memory->read<word>(pc));
//		if (timers->Timer < 0) 
//			TimerDone();
	}
}
