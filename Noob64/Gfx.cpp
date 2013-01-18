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

CAPTURESCREEN	GFX::captureScreen_ = 0;
CHANGEWINDOW	GFX::changeWindow_ = 0;
DRAWSCREEN		GFX::drawScreen_ = 0;
INITIATEGFX		GFX::initiateGFX_ = 0;
MOVESCREEN		GFX::moveScreen_ = 0;
PROCESSDLIST	GFX::processDList_ = 0;
PROCESSRDPLIST	GFX::processRDPList_ = 0;
ROMOPEN			GFX::romOpen_ = 0;
SHOWCFB			GFX::showCFB_ = 0;
UPDATESCREEN	GFX::updateScreen_ = 0;
VISTATUSCHANGED	GFX::viStatusChanged_ = 0;
VIWIDTHCHANGED	GFX::viWidthChanged_ = 0;
GFX_INFO*		GFX::gfx_info = 0;

void GFX::load(string filename, HWND hWnd)
{
	GFX::load(filename, hWnd, NULL);
}

void GFX::load(string filename, HWND hWnd, HWND hStatusBar)
{
	PLUGIN::load(filename, hWnd);

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

	gfx_info					= (GFX_INFO*) malloc(sizeof(GFX_INFO));

	gfx_info->hWnd				= hWnd;			// Render window
	gfx_info->hStatusBar		= hStatusBar;	// if render window does not have a status bar then this is NULL
	gfx_info->memoryBswaped		= TRUE;			// plugin_info->memoryBswaped;

	gfx_info->rom_header		= (byte*) MMU::get(ROM_SEG_BEG);
	gfx_info->rdram				= (byte*) MMU::get(RDRAM_SEG_BEG);
	gfx_info->dmem				= (byte*) MMU::get(SP_DMEM);
	gfx_info->imem				= (byte*) MMU::get(SP_IMEM);

	gfx_info->mi_intr_reg		= (word*) MMU::get(MI_INTR_REG);

	gfx_info->dpc_start_reg		= (word*) MMU::get(DPC_START_REG);
	gfx_info->dpc_end_reg		= (word*) MMU::get(DPC_END_REG);
	gfx_info->dpc_current_reg	= (word*) MMU::get(DPC_CURRENT_REG);
	gfx_info->dpc_status_reg	= (word*) MMU::get(DPC_STATUS_REG);
	gfx_info->dpc_clock_reg		= (word*) MMU::get(DPC_CLOCK_REG);
	gfx_info->dpc_bufbusy_reg	= (word*) MMU::get(DPC_BUFBUSY_REG);
	gfx_info->dpc_pipebusy_reg	= (word*) MMU::get(DPC_PIPEBUSY_REG);
	gfx_info->dpc_tmem_reg		= (word*) MMU::get(DPC_TMEM_REG);

	gfx_info->vi_status_reg		= (word*) MMU::get(VI_STATUS_REG);
	gfx_info->vi_origin_reg		= (word*) MMU::get(VI_ORIGIN_REG);
	gfx_info->vi_width_reg		= (word*) MMU::get(VI_WIDTH_REG);
	gfx_info->vi_intr_reg		= (word*) MMU::get(VI_INTR_REG);
	gfx_info->vi_v_current_line_reg	= (word*) MMU::get(VI_CURRENT_REG);
	gfx_info->vi_timing_reg		= (word*) MMU::get(VI_BURST_REG);
	gfx_info->vi_v_sync_reg		= (word*) MMU::get(VI_V_SYNC_REG);
	gfx_info->vi_h_sync_reg		= (word*) MMU::get(VI_H_SYNC_REG);
	gfx_info->vi_leap_reg		= (word*) MMU::get(VI_LEAP_REG);
	gfx_info->vi_h_start_reg	= (word*) MMU::get(VI_H_START_REG);
	gfx_info->vi_v_start_reg	= (word*) MMU::get(VI_V_START_REG);
	gfx_info->vi_v_burst_reg	= (word*) MMU::get(VI_V_BURST_REG);
	gfx_info->vi_x_scale_reg	= (word*) MMU::get(VI_X_SCALE_REG);
	gfx_info->vi_y_scale_reg	= (word*) MMU::get(VI_Y_SCALE_REG);

	gfx_info->CheckInterrupts	= dummyCheckInterrupts;//&R4300i::check_interrupt;
	initiateGFX();
	romOpen();

	loaded = true;
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
