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

#define _CRT_SECURE_NO_WARNINGS
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
#include <Commctrl.h>

#include "Noob64.h"
#include "Commctrl.h"
#include "Helper.h"
#include "Rcp.h"
#include "Plugin.h"
#include "Rsp.h"
#include "Gfx.h"
#include "Audio.h"
#include "Mmu.h"
#include "Instruction.h"
#include "Exception.h"
#include "TimerHandler.h"
#include "R4300i.h"
#include "Rdram.h"
#include "RdramRegs.h"
#include "Sp.h"
#include "Dpc.h"
#include "Dps.h"
#include "Mi.h"
#include "Vi.h"
#include "Ai.h"
#include "Pi.h"
#include "Ri.h"
#include "Si.h"
#include "Rom.h"
#include "PifRom.h"
#include "PifRam.h"

#include "Helper.hxx"
#include "RCP.hxx"
#include "Mmu.hxx"
#include "Instruction.hxx"
#include "TimerHandler.hxx"
#include "R4300i.hxx"
#include "RdramRegs.hxx"
#include "Sp.hxx"
#include "Dpc.hxx"
#include "Dps.hxx"
#include "Mi.hxx"
#include "Vi.hxx"
#include "Ai.hxx"
#include "Pi.hxx"
#include "Ri.hxx"
#include "Si.hxx"
#include "Rom.hxx"
#include "Controller.h"
