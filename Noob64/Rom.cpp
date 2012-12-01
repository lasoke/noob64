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

ROM::ROM(string filename) : MEM_SEG(ROM_SEG_BEG, ROM_SEG_END)
{
	file.open(filename, ios::ate | ios::in | ios::binary);
	if (!file.is_open())
		throw ROM_FAILED_TO_LOAD;

	int size = (int) file.tellg();
	data = (char*) malloc(size);
	file.seekg (0, ios::beg);
    file.read(data, size);
	file.close();
	ptr = data;
	header = (ROM_HEADER*) data;

	word type = ((word*) data)[0];
	if (type == 0x40123780)
		; // BIG ENDIAN
	else if (type == 0x12408037)
	{
		// MIDDLE ENDIAN
		for (int i = 0; i < size - 1; i += 2)
		{
			char temp = data[i];
			data[i] = data[i+1];
			data[i+1] = temp;
		}
	}
	else throw ROM_UNKNOWN_FORMAT;
}

ROM::~ROM()
{
	delete[] data;
}




