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

#define RDRAM_SEG_BEG		0x00000000
#define RDRAM_SEG_END			0x03EFFFFF

#define RDRAM_CONFIG_REG		0x03F00000
#define RDRAM_DEVICE_ID_REG     0x03F00004
#define RDRAM_DELAY_REG			0x03F00008
#define RDRAM_MODE_REG			0x03F0000C
#define RDRAM_REF_INTERVAL_REG	0x03F00010
#define RDRAM_REF_ROW_REG		0x03F00014
#define RDRAM_RAS_INTERVAL_REG	0x03F00018
#define RDRAM_MIN_INTERVAL_REG	0x03F0001C
#define RDRAM_ADDR_SELECT_REG	0x03F00020
#define RDRAM_DEVICE_MANUF_REG	0x03F00024

//****************************************************************************
//** RDRAM																	**
//****************************************************************************


class RDRAM : public MEM_SEG
{
public:
	RDRAM();
private:
	struct {
		byte ram[0x800000];
	} data;
};