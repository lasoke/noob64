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

#define ROM_HEADER_SIZE			0x1000
#define ROM_BOOT_CODE_SIZE		1008

#define ROM_SEG_BEG				0x10000000
#define ROM_SEG_END				0x1F39FFFF

#define INIT_BSD_DOM1_LAT_REG	0x10000000
#define INIT_BSD_DOM1_PWD_REG	0x10000001
#define INIT_BSD_DOM1_PGS_REG	0x10000002
#define INIT_BSD_DOM1_RLS_REG	0x10000003
#define CLOCK_RATE				0x10000004
#define BOOT_ADDRESS_OFFSET		0x10000008
#define RELEASE_OFFSET			0x1000000C
#define CRC1					0x10000010
#define CRC2					0x10000014
#define IMAGE_NAME				0x10000020
#define MANUFACTURER_ID			0x1000003B
#define CARTRIDGE_ID			0x1000003C
#define COUNTRY_CODE			0x1000003E

//****************************************************************************
//** ROM																	**
//****************************************************************************

class ROM : public MEM_SEG
{
public:
	ROM(string);
	~ROM();

	inline word		getClock();
	inline word		getPc();
	inline word		getRelease();
	inline word		getCRC1();
	inline word		getCRC2();
	inline string	getName();
	inline word		getManufacturer();
	inline hword	getCartridge();
	inline hword	getCountry();

private:
	ifstream		file;
	char			*data;

	typedef struct {
	   byte			pi_bsd_dom1_lat;
	   byte			pi_bsd_dom1_pwd;
	   byte			pi_bsd_dom1_pgs;
	   byte			pi_bsd_dom1_rls;
	   word			clock;
	   word			pc;
	   word			release;
	   word			crc1;
	   word			crc2;
	   word			Unknown[2];
	   byte			name[20];
	   word			unknown;
	   word			manufacturer;
	   hword		cartridge;
	   hword		country;
	   word			bootcode[ROM_BOOT_CODE_SIZE];
	} ROM_HEADER;

	ROM_HEADER		*header;
};