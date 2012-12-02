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

	void start();						// Starts the Nintendo 64 - starts the CPU
	void setRSP(RSP*);					// Sets and initializes the RSP plugin
	void setGFX(GFX*);					// Sets and initializes the GFX plugin

	void run_rsp(void);					// Runs the RSP to perform a task
	void refresh_screen(void);			// Refreshs the screen. Called when the video timer is done.
	void update_current_halfLine(void);	// Updates the current halfline of the video plugin

	void dma_pi_write(void);			// DMA write to a PI register
	void dma_pi_read(void);				// DMA read to a PI register
	void dma_si_write(void);			// DMA write to a SI register
	void dma_si_read(void);				// DMA read to a SI register
	void dma_sp_write(void);			// DMA write to a SP register
	void dma_sp_read(void);				// DMA read to a SP register

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

	inline word			getViFieldNumber(void) const;
	inline void			setViFieldNumber(word);
	inline word			getHalfline(void) const;

private:
	R4300i				&cpu;			// Reference of the CPU
	ROM					&rom;			// Reference of the ROM
	RDRAM				&rdram;			// Reference of the RDRAM
	RDRAM_REGS			&rdram_regs;	// Reference of the RDRAM registers
	SP					&sp;			// Reference of the Signal Processor registers
	DPC					&dpc;			// Reference of the DP Command registers
	DPS					&dps;			// Reference of the DP Span registers
	MI					&mi;			// Reference of the MIPS Interface registers
	VI					&vi;			// Reference of the Video Interface registers
	AI					&ai;			// Reference of the Audio Interface registers
	PI					&pi;			// Reference of the Peripheral Interface registers
	RI					&ri;			// Reference of the RDRAM Interface registers
	SI					&si;			// Reference of the Sound Interface registers
	PIF_ROM				&pif_rom;		// Reference of the PIF ROM
	PIF_RAM				&pif_ram;		// Reference of the PIF RAM

	RSP					*rsp;			// Pointer to the RSP plugin
	GFX					*gfx;			// Pointer to the GFX plugin

	byte				SRAM[0x8000];	// RCP' Static RAM
	word				halfline;		// Refers to a vertical line with respect to interlaced video modes
	word				vi_field_number;//
};

