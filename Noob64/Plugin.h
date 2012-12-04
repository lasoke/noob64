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

typedef void (_cdecl* CLOSEDLL)(void);
typedef void (_cdecl* DLLABOUT)(HWND);
typedef void (_cdecl* DLLCONFIG)(HWND);
typedef void (_cdecl* DLLTEST)(HWND);
typedef void (_cdecl* GETDLLINFO)(PLUGIN_INFO*);
typedef void (_cdecl* ROMCLOSED)(void);

/*
** The Class PLUGIN will be used by the class of every plugin
** it contains methods and structure define in every plugins
*/
class PLUGIN
{
public:
	static bool isLoaded(void);
protected:
	static void load(wstring filename, HWND hWnd);
	static bool loaded;

	static void closeDLL(void);		// Closes the DLL
	static void dllAbout(HWND);		// Open the About window of the plugin
	static void dllConfig(HWND);	// Open the Config window of the plugin
	static void dllTest(HWND);		// Notifies the user whether the plugin is correctly loaded or not
	static void romClosed(void);	// To call when the ROM is closed

	static HINSTANCE		hDLL;
	static HWND				hWnd;

	static CLOSEDLL			closeDLL_;
	static DLLABOUT			dllAbout_;
	static DLLCONFIG		dllConfig_;
	static DLLTEST			dllTest_;
	static GETDLLINFO		getDllInfo_;
	static ROMCLOSED		romClosed_;

	static PLUGIN_INFO*		plugin_info;
};

