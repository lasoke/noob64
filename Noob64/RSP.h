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

/*
 * The RSP files contains the functions, macro and structure to represente
 * and interface our emulator with the RSP plugin.
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
	int memoryBswaped;    /* If this is set to TRUE, then the memory has been pre
	                          bswap on a dword (32 bits) boundry */
	byte* rdram;
	byte* dmem;
	byte* imem;

	word* mi_intr_reg;

	word* sp_mem_addr_reg;
	word* sp_dram_addr_reg;
	word* sp_rd_len_reg;
	word* sp_wr_len_reg;
	word* sp_status_reg;
	word* sp_dma_full_reg;
	word* sp_dma_busy_reg;
	word* sp_pc_reg;
	word* sp_semaphore_reg;

	word* dpc_start_reg;
	word* dpc_end_reg;
	word* dpc_current_reg;
	word* dpc_status_reg;
	word* dpc_clock_reg;
	word* dpc_bufbusy_reg;
	word* dpc_pipebusy_reg;
	word* dpc_tmem_reg;

	void (*CheckInterrupts)(void);
	void (*ProcessDList)(void);
	void (*ProcessAList)(void);
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
	void (*ProcessMenuItem) (int ID);

	/* Break Points */
	int	 UseBPoints;
	char BPPanelName[20];
	void (*Add_BPoint)(void);
	void (*CreateBPPanel)(HWND hDlg, RECT rcBox);
	void (*HideBPPanel)(void);
	void (*PaintBPPanel)(PAINTSTRUCT ps);
	void (*ShowBPPanel)(void);
	void (*RefreshBpoints)(HWND hList);
	void (*RemoveBpoint)(HWND hList, int index);
	void (*RemoveAllBpoint)(void);
	
	/* RSP command Window */
	void (*Enter_RSP_Commands_Window) (void);
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

typedef word (__cdecl* DORSPCYCLES)(word);
typedef void (__cdecl* GETRSPDEBUGINFO)(RSPDEBUG_INFO*);
typedef void (__cdecl* INITIATERSP)(RSP_INFO, word*);
typedef void (__cdecl* INITIATERSPDEBUGGER)(DEBUG_INFO);

/*
** The Class RSP is used to load the plugin RSP
** and contains functions and variables defined
** in the .dll plugin
*/
class RSP
{
public:
	static void dllAbout();			// Open the About window of the plugin
	static void dllConfig();		// Open the Config window of the plugin
	static void closeDLL(void);		// Closes the DLL
	static bool isLoaded(void);
private:
	static void dllTest();			// Notifies the user whether the plugin is correctly loaded or not
	static void romClosed(void);	// To call when the ROM is closed

	static bool				loaded;
	static HINSTANCE		hDLL;
	static HWND				hWnd;

	static CLOSEDLL			closeDLL_;
	static DLLABOUT			dllAbout_;
	static DLLCONFIG		dllConfig_;
	static DLLTEST			dllTest_;
	static GETDLLINFO		getDllInfo_;
	static ROMCLOSED		romClosed_;

	static PLUGIN_INFO*		plugin_info;

public:
	static bool load(string filename, HWND hWnd);	// Plugs the DLL into the RCP
	static bool init(void);

	static word doRspCycles(word);			// Allows the RSP to run in parrel with the CPU
	static void getRspDebugInfo(void);		// Retreives the debug info of the RSP
	static void initiateRSP(word*);			// Initializes the value of the RSP variables
	static void initiateRSPDebugger(void);	// Initializes the value of the RSP debugger variables

private:
	static DORSPCYCLES				doRspCycles_;
	static GETRSPDEBUGINFO			getRspDebugInfo_;
	static INITIATERSP				initiateRSP_;
	static INITIATERSPDEBUGGER		initiateRSPDebugger_;
	
	static RSP_INFO*				rsp_info;
	static RSPDEBUG_INFO*			rspdebug_info;
	static DEBUG_INFO*				debug_info;
};

