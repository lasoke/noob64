#include "StdAfx.h"
#include "Rsp.h"


RSP::RSP(wstring filename, MEMORY *mem) : PLUGIN(filename)
{
	memory						= mem;

	doRspCycles_				= (DORSPCYCLES) GetProcAddress(hDLL, "DoRspCycles");
	getRspDebugInfo_			= (GETRSPDEBUGINFO) GetProcAddress(hDLL, "GetRspDebugInfo");
	initiateRSP_				= (INITIATERSP) GetProcAddress(hDLL, "InitiateRSP");
	initiateRSPDebugger_		= (INITIATERSPDEBUGGER) GetProcAddress(hDLL, "InitiateRSPDebugger");

	rsp_info					= (RSP_INFO*) malloc(sizeof(RSP_INFO));
	rspdebug_info				= getRspDebugInfo_ == NULL ? NULL : (RSPDEBUG_INFO*) malloc(sizeof(RSPDEBUG_INFO));
	debug_info					= initiateRSPDebugger_ == NULL ? NULL : (DEBUG_INFO*) malloc(sizeof(DEBUG_INFO));

	rsp_info->hInst				= hDLL; // FIXME?
	rsp_info->MemoryBswaped		= plugin_info->MemoryBswaped;
	rsp_info->RDRAM				= (byte*) memory->rdram.ptr;

	rsp_info->MI_INTR_REG		= (word*) memory->mi_regs.ptr + 0x8;

	rsp_info->DMEM				= (byte*) memory->sp_regs.ptr + 0x00000;
	rsp_info->IMEM				= (byte*) memory->sp_regs.ptr + 0x01000;
	rsp_info->SP_MEM_ADDR_REG	= (word*) memory->sp_regs.ptr + 0x40000;
	rsp_info->SP_DRAM_ADDR_REG	= (word*) memory->sp_regs.ptr + 0x40004;
	rsp_info->SP_RD_LEN_REG		= (word*) memory->sp_regs.ptr + 0x40008;
	rsp_info->SP_WR_LEN_REG		= (word*) memory->sp_regs.ptr + 0x4000C;
	rsp_info->SP_STATUS_REG		= (word*) memory->sp_regs.ptr + 0x40010;
	rsp_info->SP_DMA_FULL_REG	= (word*) memory->sp_regs.ptr + 0x40014;
	rsp_info->SP_DMA_BUSY_REG	= (word*) memory->sp_regs.ptr + 0x40018;
	rsp_info->SP_SEMAPHORE_REG	= (word*) memory->sp_regs.ptr + 0x4001C;
	rsp_info->SP_PC_REG			= (word*) memory->sp_regs.ptr + 0x80000;

	rsp_info->DPC_START_REG		= (word*) memory->dpc_regs.ptr + 0x00;
	rsp_info->DPC_END_REG		= (word*) memory->dpc_regs.ptr + 0x04;
	rsp_info->DPC_CURRENT_REG	= (word*) memory->dpc_regs.ptr + 0x08;
	rsp_info->DPC_STATUS_REG	= (word*) memory->dpc_regs.ptr + 0x0C;
	rsp_info->DPC_CLOCK_REG		= (word*) memory->dpc_regs.ptr + 0x10;
	rsp_info->DPC_BUFBUSY_REG	= (word*) memory->dpc_regs.ptr + 0x14;
	rsp_info->DPC_PIPEBUSY_REG	= (word*) memory->dpc_regs.ptr + 0x18;
	rsp_info->DPC_TMEM_REG		= (word*) memory->dpc_regs.ptr + 0x1C;

	// TODO: ?
	void (*CheckInterrupts)(void);
	void (*ProcessDlistList)(void);
	void (*ProcessAlistList)(void);
	void (*ProcessRdpList)(void);
	void (*ShowCFB)(void);
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

