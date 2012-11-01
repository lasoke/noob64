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

RSP::RSP(wstring filename, MEMORY *mem) : PLUGIN(filename, mem)
{
	doRspCycles_				= (DORSPCYCLES) GetProcAddress(hDLL, "DoRspCycles");
	getRspDebugInfo_			= (GETRSPDEBUGINFO) GetProcAddress(hDLL, "GetRspDebugInfo");
	initiateRSP_				= (INITIATERSP) GetProcAddress(hDLL, "InitiateRSP");
	initiateRSPDebugger_		= (INITIATERSPDEBUGGER) GetProcAddress(hDLL, "InitiateRSPDebugger");

	rsp_info					= (RSP_INFO*) malloc(sizeof(RSP_INFO));
	rspdebug_info				= getRspDebugInfo_ == NULL ? NULL : (RSPDEBUG_INFO*) malloc(sizeof(RSPDEBUG_INFO));
	debug_info					= initiateRSPDebugger_ == NULL ? NULL : (DEBUG_INFO*) malloc(sizeof(DEBUG_INFO));

	rsp_info->hInst				= hDLL; // FIXME?
	rsp_info->memoryBswaped		= plugin_info->memoryBswaped;
	rsp_info->rdram				= (byte*) memory->rdram[0];

	rsp_info->mi_intr_reg		= (word*) memory->mi_regs[0x8];

	rsp_info->dmem				= (byte*) memory->sp_regs[0x00000];
	rsp_info->imem				= (byte*) memory->sp_regs[0x01000];
	rsp_info->sp_mem_addr_reg	= (word*) memory->sp_regs[0x40000];
	rsp_info->sp_dram_addr_reg	= (word*) memory->sp_regs[0x40004];
	rsp_info->sp_rd_len_reg		= (word*) memory->sp_regs[0x40008];
	rsp_info->sp_wr_len_reg		= (word*) memory->sp_regs[0x4000C];
	rsp_info->sp_status_reg		= (word*) memory->sp_regs[0x40010];
	rsp_info->sp_dma_full_reg	= (word*) memory->sp_regs[0x40014];
	rsp_info->sp_dma_busy_reg	= (word*) memory->sp_regs[0x40018];
	rsp_info->sp_semaphore_reg	= (word*) memory->sp_regs[0x4001C];
	rsp_info->sp_pc_reg			= (word*) memory->sp_regs[0x80000];

	rsp_info->dpc_start_reg		= (word*) memory->dpc_regs[0x00];
	rsp_info->dpc_end_reg		= (word*) memory->dpc_regs[0x04];
	rsp_info->dpc_current_reg	= (word*) memory->dpc_regs[0x08];
	rsp_info->dpc_status_reg	= (word*) memory->dpc_regs[0x0C];
	rsp_info->dpc_clock_reg		= (word*) memory->dpc_regs[0x10];
	rsp_info->dpc_bufbusy_reg	= (word*) memory->dpc_regs[0x14];
	rsp_info->dpc_pipebusy_reg	= (word*) memory->dpc_regs[0x18];
	rsp_info->dpc_tmem_reg		= (word*) memory->dpc_regs[0x1C];

	// FIXME:
	rsp_info->CheckInterrupts	= NULL;
	rsp_info->ProcessDlistList  = NULL;
	rsp_info->ProcessAlistList  = NULL;
	rsp_info->ProcessRdpList	= NULL;
	rsp_info->ShowCFB			= NULL;

	int cycles;
	initiateRSP((word*)&cycles);

}

RSP::~RSP(void)
{
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

