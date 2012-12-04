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
#include "Plugin.h"

bool			PLUGIN::loaded = false;
HINSTANCE		PLUGIN::hDLL = 0;
HWND			PLUGIN::hWnd = 0;
CLOSEDLL		PLUGIN::closeDLL_ = 0;
DLLABOUT		PLUGIN::dllAbout_ = 0;
DLLCONFIG		PLUGIN::dllConfig_ = 0;
DLLTEST			PLUGIN::dllTest_ = 0;
GETDLLINFO		PLUGIN::getDllInfo_ = 0;
ROMCLOSED		PLUGIN::romClosed_ = 0;
PLUGIN_INFO*	PLUGIN::plugin_info = 0;

bool PLUGIN::isLoaded(void)
{
	return loaded;
}

void PLUGIN::load(wstring filename, HWND h)
{
	if (!(hDLL = LoadLibrary(filename.c_str())))
		throw PLUGIN_FAILED_TO_LOAD;

	hWnd					= h;

	closeDLL_				= (CLOSEDLL) GetProcAddress(hDLL, "CloseDLL");
	dllAbout_				= (DLLABOUT) GetProcAddress(hDLL, "DllAbout");
	dllConfig_				= (DLLCONFIG) GetProcAddress(hDLL, "DllConfig");
	dllTest_				= (DLLTEST)	GetProcAddress(hDLL, "DllTest");
	getDllInfo_				= (GETDLLINFO) GetProcAddress(hDLL, "GetDllInfo");
	romClosed_				= (ROMCLOSED) GetProcAddress(hDLL, "RomClosed");

	plugin_info				= (PLUGIN_INFO*) malloc(sizeof(PLUGIN_INFO));
	getDllInfo_(plugin_info);
}

void PLUGIN::closeDLL()
{
	return closeDLL_();
}

void PLUGIN::dllAbout(HWND h)
{
	return dllAbout_(h);
}

void PLUGIN::dllConfig(HWND h)
{
	return dllConfig_(h);
}

void PLUGIN::dllTest(HWND h)
{
	return dllTest_(h);
}

void PLUGIN::romClosed()
{
	return romClosed_();
}

