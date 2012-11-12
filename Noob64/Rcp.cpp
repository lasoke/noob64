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

//****************************************************************************
//** RCP																	**
//****************************************************************************

RCP::RCP(ROM* rom) :
	cpu			(*new R4300i(this)),
	rom			(*rom),
	rdram		(*new RDRAM()),
	rdram_regs	(*new RDRAM_REGS()),
	sp			(*new SP()),
	dpc			(*new DPC()),
	dps			(*new DPS()),
	mi			(*new MI()),
	vi			(*new VI()),
	ai			(*new AI()),
	pi			(*new PI()),
	ri			(*new RI()),
	si			(*new SI()),
	pif_rom		(*new PIF_ROM()),
	pif_ram		(*new PIF_RAM())
{
	memset(SRAM, 0, sizeof(SRAM));
	cic_chip = 0;
	check_intr = false;
}

void RCP::start()
{
	cpu.start();
}

void RCP::setRSP(RSP* r)
{
	rsp = r;
	rsp->init(this);
}
void RCP::setGFX(GFX* g)
{
	gfx = g;
	gfx->init(this);
}

void RCP::run_rsp(void) 
{
	if (sp.getStatus() & SP_STATUS_HALT || sp.getStatus() & SP_STATUS_BROKE)
		return;

	word task = *(word*)(cpu.getMMU()[SP_DMEM + 0xFC0]);

	if (task == 1 && (dpc.getStatus() & DPC_STATUS_FREEZE)) 
		return;
                        
	if (task == 1)
		cpu.incDList();
	else if (task == 2)
		cpu.incAList();

	rsp->doRspCycles(100);

#	ifdef CFB_READ	
		if (VI_ORIGIN_REG > 0x280) 
			SetFrameBuffer(VI_ORIGIN_REG, (word)(VI_WIDTH_REG * (VI_WIDTH_REG *.75)));
#	endif
}


void RCP::refresh_screen()
{
	static word OLD_VI_V_SYNC_REG = 0, VI_INTR_TIME = 500000;

	if (OLD_VI_V_SYNC_REG != vi.getVsync())
	{
		if (!vi.getVsync())
			VI_INTR_TIME = 500000;
		else 
		{
			VI_INTR_TIME = (vi.getVsync() + 1) * 1500;
			if (vi.getVsync() % 1)
				VI_INTR_TIME -= 38;
		}
	}

	TimerHandler& t = cpu.getTimerHandler();
	t.change_timer(VI_TIMER, t.timer + t.next_timer[VI_TIMER] + VI_INTR_TIME, cpu.getCop0(COMPARE), cpu.getCop0(COUNT));
	
	if ((VI_STATUS_REG & 0x10) != 0)
		cpu.setViFieldNumber(!cpu.getViFieldNumber() ? 1 : 0);
	else
		cpu.setViFieldNumber(0);

	gfx->updateScreen();
}


void RCP::updateCurrentHalfLine ()
{
	TimerHandler& t = cpu.getTimerHandler();
    if (t.timer < 0) { 
		halfline = 0;
		return;
	}

	halfline = (t.timer / 1500);
	halfline &= ~1;
	halfline += cpu.getViFieldNumber();
}

//****************************************************************************
//** SEGMENTS																**
//****************************************************************************

#define INIT()						\
	memset(&data, 0, sizeof(data));	\
	ptr = (char*) &data;

MEM_SEG::MEM_SEG(word b, word e) : ptr(0), begining(b), end(e)					{}
MEM_SEG::~MEM_SEG()																{}
RDRAM::RDRAM() : MEM_SEG(RDRAM_SEG_BEGINING, RDRAM_SEG_END)						{ INIT() }
RDRAM_REGS::RDRAM_REGS() : MEM_SEG(RDRAM_REGS_SEG_BEGINING, RDRAM_REGS_SEG_END) { INIT() }
SP::SP() : MEM_SEG(SP_SEG_BEGINING, SP_SEG_END)									{ INIT() }
DPC::DPC() : MEM_SEG(DPC_SEG_BEGINING, DPC_SEG_END)								{ INIT() }
DPS::DPS() : MEM_SEG(DPS_SEG_BEGINING, DPS_SEG_END)								{ INIT() }
MI::MI() : MEM_SEG(MI_SEG_BEGINING, MI_SEG_END)									{ INIT() }
VI::VI() : MEM_SEG(VI_SEG_BEGINING, VI_SEG_END)									{ INIT() }
AI::AI() : MEM_SEG(AI_SEG_BEGINING, AI_SEG_END)									{ INIT() }
PI::PI() : MEM_SEG(PI_SEG_BEGINING, PI_SEG_END)									{ INIT() }
RI::RI() : MEM_SEG(RI_SEG_BEGINING, RI_SEG_END)									{ INIT() }
SI::SI() : MEM_SEG(SI_SEG_BEGINING, SI_SEG_END)									{ INIT() }
PIF_ROM::PIF_ROM() : MEM_SEG(PIF_ROM_SEG_BEGINING, PIF_ROM_SEG_END)				{ INIT() }
PIF_RAM::PIF_RAM() : MEM_SEG(PIF_RAM_SEG_BEGINING, PIF_RAM_SEG_END)				{ INIT() }

char* MEM_SEG::operator[] (const word address) const
{
	return ptr + address - begining;
}

