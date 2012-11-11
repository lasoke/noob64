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

#pragma once

#include "Rom.h"

inline word ROM::getClock()						{ return header->clock;	}
inline word ROM::getPc()						{ return header->pc; }
inline word ROM::getRelease()					{ return header->release; }
inline word ROM::getCRC1()						{ return header->crc1; }
inline word ROM::getCRC2()						{ return header->crc2; }
inline string ROM::getName()
{
	string s = "";
	for(int i = 0; i < sizeof(header->name); i++)
		s += header->name[i];
	return s;
}
inline word ROM::getManufacturer()				{ return header->manufacturer; }
inline hword ROM::getCartridge()				{ return header->cartridge; }
inline hword ROM::getCountry()					{ return header->country; }
