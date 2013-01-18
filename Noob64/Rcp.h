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

/*
 * The Rcp files contains the functions, macro and structure to represente
 * and handle every interaction between the R4300i and the RCP::
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
	//RCP(ROM* rom);

	void static start();						// Starts the Nintendo 64 - starts the CPU
	void static setROM(ROM*);					// Sets and initializes the ROM

	void static run_rsp(void);					// Runs the RSP to perform a task
	void static refresh_screen(void);			// Refreshs the screen. Called when the video timer is done.

	void static dma_pi_write(void);				// DMA write to a PI register
	void static dma_pi_read(void);				// DMA read to a PI register
	void static dma_si_write(void);				// DMA write to a SI register
	void static dma_si_read(void);				// DMA read to a SI register
	void static dma_sp_write(void);				// DMA write to a SP register
	void static dma_sp_read(void);				// DMA read to a SP register

	static inline RDRAM*		getRDRAM(void);
	static inline RDRAM_REGS*	getRdramRegs(void);
	static inline SP*			getSP(void);
	static inline DPC*			getDPC(void);
	static inline DPS*			getDPS(void);
	static inline MI*			getMI(void);
	static inline VI*			getVI(void);
	static inline AI*			getAI(void);
	static inline PI*			getPI(void);
	static inline RI*			getRI(void);
	static inline SI*			getSI(void);
	static inline PIF_ROM*		getPifRom(void);
	static inline PIF_RAM*		getPifRam(void);

	static inline ROM*			getROM(void);

	static inline word			getViFieldNumber(void);
	static inline void			setViFieldNumber(word);

private:
	static RDRAM		*rdram;			// Pointer to the RDRAM
	static RDRAM_REGS	*rdram_regs;	// Pointer to the RDRAM registers
	static SP			*sp;			// Pointer to the Signal Processor registers
	static DPC			*dpc;			// Pointer to the DP Command registers
	static DPS			*dps;			// Pointer to the DP Span registers
	static MI			*mi;			// Pointer to the MIPS Interface registers
	static VI			*vi;			// Pointer to the Video Interface registers
	static AI			*ai;			// Pointer to the Audio Interface registers
	static PI			*pi;			// Pointer to the Peripheral Interface registers
	static RI			*ri;			// Pointer to the RDRAM Interface registers
	static SI			*si;			// Pointer to the Sound Interface registers
	static PIF_ROM		*pif_rom;		// Pointer to the PIF ROM
	static PIF_RAM		*pif_ram;		// Pointer to the PIF RAM
	static ROM			*rom;			// Pointer to the ROM

	static byte			SRAM[0x8000];	// RCP' Static RAM
	static word			vi_field_number;//
};

