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

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

#include "Noob64.h"
#include "Rcp.h"
#include "Rcp.hxx"
#include "Mmu.h"
#include "Mmu.hxx"
#include "Rom.h"
#include "Rom.hxx"
#include "Rdram.h"
#include "RdramRegs.h"
#include "RdramRegs.hxx"
#include "Sp.h"
#include "Sp.hxx"
#include "Dpc.h"
#include "Dpc.hxx"
#include "Dps.h"
#include "Dps.hxx"
#include "Ai.h"
#include "Ai.hxx"
#include "Mi.h"
#include "Mi.hxx"
#include "Vi.h"
#include "Vi.hxx"
#include "Pi.h"
#include "Pi.hxx"
#include "Ri.h"
#include "Ri.hxx"
#include "Si.h"
#include "Si.hxx"
#include "PifRom.h"
#include "PifRam.h"
#include "Instruction.h"
#include "Instruction.hxx"
#include "Exception.h"
#include "Helper.h"
#include "Helper.hxx"
#include "Tlb.h"
#include "TimerHandler.h"
#include "R4300i.h"
#include "R4300i.hxx"
#include "Plugin.h"
#include "Rsp.h"
#include "Gfx.h"