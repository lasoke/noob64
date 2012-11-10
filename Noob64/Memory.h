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

#define KSEG0					0x80000000
#define KSEG1					0xA0000000
#define KSEG2					0xC0000000
#define KSEG3					0xE0000000

typedef unsigned __int8			byte;
typedef unsigned __int16		hword;
typedef unsigned __int32		word;
typedef unsigned __int64		dword;

typedef __int8					sbyte;
typedef __int16					shword;
typedef __int32					sword;
typedef __int64					sdword;

typedef float					s; // Single-Precision	Floating-Point Format:	[31:sign;30-23-exponent;22-0:fraction]
typedef double					d; // Double-Precision	Floating-Point Format:	[63:sign;62-52:exponent;51-0:fraction]
typedef long					w; // Word				Fixed-Point Format:		[31:sign;30-0:int]
typedef long long int			l; // Longword			Fixed-Point Format:		[63:sign;62-0:int]

class ROM;
class RDRAM;
class RDRAM_REGS;
class SP_REGS;
class DPC_REGS;
class DPS_REGS;
class MI_REGS;
class VI_REGS;
class AI_REGS;
class PI_REGS;
class RI_REGS;
class SI_REGS;
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
	const char *ptr;
	inline bool contains(word address) const;
	void* operator[] (const word address) const;
protected:
	const word begining;
	const word end;
};

//****************************************************************************
//** MEMORY					                                                **
//****************************************************************************

class MEMORY
{
public:
	MEMORY(ROM* rom);

	ROM			&rom;
	RDRAM		&rdram;
	RDRAM_REGS	&rdram_regs;
	SP_REGS		&sp_regs;
	DPC_REGS	&dpc_regs;
	DPS_REGS	&dps_regs;
	MI_REGS		&mi_regs;
	VI_REGS		&vi_regs;
	AI_REGS		&ai_regs;
	PI_REGS		&pi_regs;
	RI_REGS		&ri_regs;
	SI_REGS		&si_regs;
	PIF_ROM		&pif_rom;
	PIF_RAM		&pif_ram;

	R4300i		*cpu;
	RSP			*rsp;
	GFX			*gfx;

	void* operator[] (const word address);

	template <typename Type> inline Type read(word address);
	template <typename Type> inline void write(Type data, word address);

	inline bool isCheckInterrupt() const;
	inline void setCheckInterrupt(bool);

	void dma_pi_write();
	void dma_pi_read();
	void dma_si_write();
	void dma_si_read();
	void dma_sp_write();
	void dma_sp_read();

private:
	inline void* virtual_to_physical(word address);
	inline bool read_from_register(word *data, word address);
	inline bool write_in_register(word data, word address);
	inline void checkDMA(word address);

	byte		SRAM[0x8000];
	word		cic_chip;
	bool		check_intr;
};

bool is_address_defined(word address);
