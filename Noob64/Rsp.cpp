#include "StdAfx.h"
#include "Rsp.h"

void checkInterrupts_temp(void)
{
	cout << "CheckInterrupts" << endl;
	getchar();
}

void processDlistList_temp(void)
{
	cout << "ProcessDlistList" << endl;
	getchar();
}

void processAlistList_temp(void)
{
	cout << "ProcessAlistList" << endl;
	getchar();
}

void processRdpList_temp(void)
{
	cout << "ProcessRdpList" << endl;
	getchar();
}

void showCFB_temp(void)
{
	cout << "ShowCFB" << endl;
	getchar();
}

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
	rsp_info->CheckInterrupts	= checkInterrupts_temp;
	rsp_info->ProcessDlistList  = processDlistList_temp;
	rsp_info->ProcessAlistList  = processAlistList_temp;
	rsp_info->ProcessRdpList	= processRdpList_temp;
	rsp_info->ShowCFB			= showCFB_temp;

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

