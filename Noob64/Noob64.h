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

#include "resource.h"

using namespace std;

//#define DEBUG

// The time unit used by the Count register
// and the timer handler
#define	TIME_UNIT				1

typedef unsigned __int8			byte;
typedef unsigned __int16		hword;
typedef unsigned __int32		word;
typedef unsigned __int64		dword;

typedef __int8					sbyte;
typedef __int16					shword;
typedef __int32					sword;
typedef __int64					sdword;

typedef float					s; // Single-Precision	Floating-Point Format:	[31:sign;30-23-exponent;22-0:fraction]
typedef double					d; // Double-Precision	Floating-Point Format:	[63:sign;62-52:exponent;51-0:fraction]
typedef long					w; // Word				Fixed-Point Format:		[31:sign;30-0:int]
typedef long long int			l; // Longword			Fixed-Point Format:		[63:sign;62-0:int]

// The Noob64 exceptions
enum NOOB64_EXCEPTION
{
	PLUGIN_FAILED_TO_LOAD,	// Thrown when a plugin were unable to load
	PLUGIN_FAILED_TO_INIT,	// Thrown when a plugin failed to initialize
	ROM_FAILED_TO_LOAD,		// Thrown when a ROM failed to load
	ROM_UNKNOWN_FORMAT,		// Thrown when the ROM is corrupted
	VIRTUAL_ADDRESS_ERROR,	// Thrown when we try to access an unhandled virtual address
	TLB_NOT_HANDLED,		// Thrown when we try to access an unregister TLB address
	TIMER_BROKEN			// Thrown when there is a problem with the timer handler
};
