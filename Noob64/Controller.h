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
 * The Gfx files contains the functions, macro and structure to represente
 * and connect our emulator to the Gfx plugin.
 *
 */

#pragma once

#include "Plugin.h"

/*** Conteroller plugin's ****/
#define PLUGIN_NONE					1
#define PLUGIN_MEMPAK				2
#define PLUGIN_RUMBLE_PAK			3 
#define PLUGIN_TANSFER_PAK			4 // not implemeted for non raw data
#define PLUGIN_RAW					5 // the controller plugin is passed in raw data

typedef int BOOL;

typedef struct {
	BOOL Present;
	BOOL RawData;
	int  Plugin;
} CONTROL;

typedef struct {
	HWND hMainWindow;
	HINSTANCE hinst;

	BOOL MemoryBswaped;		// If this is set to TRUE, then the memory has been pre
							//   bswap on a dword (32 bits) boundry, only effects header. 
							//	eg. the first 8 bytes are stored like this:
							//        4 3 2 1   8 7 6 5
	BYTE * HEADER;			// This is the rom header (first 40h bytes of the rom)
	CONTROL *Controls;		// A pointer to an array of 4 controllers .. eg:
							// CONTROL Controls[4];
} CONTROL_INFO;

union BUTTONS {
	DWORD Value;
	struct {
		unsigned R_DPAD       : 1;
		unsigned L_DPAD       : 1;
		unsigned D_DPAD       : 1;
		unsigned U_DPAD       : 1;
		unsigned START_BUTTON : 1;
		unsigned Z_TRIG       : 1;
		unsigned B_BUTTON     : 1;
		unsigned A_BUTTON     : 1;

		unsigned R_CBUTTON    : 1;
		unsigned L_CBUTTON    : 1;
		unsigned D_CBUTTON    : 1;
		unsigned U_CBUTTON    : 1;
		unsigned R_TRIG       : 1;
		unsigned L_TRIG       : 1;
		unsigned Reserved1    : 1;
		unsigned Reserved2    : 1;

		signed   Y_AXIS       : 8;

		signed   X_AXIS       : 8;
	};
};

typedef void (__cdecl* CONTCLOSEDLL)(void);
typedef void (__cdecl* CONTROLLERCOMMAND)(int Control, BYTE * Command);
typedef void (__cdecl* CONTDLLABOUT)(HWND hParent);
typedef bool (__cdecl* CONTCONFIG)(HWND hParent);
typedef void (__cdecl* INITIATECONTROLLERS_1_0)(HWND hMainWindow, CONTROL Controls[4]);
typedef void (__cdecl* INITIATECONTROLLERS_1_1)(CONTROL_INFO ControlInfo);
typedef void (__cdecl* GETKEYS)(int Control, BUTTONS * Keys);
typedef void (__cdecl* READCONTROLLER)(int Control, BYTE * Command);
typedef void (__cdecl* WMKEYDOWN)(WPARAM wParam, LPARAM lParam);
typedef void (__cdecl* WMKEYUP)(WPARAM wParam, LPARAM lParam);
typedef void (__cdecl* RUMBLECOMMAND)(int Control, BOOL bRumble);

class CONTROLLER : public PLUGIN
{
public:
	static void load(string filename, HWND hWnd, HWND hStatusWnd);	// Plugs the DLL into the RCP

	static void contCloseDLL(void);
	static void controllerCommand(int Control, BYTE * Command);	
	static void contDllAbout(HWND hParent);
	static bool contConfig(HWND hParent);
	static void initiateControllers_1_0(HWND hMainWindow, CONTROL Controls[4]);
	static void initiateControllers_1_1(CONTROL_INFO ControlInfo);
	static void getKeys(int Control, BUTTONS * Keys);
	static void readController(int Control, BYTE * Command);
	static void wmKeyDown(WPARAM wParam, LPARAM lParam);
	static void wmKeyUp(WPARAM wParam, LPARAM lParam);
	static void rumbleCommand(int Control, BOOL bRumble);
	
	static CONTROL						controllers[4];
private:
	static CONTCLOSEDLL					contCloseDLL_;
	static CONTROLLERCOMMAND			controllerCommand_;
	static CONTDLLABOUT					contDllAbout_;
	static CONTCONFIG					contConfig_;
	static INITIATECONTROLLERS_1_0		initiateControllers_1_0_;
	static INITIATECONTROLLERS_1_1		initiateControllers_1_1_;
	static GETKEYS						getKeys_;
	static READCONTROLLER				readController_;
	static WMKEYDOWN					wmKeyDown_;
	static WMKEYUP						wmKeyUp_;
	static RUMBLECOMMAND				rumbleCommand_;

	static CONTROL_INFO*				control_info;
	static w							contVersion;
};
