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

#define DPC_SEG_BEGINING		0x04100000
#define DPC_SEG_END				0x041FFFFF

#define DPC_START_REG			0x04100000
#define DPC_END_REG				0x04100004
#define DPC_CURRENT_REG			0x04100008
#define DPC_STATUS_REG			0x0410000C
#define DPC_CLOCK_REG			0x04100010
#define DPC_BUFBUSY_REG			0x04100014
#define DPC_PIPEBUSY_REG		0x04100018
#define DPC_TMEM_REG			0x0410001C

#define DPC_CLR_XBUS_DMEM_DMA		0x0001
#define DPC_SET_XBUS_DMEM_DMA		0x0002
#define DPC_CLR_FREEZE				0x0004
#define DPC_SET_FREEZE				0x0008
#define DPC_CLR_FLUSH				0x0010
#define DPC_SET_FLUSH				0x0020
#define DPC_CLR_TMEM_CTR			0x0040
#define DPC_CLR_PIPE_CTR			0x0080
#define DPC_CLR_CMD_CTR				0x0100
#define DPC_CLR_CLOCK_CTR			0x0200

#define DPC_STATUS_XBUS_DMEM_DMA	0x0001
#define DPC_STATUS_FREEZE			0x0002
#define DPC_STATUS_FLUSH			0x0004
#define DPC_STATUS_START_GCLK		0x0008
#define DPC_STATUS_TMEM_BUSY		0x0010
#define DPC_STATUS_PIPE_BUSY		0x0020
#define DPC_STATUS_CMD_BUSY			0x0040
#define DPC_STATUS_CBUF_READY		0x0080
#define DPC_STATUS_DMA_BUSY			0x0100
#define DPC_STATUS_END_VALID		0x0200
#define DPC_STATUS_START_VALID		0x0400

//****************************************************************************
//** DP Command Registers													**
//****************************************************************************

class DPC_REGS : public MEM_SEG
{
public:
	DPC_REGS();

	inline word getStart();
	inline void setStart(word);
	inline word getEnd();
	inline void setEnd(word);
	inline word getCurrent();
	inline void setCurrent(word);
	inline word getStatus();
	inline void setStatus(word);
	inline word getClock();
	inline void setClock(word);
	inline word getBufBusy();
	inline void setBufBusy(word);
	inline word getPipeBusy();
	inline void setPipeBusy(word);
	inline word getTmem();
	inline void setTmem(word);

private:
	struct {
		word start;
		word end;
		word current;
		word status;
		word clock;
		word bufbusy;
		word pipebusy;
		word tmem;
		byte unused[0xFFFE0];
	} data;
};