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

	ROM*		RCP::rom		= 0;
	RDRAM*		RCP::rdram		= new RDRAM();
	RDRAM_REGS* RCP::rdram_regs = new RDRAM_REGS();
	SP*			RCP::sp			= new SP();
	DPC*		RCP::dpc		= new DPC();
	DPS*		RCP::dps		= new DPS();
	MI*			RCP::mi			= new MI();
	VI*			RCP::vi			= new VI();
	AI*			RCP::ai			= new AI();
	PI*			RCP::pi			= new PI();
	RI*			RCP::ri			= new RI();
	SI*			RCP::si			= new SI();
	PIF_ROM*	RCP::pif_rom	= new PIF_ROM();
	PIF_RAM*	RCP::pif_ram	= new PIF_RAM();

	word		RCP::vi_field_number = 0;
	byte		RCP::SRAM[0x8000] = {0};

//****************************************************************************
//** RCP																	**
//****************************************************************************

void RCP::start()
{
	memset(SRAM, 0, sizeof(SRAM));
	vi_field_number	= 0;
	R4300i::start();
}

void RCP::setROM(ROM* r)
{
	rom = r;
}

void RCP::run_rsp(void) 
{
	if (sp->getStatus() & SP_STATUS_HALT || sp->getStatus() & SP_STATUS_BROKE)
		return;
	word task = *(word*)(MMU::get(SP_DMEM + 0xFC0));
	if (task == 1 && (dpc->getStatus() & DPC_STATUS_FREEZE)) 
		return;
	word * rdram_tmp = (word*)(*rdram)[RDRAM_SEG_BEG];
	for (int i = 0; i < (0x800000 / 4); i++)
	{
		rdram_tmp[i] = type_to_binary<word>(rdram_tmp[i]);
	}
	RSP::doRspCycles(100);
	for (int i = 0; i < (0x800000 / 4); i++)
	{
		rdram_tmp[i] = binary_to_type<word>(rdram_tmp[i]);
	}
}

static word delay = 0;

void RCP::refresh_screen()
{
	GFX::updateScreen();
	delay = !vi->getVsync() ? 500000 : (vi->getVsync() + 1) * 1500;
	if (vi->getVsync() && vi->getVsync() % 1)
		delay -= 38;

	TimerHandler::change_timer(VI_TIMER, TimerHandler::getTimer() + TimerHandler::getNextTimer(VI_TIMER) + delay);
	vi_field_number = vi->getStatus() & 0x40 ? 1 - vi_field_number : 0;
}

//****************************************************************************
//** SEGMENTS																**
//****************************************************************************

#define INIT()						\
	memset(&data, 0, sizeof(data));	\
	ptr = (char*) &data;

MEM_SEG::MEM_SEG(word b, word e) : ptr(0), begining(b), end(e)				{}
MEM_SEG::~MEM_SEG()															{}
RDRAM::RDRAM() : MEM_SEG(RDRAM_SEG_BEG, RDRAM_SEG_END)						{ INIT() }
RDRAM_REGS::RDRAM_REGS() : MEM_SEG(RDRAM_REGS_SEG_BEG, RDRAM_REGS_SEG_END)	{ INIT() }
SP::SP() : MEM_SEG(SP_SEG_BEG, SP_SEG_END)									{ INIT() }
DPC::DPC() : MEM_SEG(DPC_SEG_BEG, DPC_SEG_END)								{ INIT() }
DPS::DPS() : MEM_SEG(DPS_SEG_BEG, DPS_SEG_END)								{ INIT() }
MI::MI() : MEM_SEG(MI_SEG_BEG, MI_SEG_END)									{ INIT() }
VI::VI() : MEM_SEG(VI_SEG_BEG, VI_SEG_END)									{ INIT() }
AI::AI() : MEM_SEG(AI_SEG_BEG, AI_SEG_END)									{ INIT() }
PI::PI() : MEM_SEG(PI_SEG_BEG, PI_SEG_END)									{ INIT() }
RI::RI() : MEM_SEG(RI_SEG_BEG, RI_SEG_END)									{ INIT() }
SI::SI() : MEM_SEG(SI_SEG_BEG, SI_SEG_END)									{ INIT() }
PIF_ROM::PIF_ROM() : MEM_SEG(PIF_ROM_SEG_BEG, PIF_ROM_SEG_END)				{ INIT() }
PIF_RAM::PIF_RAM() : MEM_SEG(PIF_RAM_SEG_BEG, PIF_RAM_SEG_END)				{ INIT() }

char* MEM_SEG::operator[] (const word address) const
{
	return ptr + address - begining;
}

