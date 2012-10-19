#pragma once

#include "Plugin.h"

typedef struct {
	HINSTANCE hInst;
	bool MemoryBswaped;    /* If this is set to TRUE, then the memory has been pre
	                          bswap on a dword (32 bits) boundry */
	byte * rdram;
	byte * dmem;
	byte * imem;

	word * mi_intr_reg;

	word * sp_mem_addr_reg;
	word * sp_dram_addr_reg;
	word * sp_rd_len_reg;
	word * sp_wr_len_reg;
	word * sp_status_reg;
	word * sp_dma_full_reg;
	word * sp_dma_busy_reg;
	word * sp_pc_reg;
	word * sp_semaphore_reg;

	word * dpc_start_reg;
	word * dpc_end_reg;
	word * dpc_current_reg;
	word * dpc_status_reg;
	word * dpc_clock_reg;
	word * dpc_bufbusy_reg;
	word * dpc_pipebusy_reg;
	word * dpc_tmem_reg;

	void (*CheckInterrupts)(void);
	void (*ProcessDlistList)(void);
	void (*ProcessAlistList)(void);
	void (*ProcessRdpList)(void);
	void (*ShowCFB)(void);
} RSP_INFO;

typedef struct {
	/* Menu */
	/* Items should have an ID between 5001 and 5100 */
	HMENU hRSPMenu;
	void (*ProcessMenuItem) ( int ID );

	/* Break Points */
	bool UseBPoints;
	char BPPanelName[20];
	void (*Add_BPoint)      (void);
	void (*CreateBPPanel)   (HWND hDlg, RECT rcBox);
	void (*HideBPPanel)     (void);
	void (*PaintBPPanel)    (PAINTSTRUCT ps);
	void (*ShowBPPanel)     (void);
	void (*RefreshBpoints)  (HWND hList);
	void (*RemoveBpoint)    (HWND hList, int index);
	void (*RemoveAllBpoint) (void);
	
	/* RSP command Window */
	void (*Enter_RSP_Commands_Window) (void );

} RSPDEBUG_INFO;

typedef struct {
	void (*UpdateBreakPoints)(void);
	void (*UpdateMemory)(void);
	void (*UpdateR4300iRegisters)(void);
	void (*Enter_BPoint_Window)(void);
	void (*Enter_R4300i_Commands_Window)(void);
	void (*Enter_R4300i_Register_Window)(void);
	void (*Enter_RSP_Commands_Window) (void);
	void (*Enter_Memory_Window)(void);
} DEBUG_INFO;

typedef word (_cdecl* DORSPCYCLES)(word);
typedef void (_cdecl* GETRSPDEBUGINFO)(RSPDEBUG_INFO*);
typedef void (_cdecl* INITIATERSP)(RSP_INFO, word*);
typedef void (_cdecl* INITIATERSPDEBUGGER)(DEBUG_INFO);


class RSP : public PLUGIN
{
public:
	RSP(wstring filename, MEMORY *mem);
	~RSP();

	word doRspCycles(word);
	void getRspDebugInfo();
	void initiateRSP(word*);
	void initiateRSPDebugger();

private:
	MEMORY					*memory;

	DORSPCYCLES				doRspCycles_;
	GETRSPDEBUGINFO			getRspDebugInfo_;
	INITIATERSP				initiateRSP_;
	INITIATERSPDEBUGGER		initiateRSPDebugger_;
	
	RSP_INFO				*rsp_info;
	RSPDEBUG_INFO			*rspdebug_info;
	DEBUG_INFO				*debug_info;
};

