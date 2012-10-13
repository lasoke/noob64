#pragma once

#include "Plugin.h"

typedef struct {
	HINSTANCE hInst;
	bool MemoryBswaped;    /* If this is set to TRUE, then the memory has been pre
	                          bswap on a dword (32 bits) boundry */
	byte * RDRAM;
	byte * DMEM;
	byte * IMEM;

	word * MI_INTR_REG;

	word * SP_MEM_ADDR_REG;
	word * SP_DRAM_ADDR_REG;
	word * SP_RD_LEN_REG;
	word * SP_WR_LEN_REG;
	word * SP_STATUS_REG;
	word * SP_DMA_FULL_REG;
	word * SP_DMA_BUSY_REG;
	word * SP_PC_REG;
	word * SP_SEMAPHORE_REG;

	word * DPC_START_REG;
	word * DPC_END_REG;
	word * DPC_CURRENT_REG;
	word * DPC_STATUS_REG;
	word * DPC_CLOCK_REG;
	word * DPC_BUFBUSY_REG;
	word * DPC_PIPEBUSY_REG;
	word * DPC_TMEM_REG;

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

