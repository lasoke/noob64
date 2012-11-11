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

#include "Rcp.h"

#define DPS_SEG_BEGINING		0x04200000
#define DPS_SEG_END				0x042FFFFF

#define DPS_TBIST_REG			0x04200000
#define DPS_TEST_MODE_REG		0x04200004
#define DPS_BUFTEST_ADDR_REG	0x04200008
#define DPS_BUFTEST_DATA_REG	0x0420000C

//****************************************************************************
//** DP Span Registers														**
//****************************************************************************

class DPS : public MEM_SEG
{
public:
	DPS();

	inline word getTbist();
	inline void setTbist(word);
	inline word getTestMode();
	inline void setTestMode(word);
	inline word getBufTestAddr();
	inline void setBufTestAddr(word);
	inline word getBufTestData();
	inline void setBufTestData(word);

private:
	struct	{
		word tbist;
		word test_mode;
		word buftest_addr;
		word buftest_data;
		byte unused[0xFFFF0];
	} data;
};