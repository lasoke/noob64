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

void dummy_checkInterrupts()
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
}

void GFX::init(MEMORY *mem)
{
	PLUGIN::init(mem);

	gfx_info					= (GFX_INFO*) malloc(sizeof(GFX_INFO));

	gfx_info->hWnd				= hWnd;	// Render window
	gfx_info->hStatusBar		= 0;	// if render window does not have a status bar then this is NULL
	gfx_info->memoryBswaped		= plugin_info->memoryBswaped;

	gfx_info->rom_header		= (byte*) memory->rom[0];
	gfx_info->rdram				= (byte*) memory->rdram[0];
	gfx_info->dmem				= (byte*) memory->sp_regs[0x00000];
	gfx_info->imem				= (byte*) memory->sp_regs[0x01000];

	gfx_info->mi_intr_reg		= (word*) memory->mi_regs[0x08];

	gfx_info->dpc_start_reg		= (word*) memory->dpc_regs[0x00];
	gfx_info->dpc_end_reg		= (word*) memory->dpc_regs[0x04];
	gfx_info->dpc_current_reg	= (word*) memory->dpc_regs[0x08];
	gfx_info->dpc_status_reg	= (word*) memory->dpc_regs[0x0C];
	gfx_info->dpc_clock_reg		= (word*) memory->dpc_regs[0x10];
	gfx_info->dpc_bufbusy_reg	= (word*) memory->dpc_regs[0x14];
	gfx_info->dpc_pipebusy_reg	= (word*) memory->dpc_regs[0x18];
	gfx_info->dpc_tmem_reg		= (word*) memory->dpc_regs[0x1C];

	gfx_info->vi_status_reg		= (word*) memory->vi_regs[0x00];
	gfx_info->vi_origin_reg		= (word*) memory->vi_regs[0x04];
	gfx_info->vi_width_reg		= (word*) memory->vi_regs[0x08];
	gfx_info->vi_intr_reg		= (word*) memory->vi_regs[0x0C];
	gfx_info->vi_v_current_line_reg	= (word*) memory->vi_regs[0x10];
	gfx_info->vi_timing_reg		= (word*) memory->vi_regs[0x14];
	gfx_info->vi_v_sync_reg		= (word*) memory->vi_regs[0x18];
	gfx_info->vi_h_sync_reg		= (word*) memory->vi_regs[0x1C];
	gfx_info->vi_leap_reg		= (word*) memory->vi_regs[0x20];
	gfx_info->vi_h_start_reg	= (word*) memory->vi_regs[0x24];
	gfx_info->vi_v_start_reg	= (word*) memory->vi_regs[0x28];
	gfx_info->vi_v_burst_reg	= (word*) memory->vi_regs[0x2C];
	gfx_info->vi_x_scale_reg	= (word*) memory->vi_regs[0x30];
	gfx_info->vi_y_scale_reg	= (word*) memory->vi_regs[0x34];

	// TODO:
	gfx_info->CheckInterrupts	= dummy_checkInterrupts;

	romOpen();
	initiateGFX();
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
