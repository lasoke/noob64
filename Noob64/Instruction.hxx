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

#include "Instruction.h"

inline dword extend_sign_word(dword d)
{
	return d & 0x80000000 ? d |= 0xFFFFFFFF00000000 : d &= 0xFFFFFFFF;
}
inline dword extend_sign_halfword(dword d)
{
	return d & 0x8000 ? d |= 0xFFFFFFFFFFFF0000 : d &= 0xFFFF;
}
inline dword extend_sign_byte(dword d)
{
	return d & 0x80 ? d |= 0xFFFFFFFFFFFFFF00 : d &= 0xFF;
}
inline int getOpCode(word instr)	{ return (instr & 0xfc000000) >> 26; }
inline int getRs(word instr)		{ return (instr & 0x3e00000) >> 21; }
inline int getRt(word instr)		{ return (instr & 0x1F0000) >> 16; }
inline int getRd(word instr)		{ return (instr & 0xF800) >> 11; }
inline int getSa(word instr)		{ return (instr & 0x7C0) >> 6; }
inline int getFunct(word instr)		{ return instr & 0x3F; }
inline int getImmediate(word instr)	{ return instr & 0xFFFF; }
inline int getTarget(word instr)	{ return instr & 0x3FFFFFF; }
inline int getCond(word instr)		{ return instr & 0xF; }
inline int getNd(word instr)		{ return (instr & 0x20000) >> 17; }
inline int getTf(word instr)		{ return (instr & 0x10000) >> 16; }
inline int getNdTf(word instr)		{ return (instr & 0x30000) >> 16; }