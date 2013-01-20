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

CONTCLOSEDLL				CONTROLLER::contCloseDLL_ = 0;
CONTROLLERCOMMAND			CONTROLLER::controllerCommand_ = 0;
CONTDLLABOUT				CONTROLLER::contDllAbout_ = 0;
CONTCONFIG					CONTROLLER::contConfig_ = 0;
INITIATECONTROLLERS_1_0		CONTROLLER::initiateControllers_1_0_ = 0;
INITIATECONTROLLERS_1_1		CONTROLLER::initiateControllers_1_1_ = 0;
GETKEYS						CONTROLLER::getKeys_ = 0;
READCONTROLLER				CONTROLLER::readController_ = 0;
WMKEYDOWN					CONTROLLER::wmKeyDown_ = 0;
WMKEYUP						CONTROLLER::wmKeyUp_ = 0;
RUMBLECOMMAND				CONTROLLER::rumbleCommand_ = 0;

CONTROL_INFO*				CONTROLLER::control_info = 0;
w							CONTROLLER::contVersion = 0;
CONTROL						CONTROLLER::controllers[4];


void CONTROLLER::load(string filename, HWND hWnd, HWND hStatusWnd)
{
	SendMessage( hStatusWnd, SB_SETTEXT, 0, (LPARAM)"loading Controller plugin" );
	PLUGIN::load(filename, hWnd, hStatusWnd);
	
	contVersion = plugin_info->version;

	contCloseDLL_				= (CONTCLOSEDLL) GetProcAddress(hDLL, "ContCloseDLL");
	controllerCommand_				= (CONTROLLERCOMMAND) GetProcAddress(hDLL, "ControllerCommand");
	contDllAbout_					= (CONTDLLABOUT) GetProcAddress(hDLL, "ContDllAbout");
	contConfig_				= (CONTCONFIG) GetProcAddress(hDLL, "ContConfig");
	if (contVersion == 0x0100)
		initiateControllers_1_0_ = (INITIATECONTROLLERS_1_0) GetProcAddress(hDLL, "InitiateControllers_1_0");
	if (contVersion == 0x0101)
		initiateControllers_1_1_ = (INITIATECONTROLLERS_1_1) GetProcAddress(hDLL, "InitiateControllers_1_1");
	getKeys_ = (GETKEYS) GetProcAddress(hDLL, "GetKeys");
	readController_	= (READCONTROLLER) GetProcAddress(hDLL, "ReadController");
	wmKeyDown_					= (WMKEYDOWN) GetProcAddress(hDLL, "WM_KeyDown");
	wmKeyUp_				= (WMKEYUP) GetProcAddress(hDLL, "WM_KeyUp");
	rumbleCommand_			= (RUMBLECOMMAND) GetProcAddress(hDLL, "RumbleCommand");

	controllers[0].Present = FALSE;
	controllers[0].RawData = FALSE;
	controllers[0].Plugin  = PLUGIN_NONE;

	controllers[1].Present = FALSE;
	controllers[1].RawData = FALSE;
	controllers[1].Plugin  = PLUGIN_NONE;

	controllers[2].Present = FALSE;
	controllers[2].RawData = FALSE;
	controllers[2].Plugin  = PLUGIN_NONE;

	controllers[3].Present = FALSE;
	controllers[3].RawData = FALSE;
	controllers[3].Plugin  = PLUGIN_NONE;

	if (contVersion == 0x0100)
		initiateControllers_1_0(hWnd, controllers);
	if (contVersion == 0x0101)
	{
		control_info = (CONTROL_INFO*) malloc(sizeof(CONTROL_INFO));
		control_info->Controls = controllers;
		control_info->HEADER = (byte*) MMU::get(ROM_SEG_BEG);
		control_info->hinst = 0;
		control_info->hMainWindow = hWnd;
		control_info->MemoryBswaped = TRUE;
		initiateControllers_1_1(*control_info);
	}

	loaded = true;
	SendMessage( hStatusWnd, SB_SETTEXT, 0, (LPARAM)"Controller plugin loaded" );
}

void CONTROLLER::contCloseDLL(void)
{
	return contCloseDLL_();
}

void CONTROLLER::controllerCommand(int Control, BYTE * Command)
{
	return controllerCommand_(Control, Command);
}	

void CONTROLLER::contDllAbout(HWND hParent)
{
	return contDllAbout_(hParent);
}

bool CONTROLLER::contConfig(HWND hParent)
{
	return contConfig_(hParent);
}

void CONTROLLER::initiateControllers_1_0(HWND hMainWindow, CONTROL Controls[4])
{
//	return initiateControllers_1_0_(hMainWindow, Controls);
}

void CONTROLLER::initiateControllers_1_1(CONTROL_INFO ControlInfo)
{
	return initiateControllers_1_1_(ControlInfo);
}

void CONTROLLER::getKeys(int Control, BUTTONS * Keys)
{
	return getKeys_(Control, Keys);
}

void CONTROLLER::readController(int Control, BYTE * Command)
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

void CONTROLLER::rumbleCommand(int Control, BOOL bRumble)
{
	return rumbleCommand_(Control, bRumble);
}