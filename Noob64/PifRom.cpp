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

void n64_cic_nus_6105(char chl[], char rsp[], int len)
{
	static char lut0[0x10] = {
		0x4, 0x7, 0xA, 0x7, 0xE, 0x5, 0xE, 0x1, 
		0xC, 0xF, 0x8, 0xF, 0x6, 0x3, 0x6, 0x9
	};
	static char lut1[0x10] = {
		0x4, 0x1, 0xA, 0x7, 0xE, 0x5, 0xE, 0x1, 
		0xC, 0x9, 0x8, 0x5, 0x6, 0x3, 0xC, 0x9
	};
	char key, *lut;
	int i, sgn, mag, mod;

	for (key = 0xB, lut = lut0, i = 0; i < len; i++) {
		rsp[i] = (key + 5 * chl[i]) & 0xF;
		key = lut[rsp[i]];
		sgn = (rsp[i] >> 3) & 0x1;
		mag = ((sgn == 1) ? ~rsp[i] : rsp[i]) & 0x7;
		mod = (mag % 3 == 1) ? sgn : 1 - sgn;
		if (lut == lut1 && (rsp[i] == 0x1 || rsp[i] == 0x9))
			mod = 1;
		if (lut == lut1 && (rsp[i] == 0xB || rsp[i] == 0xE))
			mod = 0;
		lut = (mod == 1) ? lut1 : lut0;
	}
}
