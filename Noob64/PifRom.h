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

//****************************************************************************
//** PIF ROM																**
//****************************************************************************

#define PIF_ROM_SEG_BEG		0x1FC00000
#define PIF_ROM_SEG_END		0x1FC007BF

class PIF_ROM : public MEM_SEG
{
public:
	PIF_ROM();
private:
	struct {
		byte prom[0x7C0];
	} data;
};

void n64_cic_nus_6105(char chl[], char rsp[], int len);
