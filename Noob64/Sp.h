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

#include "Memory.h"

#define SP_SEG_BEGINING			0x04000000
#define SP_SEG_END				0x040FFFFF

#define SP_DMEM					0x04000000
#define SP_IMEM					0x04001000
#define SP_MEM_ADDR_REG			0x04040000
#define SP_DRAM_ADDR_REG        0x04040004
#define SP_RD_LEN_REG			0x04040008
#define SP_WR_LEN_REG			0x0404000C
#define SP_STATUS_REG			0x04040010
#define SP_DMA_FULL_REG			0x04040014
#define SP_DMA_BUSY_REG			0x04040018
#define SP_SEMAPHORE_REG		0x0404001C
#define SP_PC_REG				0x04080000
#define SP_IBIST_REG			0x04080004

#define SP_CLR_HALT				0x00001
#define SP_SET_HALT				0x00002
#define SP_CLR_BROKE			0x00004
#define SP_CLR_INTR				0x00008
#define SP_SET_INTR				0x00010
#define SP_CLR_SSTEP			0x00020
#define SP_SET_SSTEP			0x00040
#define SP_CLR_INTR_BREAK		0x00080
#define SP_SET_INTR_BREAK		0x00100
#define SP_CLR_SIG0				0x00200
#define SP_SET_SIG0				0x00400
#define SP_CLR_SIG1				0x00800
#define SP_SET_SIG1				0x01000
#define SP_CLR_SIG2				0x02000
#define SP_SET_SIG2				0x04000
#define SP_CLR_SIG3				0x08000
#define SP_SET_SIG3				0x10000
#define SP_CLR_SIG4				0x20000
#define SP_SET_SIG4				0x40000	
#define SP_CLR_SIG5				0x80000
#define SP_SET_SIG5				0x100000
#define SP_CLR_SIG6				0x200000
#define SP_SET_SIG6				0x400000
#define SP_CLR_SIG7				0x800000
#define SP_SET_SIG7				0x1000000

#define SP_STATUS_HALT			0x001
#define SP_STATUS_BROKE			0x002
#define SP_STATUS_DMA_BUSY		0x004
#define SP_STATUS_DMA_FULL		0x008
#define SP_STATUS_IO_FULL		0x010
#define SP_STATUS_SSTEP			0x020
#define SP_STATUS_INTR_BREAK	0x040
#define SP_STATUS_SIG0			0x080
#define SP_STATUS_SIG1			0x100
#define SP_STATUS_SIG2			0x200
#define SP_STATUS_SIG3			0x400
#define SP_STATUS_SIG4			0x800
#define SP_STATUS_SIG5			0x1000
#define SP_STATUS_SIG6			0x2000
#define SP_STATUS_SIG7			0x4000

//****************************************************************************
//** SP Registers															**
//****************************************************************************

class SP_REGS : public MEM_SEG
{
public:
	SP_REGS();

	//contains the instruction of the RSP
	inline byte *getDmem();
	inline byte *getImem();

	inline word getMemAddr();
	inline void setMemAddr(word);
	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getRdLen();
	inline void setRdLen(word);
	inline word getWrLen();
	inline void setWrLen(word);
	inline word getStatus();
	inline void setStatus(word);
	inline void setSpecialStatus(word);
	inline word getDmaFull();
	inline void setDmaFull(word);
	inline word getDmaBusy();
	inline void setDmaBusy(word);
	inline word getSemaphore();
	inline void setSemaphore(word);
	inline void setSpecialSemaphore(word);
	inline word getPc();
	inline void setPc(word);
	inline word getIbist();
	inline void setIbist(word);
	
private:
	struct {
		byte dmem[0x1000];
		byte imem[0x1000];
		byte unused[0x3E000];
		word mem_addr;
		word dram_addr;
		word rd_len;
		word wr_len;
		word status;
		word dma_full;
		word dma_busy;
		word semaphore;
		byte unused2[0x3FFE0];
		word pc;
		word ibist;
		byte unused3[0x7FFF8];
	} data;
};