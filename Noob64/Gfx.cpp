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
#include "Gfx.h"

void dummy()
{
	return;
}

GFX::GFX(wstring filename, HWND hWnd) : PLUGIN(filename, hWnd)
{
	captureScreen_				= (CAPTURESCREEN) GetProcAddress(hDLL, "CaptureScreen");
	changeWindow_				= (CHANGEWINDOW) GetProcAddress(hDLL, "ChangeWindow");
	drawScreen_					= (DRAWSCREEN) GetProcAddress(hDLL, "DrawScreen");
	initiateGFX_				= (INITIATEGFX) GetProcAddress(hDLL, "InitiateGFX");
	moveScreen_					= (MOVESCREEN) GetProcAddress(hDLL, "MoveScreen");
	processDList_				= (PROCESSDLIST) GetProcAddress(hDLL, "ProcessDList");
	processRDPList_				= (PROCESSRDPLIST) GetProcAddress(hDLL, "ProcessRDPList");
	romOpen_					= (ROMOPEN) GetProcAddress(hDLL, "RomOpen");
	showCFB_					= (SHOWCFB) GetProcAddress(hDLL, "ShowCFB");
	updateScreen_				= (UPDATESCREEN) GetProcAddress(hDLL, "UpdateScreen");
	viStatusChanged_			= (VISTATUSCHANGED) GetProcAddress(hDLL, "ViStatusChanged");
	viWidthChanged_				= (VIWIDTHCHANGED) GetProcAddress(hDLL, "ViWidthChanged");
}

GFX::~GFX(void)
{
	// TODO
}

void GFX::init(MEMORY *mem)
{
	PLUGIN::init(mem);
	mem->gfx = this;

	gfx_info					= (GFX_INFO*) malloc(sizeof(GFX_INFO));

	gfx_info->hWnd				= hWnd;	// Render window
	gfx_info->hStatusBar		= 0;	// if render window does not have a status bar then this is NULL
	gfx_info->memoryBswaped		= plugin_info->memoryBswaped;

	gfx_info->rom_header		= (byte*) (*memory)[ROM_SEG_BEGINING];
	gfx_info->rdram				= (byte*) (*memory)[RDRAM_SEG_BEGINING];
	gfx_info->dmem				= (byte*) (*memory)[SP_DMEM];
	gfx_info->imem				= (byte*) (*memory)[SP_IMEM];

	gfx_info->mi_intr_reg		= (word*) (*memory)[MI_INTR_REG];

	gfx_info->dpc_start_reg		= (word*) (*memory)[DPC_START_REG];
	gfx_info->dpc_end_reg		= (word*) (*memory)[DPC_END_REG];
	gfx_info->dpc_current_reg	= (word*) (*memory)[DPC_CURRENT_REG];
	gfx_info->dpc_status_reg	= (word*) (*memory)[DPC_STATUS_REG];
	gfx_info->dpc_clock_reg		= (word*) (*memory)[DPC_CLOCK_REG];
	gfx_info->dpc_bufbusy_reg	= (word*) (*memory)[DPC_BUFBUSY_REG];
	gfx_info->dpc_pipebusy_reg	= (word*) (*memory)[DPC_PIPEBUSY_REG];
	gfx_info->dpc_tmem_reg		= (word*) (*memory)[DPC_TMEM_REG];

	gfx_info->vi_status_reg		= (word*) (*memory)[VI_STATUS_REG];
	gfx_info->vi_origin_reg		= (word*) (*memory)[VI_ORIGIN_REG];
	gfx_info->vi_width_reg		= (word*) (*memory)[VI_WIDTH_REG];
	gfx_info->vi_intr_reg		= (word*) (*memory)[VI_INTR_REG];
	gfx_info->vi_v_current_line_reg	= (word*) (*memory)[VI_CURRENT_REG];
	gfx_info->vi_timing_reg		= (word*) (*memory)[VI_BURST_REG];
	gfx_info->vi_v_sync_reg		= (word*) (*memory)[VI_V_SYNC_REG];
	gfx_info->vi_h_sync_reg		= (word*) (*memory)[VI_H_SYNC_REG];
	gfx_info->vi_leap_reg		= (word*) (*memory)[VI_LEAP_REG];
	gfx_info->vi_h_start_reg	= (word*) (*memory)[VI_H_START_REG];
	gfx_info->vi_v_start_reg	= (word*) (*memory)[VI_V_START_REG];
	gfx_info->vi_v_burst_reg	= (word*) (*memory)[VI_V_BURST_REG];
	gfx_info->vi_x_scale_reg	= (word*) (*memory)[VI_X_SCALE_REG];
	gfx_info->vi_y_scale_reg	= (word*) (*memory)[VI_Y_SCALE_REG];

	// TODO:
	gfx_info->CheckInterrupts	= dummy;
	initiateGFX();
	romOpen();
}

void GFX::RefreshScreen()
{
	static word OLD_VI_V_SYNC_REG = 0, VI_INTR_TIME = 500000;

	if (OLD_VI_V_SYNC_REG != memory.vi_regs.getVsync())
	{
		if (memory.vi_regs.getVsync() == 0)
		{
			VI_INTR_TIME = 500000;
		} 
		else 
		{
			VI_INTR_TIME = (memory.vi_regs.getVsync() + 1) * 1500;
			if ((memory.vi_regs.getVsync() % 1) != 0)
				VI_INTR_TIME -= 38;
		}
	}
	timer_handler.ChangeTimer(ViTimer, timer_handler.Timer + timer_handler.NextTimer[ViTimer] + VI_INTR_TIME, Compare, Count);
	
	if ((VI_STATUS_REG & 0x10) != 0)
		ViFieldNumber = (ViFieldNumber == 0) ? 1 : 0;
	else
		ViFieldNumber = 0;
	
	memory.gfx->updateScreen();
}

void GFX::captureScreen(char* directory)
{
	return captureScreen_(directory);
}

void GFX::changeWindow(void)
{
	return changeWindow_();
}

void GFX::drawScreen(void)
{
	return drawScreen_();
}

bool GFX::initiateGFX()
{
	return initiateGFX_(*gfx_info);
}

void GFX::moveScreen(int x, int y)
{
	return moveScreen_(x, y);
}

void GFX::processDList(void)
{
	return processDList_();
}

void GFX::processRDPList(void)
{
	return processRDPList_();
}

void GFX::romOpen(void)
{
	return romOpen_();
}

void GFX::showCFB(void)
{
	return showCFB_();
}

void GFX::updateScreen(void)
{
	return updateScreen_();
}

void GFX::viStatusChanged(void)
{
	return viStatusChanged_();
}

void GFX::viWidthChanged(void)
{
	return viWidthChanged_();
}
