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
#include "Rsp.h"

DORSPCYCLES				RSP::doRspCycles_ = 0;
GETRSPDEBUGINFO			RSP::getRspDebugInfo_ = 0;
INITIATERSP				RSP::initiateRSP_ = 0;
INITIATERSPDEBUGGER		RSP::initiateRSPDebugger_ = 0;
RSP_INFO*				RSP::rsp_info = 0;
RSPDEBUG_INFO*			RSP::rspdebug_info = 0;
DEBUG_INFO*				RSP::debug_info = 0;

void RSP::load(wstring filename, HWND hWnd)
{
	PLUGIN::load(filename, hWnd);

	doRspCycles_				= (DORSPCYCLES) GetProcAddress(hDLL, "DoRspCycles");
	getRspDebugInfo_			= (GETRSPDEBUGINFO) GetProcAddress(hDLL, "GetRspDebugInfo");
	initiateRSP_				= (INITIATERSP) GetProcAddress(hDLL, "InitiateRSP");
	initiateRSPDebugger_		= (INITIATERSPDEBUGGER) GetProcAddress(hDLL, "InitiateRSPDebugger");

	rsp_info					= (RSP_INFO*) malloc(sizeof(RSP_INFO));
	rspdebug_info				= getRspDebugInfo_ == NULL ? NULL : (RSPDEBUG_INFO*) malloc(sizeof(RSPDEBUG_INFO));
	debug_info					= initiateRSPDebugger_ == NULL ? NULL : (DEBUG_INFO*) malloc(sizeof(DEBUG_INFO));

	rsp_info->hInst				= hDLL;
	rsp_info->memoryBswaped		= plugin_info->memoryBswaped;
	rsp_info->rdram				= (byte*) MMU::get(RDRAM_SEG_BEG);

	rsp_info->mi_intr_reg		= (word*) MMU::get(MI_INTR_REG);

	rsp_info->dmem				= (byte*) MMU::get(SP_DMEM);
	rsp_info->imem				= (byte*) MMU::get(SP_IMEM);
	rsp_info->sp_mem_addr_reg	= (word*) MMU::get(SP_MEM_ADDR_REG);
	rsp_info->sp_dram_addr_reg	= (word*) MMU::get(SP_DRAM_ADDR_REG);
	rsp_info->sp_rd_len_reg		= (word*) MMU::get(SP_RD_LEN_REG);
	rsp_info->sp_wr_len_reg		= (word*) MMU::get(SP_WR_LEN_REG);
	rsp_info->sp_status_reg		= (word*) MMU::get(SP_STATUS_REG);
	rsp_info->sp_dma_full_reg	= (word*) MMU::get(SP_DMA_FULL_REG);
	rsp_info->sp_dma_busy_reg	= (word*) MMU::get(SP_DMA_BUSY_REG);
	rsp_info->sp_semaphore_reg	= (word*) MMU::get(SP_SEMAPHORE_REG);
	rsp_info->sp_pc_reg			= (word*) MMU::get(SP_PC_REG);

	rsp_info->dpc_start_reg		= (word*) MMU::get(DPC_START_REG);
	rsp_info->dpc_end_reg		= (word*) MMU::get(DPC_END_REG);
	rsp_info->dpc_current_reg	= (word*) MMU::get(DPC_CURRENT_REG);
	rsp_info->dpc_status_reg	= (word*) MMU::get(DPC_STATUS_REG);
	rsp_info->dpc_clock_reg		= (word*) MMU::get(DPC_CLOCK_REG);
	rsp_info->dpc_bufbusy_reg	= (word*) MMU::get(DPC_BUFBUSY_REG);
	rsp_info->dpc_pipebusy_reg	= (word*) MMU::get(DPC_PIPEBUSY_REG);
	rsp_info->dpc_tmem_reg		= (word*) MMU::get(DPC_TMEM_REG);

	// TODO:
	rsp_info->CheckInterrupts	= &R4300i::check_interrupt;
	rsp_info->ProcessDList		= &GFX::processDList;
	rsp_info->ProcessAList		= dummyProcessAList;//&AUDIO::processAList;
	rsp_info->ProcessRdpList	= &GFX::processRDPList;
	rsp_info->ShowCFB			= &GFX::showCFB;

	int cycles;
	initiateRSP((word*)&cycles);

	loaded = true;
}

word RSP::doRspCycles(word w)
{
	return doRspCycles_(w);
}

void RSP::getRspDebugInfo()
{
	return getRspDebugInfo_(rspdebug_info);
}

void RSP::initiateRSP(word* cycle_count)
{
	return initiateRSP_(*rsp_info, cycle_count);
}

void RSP::initiateRSPDebugger()
{
	return initiateRSPDebugger_(*debug_info);
}

