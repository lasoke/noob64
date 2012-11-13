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

R4300i::R4300i(RCP *r) :
		rcp(*r),
		mmu(*new MMU(*this, rcp)),
		timer_handler(*new TimerHandler())
		
{
}

void R4300i::reset()
{
	for (int i = 0; i < 32; i++)
	{
		r[i]				= (dword) 0;
		f[i]				= (dword) 0;
		cop0[i]				= (word)  0;
	}
	pc						= 0;
	hi						= 0;
	lo						= 0;
	fcr0					= 0;
	fcr31					= 0x01000800;
	ll						= false;

	delay_slot				= false;
	running					= true;
	cic_chip				= 0;
	interrupt_detected		= false;
	alist_counter			= 0;
	dlist_counter			= 0;

	mmu.reset();
	timer_handler.reset();
}

void R4300i::pif_init()
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
	r[20]	= 0x0000000000000001; // rom_info.tv_sys
	r[22]	= 0x000000000000003F; // rom_info.cic
	r[23]	= 0x0000000000000001;
	r[25]	= 0xFFFFFFFFD73F2993;
	r[29]	= 0xFFFFFFFFA4001FF0;
	r[31]	= 0xFFFFFFFFA4001554;
	
	Config	= 0x0006E463;
	Status	= 0x34000000;
	PRevID	= 0x00000B00;
	Random	= 0x0000001F;

	mmu.write<word>(0x02020202, MI_VERSION_REG);
	mmu.write<word>(0x00000041, SP_STATUS_REG);
	mmu.write<word>(0x00000088, DPC_STATUS_REG);
	mmu.write<word>(0x00000040, PI_BSD_DOM1_LAT_REG);
	mmu.write<word>(0x00000012, PI_BSD_DOM1_PWD_REG);
	mmu.write<word>(0x00000007, PI_BSD_DOM1_PGS_REG);
	mmu.write<word>(0x00000003, PI_BSD_DOM1_RLS_REG);

	fcr0 = 0x511;

	sdword CRC = 0;
	
	// Copies first 0x1000 bytes of ROM to first 0x1000 bytes of SP_MEM
	for(int i = 0; i < 0x1000; i++)
		mmu.write<byte>(*((byte*) mmu[ROM_SEG_BEGINING+i]), SP_SEG_BEGINING+i);
	// Sets PC right after the ROM header
	pc = 0xA4000040;

	mmu.write<word>(0xBDA807FC, 0x04001004);
	mmu.write<word>(0x3C0DBFC0, 0x04001000);
	mmu.write<word>(0x25AD07C0, 0x04001008);
	mmu.write<word>(0x31080080, 0x0400100C);
	mmu.write<word>(0x5500FFFC, 0x04001010);
	mmu.write<word>(0x3C0DBFC0, 0x04001014);
	mmu.write<word>(0x8DA80024, 0x04001018);
	mmu.write<word>(0x3C0BB000, 0x0400101C);
	mmu.write<word>(0x6886A9C1, 0x04001F94);
	mmu.write<word>(0x915F5B7E, 0x04001F90);

}

void R4300i::start()
{
	reset();
	pif_init();

	int i = 0;
	int j = -1;
	word content = 0;
	while (running)
	{
		content = mmu.read<word>(0x803359A8);
		if (rcp.isCheckInterrupt())
		{
			check_interrupt();
			rcp.setCheckInterrupt(false);
			if (interrupt_detected)
			{
				trigger_intr_exception();
				interrupt_detected = false;
			}
		}
		++Count;
		timer_handler.timer -= 2;
		if ((pc & 0xFFFFFFFF) == 0x80322DF0)
			++i;
		if (i >= 51 && (pc & 0xFFFFFFFF) == 0x8027F55C)
			j = i;
		if (j == i && ((pc & 0xFFFFFFFF) < 0x8027f500 || (pc & 0xFFFFFFFF) > 0x8027f574))
			j= i;
		decode(mmu.read<word>((word) pc));
		if (timer_handler.timer < 0)
			timer_done();
	}
}
