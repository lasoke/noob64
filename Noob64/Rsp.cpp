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

RSP::RSP(wstring filename, HWND hWnd) : PLUGIN(filename, hWnd)
{
	doRspCycles_				= (DORSPCYCLES) GetProcAddress(hDLL, "DoRspCycles");
	getRspDebugInfo_			= (GETRSPDEBUGINFO) GetProcAddress(hDLL, "GetRspDebugInfo");
	initiateRSP_				= (INITIATERSP) GetProcAddress(hDLL, "InitiateRSP");
	initiateRSPDebugger_		= (INITIATERSPDEBUGGER) GetProcAddress(hDLL, "InitiateRSPDebugger");
}

RSP::~RSP(void)
{
}

void RSP::init(RCP *rcp)
{
	PLUGIN::init(rcp);

	rsp_info					= (RSP_INFO*) malloc(sizeof(RSP_INFO));
	rspdebug_info				= getRspDebugInfo_ == NULL ? NULL : (RSPDEBUG_INFO*) malloc(sizeof(RSPDEBUG_INFO));
	debug_info					= initiateRSPDebugger_ == NULL ? NULL : (DEBUG_INFO*) malloc(sizeof(DEBUG_INFO));

	MMU& memory					= rcp->getCPU().getMMU();

	rsp_info->hInst				= hDLL;
	rsp_info->memoryBswaped		= plugin_info->memoryBswaped;
	rsp_info->rdram				= (byte*) memory[RDRAM_SEG_BEGINING];

	rsp_info->mi_intr_reg		= (word*) memory[MI_INTR_REG];

	rsp_info->dmem				= (byte*) memory[SP_DMEM];
	rsp_info->imem				= (byte*) memory[SP_IMEM];
	rsp_info->sp_mem_addr_reg	= (word*) memory[SP_MEM_ADDR_REG];
	rsp_info->sp_dram_addr_reg	= (word*) memory[SP_DRAM_ADDR_REG];
	rsp_info->sp_rd_len_reg		= (word*) memory[SP_RD_LEN_REG];
	rsp_info->sp_wr_len_reg		= (word*) memory[SP_WR_LEN_REG];
	rsp_info->sp_status_reg		= (word*) memory[SP_STATUS_REG];
	rsp_info->sp_dma_full_reg	= (word*) memory[SP_DMA_FULL_REG];
	rsp_info->sp_dma_busy_reg	= (word*) memory[SP_DMA_BUSY_REG];
	rsp_info->sp_semaphore_reg	= (word*) memory[SP_SEMAPHORE_REG];
	rsp_info->sp_pc_reg			= (word*) memory[SP_PC_REG];

	rsp_info->dpc_start_reg		= (word*) memory[DPC_START_REG];
	rsp_info->dpc_end_reg		= (word*) memory[DPC_END_REG];
	rsp_info->dpc_current_reg	= (word*) memory[DPC_CURRENT_REG];
	rsp_info->dpc_status_reg	= (word*) memory[DPC_STATUS_REG];
	rsp_info->dpc_clock_reg		= (word*) memory[DPC_CLOCK_REG];
	rsp_info->dpc_bufbusy_reg	= (word*) memory[DPC_BUFBUSY_REG];
	rsp_info->dpc_pipebusy_reg	= (word*) memory[DPC_PIPEBUSY_REG];
	rsp_info->dpc_tmem_reg		= (word*) memory[DPC_TMEM_REG];

	// TODO:
	rsp_info->CheckInterrupts	= dummy;
	rsp_info->ProcessDlistList  = dummy;
	rsp_info->ProcessAlistList  = dummy;
	rsp_info->ProcessRdpList	= dummy;
	rsp_info->ShowCFB			= dummy;

	int cycles;
	initiateRSP((word*)&cycles);
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

