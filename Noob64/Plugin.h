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

/*
 * The Plugin files contains the functions, macro and structure to generically 
 * represent a plugin.
 *
 */

#pragma once

#define PLUGIN_TYPE_RSP				1
#define PLUGIN_TYPE_GFX				2
#define PLUGIN_TYPE_AUDIO			3
#define PLUGIN_TYPE_CONTROLLER		4

/*
** The PLUGIN_INFO structure is common to every plugin
** and contains general info on it
*/
typedef struct {
	hword	version;        /* Should be set to 0x0101 */
	hword	type;           /* Set to PLUGIN_TYPE_RSP */
	char	name[100];      /* Name of the DLL */
	int		normalMemory;   /* a normal byte array */ 
	int		memoryBswaped;  /* a normal byte array where the memory has been pre
	                          bswap on a dword (32 bits) boundry */
} PLUGIN_INFO;

typedef void (__cdecl* CLOSEDLL)(void);
typedef void (__cdecl* DLLABOUT)(HWND);
typedef void (__cdecl* DLLCONFIG)(HWND);
typedef void (__cdecl* DLLTEST)(HWND);
typedef void (__cdecl* GETDLLINFO)(PLUGIN_INFO*);
typedef void (__cdecl* ROMCLOSED)(void);
typedef void (__cdecl* ROMOPEN)(void);
