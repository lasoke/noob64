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

/*** Controller plugin's ****/
#define PLUGIN_NONE					1
#define PLUGIN_MEMPAK				2
#define PLUGIN_RUMBLE_PAK			3 
#define PLUGIN_TANSFER_PAK			4 // not implemeted for non raw data
#define PLUGIN_RAW					5 // the controller plugin is passed in raw data

typedef struct {
	BOOL Present;
	BOOL RawData;
	int  Plugin;
} CONTROL;

typedef struct {
	HWND		hMainWindow;
	HINSTANCE	hInst;
	BOOL		memoryBswaped;
	byte*		header;			// This is the rom header (first 40h bytes of the rom)
	CONTROL*	controls;		// A pointer to an array of 4 controllers
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

typedef void (__cdecl* CONTROLLERCOMMAND)(int, byte*);
typedef void (__cdecl* INITIATECONTROLLERS)(CONTROL_INFO);
typedef void (__cdecl* GETKEYS)(int, BUTTONS*);
typedef void (__cdecl* READCONTROLLER)(int, byte*);
typedef void (__cdecl* WMKEYDOWN)(WPARAM, LPARAM);
typedef void (__cdecl* WMKEYUP)(WPARAM, LPARAM);

class CONTROLLER
{
public:
	static void dllAbout();			// Open the About window of the plugin
	static void dllConfig();		// Open the Config window of the plugin
	static void closeDLL(void);		// Closes the DLL
	static bool isLoaded(void);
protected:
	static void dllTest();			// Notifies the user whether the plugin is correctly loaded or not
	static void romClosed(void);	// To call when the ROM is closed

	static bool				loaded;
	static HINSTANCE		hDLL;
	static HWND				hWnd;

	static CLOSEDLL			closeDLL_;
	static DLLABOUT			dllAbout_;
	static DLLCONFIG		dllConfig_;
	static DLLTEST			dllTest_;
	static GETDLLINFO		getDllInfo_;
	static ROMCLOSED		romClosed_;

	static PLUGIN_INFO*		plugin_info;
public:
	static bool load(string filename, HWND hWnd); // Plugs the DLL into the RCP
	static bool load(string filename, HWND hWnd, HWND hStatusWnd);	// Plugs the DLL into the RCP
	static bool init(void);

	static void romOpen(void);
	static void controllerCommand(int Control, byte * Command);
	static void initiateControllers();
	static void getKeys(int Control, BUTTONS * Keys);
	static void readController(int Control, byte * Command);
	static void wmKeyDown(WPARAM wParam, LPARAM lParam);
	static void wmKeyUp(WPARAM wParam, LPARAM lParam);
	
	static CONTROL						controllers[4];
private:
	static ROMOPEN						romOpen_;
	static CONTROLLERCOMMAND			controllerCommand_;
	static INITIATECONTROLLERS			initiateControllers_;
	static GETKEYS						getKeys_;
	static READCONTROLLER				readController_;
	static WMKEYDOWN					wmKeyDown_;
	static WMKEYUP						wmKeyUp_;

	static CONTROL_INFO*				control_info;
};
