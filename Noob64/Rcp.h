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
 * chwing money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#pragma once

class ROM;
class RDRAM;
class RDRAM_REGS;
class SP;
class DPC;
class DPS;
class MI;
class VI;
class AI;
class PI;
class RI;
class SI;
class PIF_ROM;
class PIF_RAM;
class R4300i;
class GFX;
class RSP;

//****************************************************************************
//** MEMORY SEGMENT															**
//****************************************************************************

class MEM_SEG
{
public:
	MEM_SEG(word, word);
	virtual ~MEM_SEG() = 0;
	inline bool contains(word address) const;
	char* operator[] (const word address) const;
protected:
	char* ptr;
	const word begining;
	const word end;
};

//****************************************************************************
//** REALITY CO-PROCESSOR					                                **
//****************************************************************************

class RCP
{
public:
	RCP(ROM* rom);

	void start();
	void setRSP(RSP*);
	void setGFX(GFX*);

	void dma_pi_write(void);
	void dma_pi_read(void);
	void dma_si_write(void);
	void dma_si_read(void);
	void dma_sp_write(void);
	void dma_sp_read(void);

	void run(void);
	void refresh_screen(void);	// Refreshs the screen when the vi timer is done
	inline bool isCheckInterrupt(void) const;
	inline void setCheckInterrupt(bool);

	inline R4300i&		getCPU(void) const;
	inline ROM&			getROM(void) const;
	inline RDRAM&		getRDRAM(void) const;
	inline RDRAM_REGS&	getRdramRegs(void) const;
	inline SP&			getSP(void) const;
	inline DPC&			getDPC(void) const;
	inline DPS&			getDPS(void) const;
	inline MI&			getMI(void) const;
	inline VI&			getVI(void) const;
	inline AI&			getAI(void) const;
	inline PI&			getPI(void) const;
	inline RI&			getRI(void) const;
	inline SI&			getSI(void) const;
	inline PIF_ROM&		getPifRom(void) const;
	inline PIF_RAM&		getPifRam(void) const;
	inline RSP*			getRSP(void) const;
	inline GFX*			getGFX(void) const;

private:
	R4300i		&cpu;
	ROM			&rom;
	RDRAM		&rdram;
	RDRAM_REGS	&rdram_regs;
	SP			&sp;
	DPC			&dpc;
	DPS			&dps;
	MI			&mi;
	VI			&vi;
	AI			&ai;
	PI			&pi;
	RI			&ri;
	SI			&si;
	PIF_ROM		&pif_rom;
	PIF_RAM		&pif_ram;

	RSP			*rsp;
	GFX			*gfx;

	byte		SRAM[0x8000];
	word		cic_chip;
	bool		check_intr;

	inline void checkDMA(word address);
};

