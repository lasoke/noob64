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

#define SYSTEM_NTSC	0
#define SYSTEM_PAL	1
#define SYSTEM_MPAL	2

/*
** The Audio structure that connects
** the plugin to the RCP
*/
typedef struct {
	HWND hWnd;
	HINSTANCE hInst;

	int	memoryBswaped;
	byte* header;	// This is the rom header (first 40h bytes of the rom
					// This will be in the same memory format as the rest of the memory.
	byte* rdram;
	byte* dmem;
	byte* imem;

	word* mi_intr_reg;

	word* ai_dram_addr_reg;
	word* ai_len_reg;
	word* ai_control_reg;
	word* ai_status_reg;
	word* ai_dacrate_reg;
	word* ai_bitrate_reg;

	void (*CheckInterrupts)(void);
} AUDIO_INFO;

typedef void (__cdecl* AIDACRATECHANGED)(int);
typedef void (__cdecl* AILENCHANGED)(void);
typedef word (__cdecl* AIREADLENGTH)(void);
typedef void (__cdecl* AIUPDATE)(int);
typedef int  (__cdecl* INITIATEAUDIO)(AUDIO_INFO);
typedef void (__cdecl* PROCESSALIST)(void);


/*
** The GFX class that handles the video plugins
*/
class AUDIO
{
public:
	static void dllAbout();			// Open the About window of the plugin
	static void dllConfig();		// Open the Config window of the plugin
	static void closeDLL(void);		// Closes the DLL
	static bool isLoaded(void);
private:
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
	static bool init(void);

	static void aiDacrateChanged(int);		// Changes the sound system changed
	static void aiLenChanged(void);			// Notifies the DLL that AI_LEN_REG changed
	static word aiReadLength(void);			// Returns the value pointed by AI_LEN_REG
	static void aiUpdate(int);				// Keeps the plugin up to date. If wait is true, waits for a msg in it's queue
	static bool initiateAudio();			// Initialize the plugin
	static void processAList(void);			// Process the pending audio list

private:
	static AIDACRATECHANGED	aiDacrateChanged_;
	static AILENCHANGED		aiLenChanged_;
	static AIREADLENGTH		aiReadLength_;
	static AIUPDATE			aiUpdate_;
	static INITIATEAUDIO	initiateAudio_;
	static PROCESSALIST		processAList_;

	static AUDIO_INFO*		audio_info;
};