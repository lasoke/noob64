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

class MMU
{
public:
	MMU(R4300i&, RCP&);
	~MMU(void);

	void* operator[] (const word address);
	template <typename Type> inline Type read(word address);
	template <typename Type> inline void write(Type data, word address);

private:
	R4300i	&cpu;
	RCP		&rcp;

	inline void* virtual_to_physical(word address);
	inline bool read_from_register(word *data, word address);
	inline bool write_in_register(word data, word address);
};

bool is_address_defined(word address);

