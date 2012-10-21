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

#pragma once

#include "Plugin.h"

/*
**  RSP_INFO is the structure use by the plugin
**  to communicate with the emulator. It links the registers,
**  the memory, and some list of instructions
*/
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

/*
**	The RSPDEBUG_INFO structure can be use to debug the plugin
*/
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

/*
** The DEBUG_INFO structure help to debug the emulator
*/
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

/*
** The Class RSP is used to load the plugin RSP
** and contains functions and variables defined
** in the .dll plugin
*/
class RSP : public PLUGIN
{
public:
	RSP(wstring filename, MEMORY *mem);
	~RSP();
	
	// The main loop of the RSP, execute his instructions
	word doRspCycles(word);
	// To retreive the debug info of the RSP
	void getRspDebugInfo();
	// To initialize the value of the RSP variables
	void initiateRSP(word*);
	// To initialize the value of the RSP debugger variables
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

