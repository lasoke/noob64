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

#include "Plugin.h"

typedef struct {
	HWND hWnd;			// Render window
	HWND hStatusBar;    // if render window does not have a status bar then this is NULL
	int memoryBswaped;

	byte* rom_header;
	byte* rdram;
	byte* dmem;
	byte* imem;

	word* mi_intr_reg;

	word* dpc_start_reg;
	word* dpc_end_reg;
	word* dpc_current_reg;
	word* dpc_status_reg;
	word* dpc_clock_reg;
	word* dpc_bufbusy_reg;
	word* dpc_pipebusy_reg;
	word* dpc_tmem_reg;

	word* vi_status_reg;
	word* vi_origin_reg;
	word* vi_width_reg;
	word* vi_intr_reg;
	word* vi_v_current_line_reg;
	word* vi_timing_reg;
	word* vi_v_sync_reg;
	word* vi_h_sync_reg;
	word* vi_leap_reg;
	word* vi_h_start_reg;
	word* vi_v_start_reg;
	word* vi_v_burst_reg;
	word* vi_x_scale_reg;
	word* vi_y_scale_reg;

	void (*CheckInterrupts)(void);
} GFX_INFO;

typedef void (_cdecl* CAPTURESCREEN)(char*);
typedef void (_cdecl* CHANGEWINDOW)(void);
typedef void (_cdecl* DRAWSCREEN)(void);
typedef bool (_cdecl* INITIATEGFX)(GFX_INFO);
typedef void (_cdecl* MOVESCREEN)(int, int);
typedef void (_cdecl* PROCESSDLIST)(void);
typedef void (_cdecl* PROCESSRDPLIST)(void);
typedef void (_cdecl* ROMOPEN)(void);
typedef void (_cdecl* SHOWCFB)(void);
typedef void (_cdecl* UPDATESCREEN)(void);
typedef void (_cdecl* VISTATUSCHANGED)(void);
typedef void (_cdecl* VIWIDTHCHANGED)(void);

/*
** The GFX class handles the video plugins
*/
class GFX : public PLUGIN
{
public:
	GFX(wstring filename, HWND hWnd);
	~GFX();

	void init(MEMORY* mem);

	void captureScreen(char*);
	void changeWindow(void);
	void drawScreen(void);
	bool initiateGFX(void);
	void moveScreen(int, int);
	void processDList(void);
	void processRDPList(void);
	void romOpen(void);
	void showCFB(void);
	void updateScreen(void);
	void viStatusChanged(void);
	void viWidthChanged(void);

	
private:
	CAPTURESCREEN		captureScreen_;
	CHANGEWINDOW		changeWindow_;
	DRAWSCREEN			drawScreen_;
	INITIATEGFX			initiateGFX_;
	MOVESCREEN			moveScreen_;
	PROCESSDLIST		processDList_;
	PROCESSRDPLIST		processRDPList_;
	ROMOPEN				romOpen_;
	SHOWCFB				showCFB_;
	UPDATESCREEN		updateScreen_;
	VISTATUSCHANGED		viStatusChanged_;
	VIWIDTHCHANGED		viWidthChanged_;

	GFX_INFO			*gfx_info;
};

