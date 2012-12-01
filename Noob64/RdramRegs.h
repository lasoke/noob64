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

#define RDRAM_REGS_SEG_BEG		0x03F00000
#define RDRAM_REGS_SEG_END		0x03FFFFFF

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
//** RDRAM Registers														**
//****************************************************************************

class RDRAM_REGS : public MEM_SEG
{
public:
	RDRAM_REGS();

	inline word getConfig();
	inline void setConfig(word);
	inline word getDeviceId();
	inline void setDeviceId(word);
	inline word getDelay();
	inline void setDelay(word);
	inline word getMode();
	inline void setMode(word);
	inline word getRefInterval();
	inline void setRefInterval(word);
	inline word getRefRow();
	inline void setRefRow(word);
	inline word getRasInterval();
	inline void setRasInterval(word);
	inline word getMinInterval();
	inline void setMinInterval(word);
	inline word getAddrSelect();
	inline void setAddrSelect(word);
	inline word getDeviceManuf();
	inline void setDeviceManuf(word);

private:
	struct {
		word config;
		word device_id;
		word delay;
		word mode;
		word ref_interval;
		word ref_row;
		word ras_interval;
		word min_interval;
		word addr_select;
		word device_manuf;
		byte unknown[0xFFFD8];
	} data;
};