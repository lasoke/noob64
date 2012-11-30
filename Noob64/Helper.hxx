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

#include "Helper.h"

template <typename Type>
inline Type binary_to_type(Type toSwap)
{
	Type result = 0;
	for (unsigned int i = 0; i < sizeof(result); i++)
		result = (result << 8) + ((byte*) &toSwap)[i];
	return result;
}

template <typename Type>
inline Type type_to_binary(Type data)
{
	byte *tab = (byte*) &data;
	byte b;
	unsigned size = sizeof(data);
	for (unsigned int i = 0; i < size / 2; i++)
	{
		b = tab[i];
		tab[i] = tab[size-1-i];
		tab[size-1-i] = b;
	}
	return data;
}