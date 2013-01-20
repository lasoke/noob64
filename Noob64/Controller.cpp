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
#include "Controller.h"

bool						CONTROLLER::loaded = false;
HINSTANCE					CONTROLLER::hDLL = 0;
HWND						CONTROLLER::hWnd = 0;
CLOSEDLL					CONTROLLER::closeDLL_ = 0;
DLLABOUT					CONTROLLER::dllAbout_ = 0;
DLLCONFIG					CONTROLLER::dllConfig_ = 0;
DLLTEST						CONTROLLER::dllTest_ = 0;
GETDLLINFO					CONTROLLER::getDllInfo_ = 0;
ROMCLOSED					CONTROLLER::romClosed_ = 0;
PLUGIN_INFO*				CONTROLLER::plugin_info = 0;

ROMOPEN						CONTROLLER::romOpen_ = 0;
CONTROLLERCOMMAND			CONTROLLER::controllerCommand_ = 0;
INITIATECONTROLLERS			CONTROLLER::initiateControllers_ = 0;
GETKEYS						CONTROLLER::getKeys_ = 0;
READCONTROLLER				CONTROLLER::readController_ = 0;
WMKEYDOWN					CONTROLLER::wmKeyDown_ = 0;
WMKEYUP						CONTROLLER::wmKeyUp_ = 0;

CONTROL_INFO*				CONTROLLER::control_info = 0;
CONTROL						CONTROLLER::controllers[4];

void CONTROLLER::load(string filename, HWND hWnd)
{
	CONTROLLER::load(filename, hWnd, NULL);
}

void CONTROLLER::load(string filename, HWND handle, HWND hStatusWnd)
{
	if (!(hDLL = LoadLibrary(filename.c_str())))
		throw PLUGIN_FAILED_TO_LOAD;

	hWnd						= handle;

	closeDLL_					= (CLOSEDLL) GetProcAddress(hDLL, "CloseDLL");
	dllAbout_					= (DLLABOUT) GetProcAddress(hDLL, "DllAbout");
	dllConfig_					= (DLLCONFIG) GetProcAddress(hDLL, "DllConfig");
	dllTest_					= (DLLTEST)	GetProcAddress(hDLL, "DllTest");
	getDllInfo_					= (GETDLLINFO) GetProcAddress(hDLL, "GetDllInfo");
	romClosed_					= (ROMCLOSED) GetProcAddress(hDLL, "RomClosed");

	plugin_info					= (PLUGIN_INFO*) malloc(sizeof(PLUGIN_INFO));
	getDllInfo_(plugin_info);
	
	romOpen_					= (ROMOPEN) GetProcAddress(hDLL, "RomOpen");
	controllerCommand_			= (CONTROLLERCOMMAND) GetProcAddress(hDLL, "ControllerCommand");
	initiateControllers_		= (INITIATECONTROLLERS) GetProcAddress(hDLL, "InitiateControllers");
	getKeys_					= (GETKEYS) GetProcAddress(hDLL, "GetKeys");
	readController_				= (READCONTROLLER) GetProcAddress(hDLL, "ReadController");
	wmKeyDown_					= (WMKEYDOWN) GetProcAddress(hDLL, "WM_KeyDown");
	wmKeyUp_					= (WMKEYUP) GetProcAddress(hDLL, "WM_KeyUp");

	control_info				= (CONTROL_INFO*) malloc(sizeof(CONTROL_INFO));

	control_info->hMainWindow	= hWnd;
	control_info->hInst			= hDLL;
	control_info->memoryBswaped = TRUE;
	control_info->header		= (byte*) MMU::get(ROM_SEG_BEG);
	control_info->controls		= controllers;
	
	for (int i = 0; i < 4; i++)
	{
		controllers[i].Present	= FALSE;
		controllers[i].RawData	= FALSE;
		controllers[i].Plugin	= PLUGIN_NONE;
	}

	initiateControllers();

	romOpen();
	loaded = true;
}

void CONTROLLER::closeDLL()
{
	return closeDLL_();
}

void CONTROLLER::dllAbout()
{
	return dllAbout_(hWnd);
}

void CONTROLLER::dllConfig()
{
	return dllConfig_(hWnd);
}

void CONTROLLER::dllTest()
{
	return dllTest_(hWnd);
}

void CONTROLLER::romClosed()
{
	return romClosed_();
}

void CONTROLLER::romOpen()
{
	return romOpen_();
}

void CONTROLLER::controllerCommand(int Control, BYTE* Command)
{
	return controllerCommand_(Control, Command);
}	

void CONTROLLER::initiateControllers()
{
	return initiateControllers_(*control_info);
}

void CONTROLLER::getKeys(int Control, BUTTONS* Keys)
{
	return getKeys_(Control, Keys);
}

void CONTROLLER::readController(int Control, BYTE* Command)
{
	return readController_(Control, Command);
}

void CONTROLLER::wmKeyDown(WPARAM wParam, LPARAM lParam)
{
	return wmKeyDown_(wParam, lParam);
}

void CONTROLLER::wmKeyUp(WPARAM wParam, LPARAM lParam)
{
	return wmKeyUp_(wParam, lParam);
}

bool CONTROLLER::isLoaded(void)
{
	return loaded;
}