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

#define PLUGIN_TYPE_RSP				1
#define PLUGIN_TYPE_GFX				2
#define PLUGIN_TYPE_AUDIO			3
#define PLUGIN_TYPE_CONTROLLER		4

typedef struct {
	hword Version;        /* Should be set to 0x0101 */
	hword Type;           /* Set to PLUGIN_TYPE_RSP */
	char Name[100];      /* Name of the DLL */

	/* If DLL supports memory these memory options then set them to TRUE or FALSE
	   if it does not support it */
	bool NormalMemory;   /* a normal byte array */ 
	bool MemoryBswaped;  /* a normal byte array where the memory has been pre
	                          bswap on a dword (32 bits) boundry */
} PLUGIN_INFO;

typedef void (_cdecl* CLOSEDLL)(void);
typedef void (_cdecl* DLLABOUT)(HWND);
typedef void (_cdecl* DLLCONFIG)(HWND);
typedef void (_cdecl* DLLTEST)(HWND);
typedef void (_cdecl* GETDLLINFO)(PLUGIN_INFO*);
typedef void (_cdecl* ROMCLOSED)(void);

class PLUGIN
{
public:
	PLUGIN(wstring filename);
	~PLUGIN();

	void closeDLL();
	void dllAbout(HWND);
	void dllConfig(HWND);
	void dllTest(HWND);
	void romClosed();

protected:
	HINSTANCE				hDLL;

	CLOSEDLL				closeDLL_;
	DLLABOUT				dllAbout_;
	DLLCONFIG				dllConfig_;
	DLLTEST					dllTest_;
	GETDLLINFO				getDllInfo_;
	ROMCLOSED				romClosed_;

	PLUGIN_INFO				*plugin_info;
};

