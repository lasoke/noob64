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
#include "Audio.h"

bool				AUDIO::loaded = false;
HINSTANCE			AUDIO::hDLL = 0;
HWND				AUDIO::hWnd = 0;
CLOSEDLL			AUDIO::closeDLL_ = 0;
DLLABOUT			AUDIO::dllAbout_ = 0;
DLLCONFIG			AUDIO::dllConfig_ = 0;
DLLTEST				AUDIO::dllTest_ = 0;
GETDLLINFO			AUDIO::getDllInfo_ = 0;
ROMCLOSED			AUDIO::romClosed_ = 0;
PLUGIN_INFO*		AUDIO::plugin_info = 0;

AIDACRATECHANGED	AUDIO::aiDacrateChanged_ = 0;
AILENCHANGED		AUDIO::aiLenChanged_ = 0;
AIREADLENGTH		AUDIO::aiReadLength_ = 0;
AIUPDATE			AUDIO::aiUpdate_ = 0;
INITIATEAUDIO		AUDIO::initiateAudio_ = 0;
PROCESSALIST		AUDIO::processAList_ = 0;
AUDIO_INFO*			AUDIO::audio_info = 0;

bool AUDIO::load(string filename, HWND handle)
{
	if (!(hDLL = LoadLibrary(filename.c_str())))
		return loaded = false;

	hWnd						= handle;

	closeDLL_					= (CLOSEDLL) GetProcAddress(hDLL, "CloseDLL");
	dllAbout_					= (DLLABOUT) GetProcAddress(hDLL, "DllAbout");
	dllConfig_					= (DLLCONFIG) GetProcAddress(hDLL, "DllConfig");
	dllTest_					= (DLLTEST)	GetProcAddress(hDLL, "DllTest");
	getDllInfo_					= (GETDLLINFO) GetProcAddress(hDLL, "GetDllInfo");
	romClosed_					= (ROMCLOSED) GetProcAddress(hDLL, "RomClosed");
	aiDacrateChanged_			= (AIDACRATECHANGED) GetProcAddress(hDLL, "AiDacrateChanged");
	aiLenChanged_				= (AILENCHANGED) GetProcAddress(hDLL, "AiLenChanged");
	aiReadLength_				= (AIREADLENGTH) GetProcAddress(hDLL, "AiReadLength");
	aiUpdate_					= (AIUPDATE) GetProcAddress(hDLL, "AiUpdate");
	initiateAudio_				= (INITIATEAUDIO) GetProcAddress(hDLL, "InitiateAudio");
	processAList_				= (PROCESSALIST) GetProcAddress(hDLL, "ProcessAList");

	if (!initiateAudio_) return loaded = false;

	plugin_info					= (PLUGIN_INFO*) malloc(sizeof(PLUGIN_INFO));
	getDllInfo_(plugin_info);

	return loaded = true;
}

bool AUDIO::init(void)
{
	if (!loaded) return false;

	audio_info					= (AUDIO_INFO*) malloc(sizeof(AUDIO_INFO));

	audio_info->hWnd			= hWnd;	// Render window
	audio_info->hInst			= hDLL;	// Instance handle
	audio_info->memoryBswaped	= TRUE;	// plugin_info->memoryBswaped;

	audio_info->header			= (byte*) MMU::get(ROM_SEG_BEG);
	audio_info->rdram			= (byte*) MMU::get(RDRAM_SEG_BEG);
	audio_info->dmem			= (byte*) MMU::get(SP_DMEM);
	audio_info->imem			= (byte*) MMU::get(SP_IMEM);

	audio_info->mi_intr_reg		= (word*) MMU::get(MI_INTR_REG);

	audio_info->ai_dram_addr_reg= (word*) MMU::get(AI_DRAM_ADDR_REG);
	audio_info->ai_len_reg		= (word*) MMU::get(AI_LEN_REG);
	audio_info->ai_control_reg	= (word*) MMU::get(AI_CONTROL_REG);
	audio_info->ai_status_reg	= (word*) MMU::get(AI_STATUS_REG);
	audio_info->ai_dacrate_reg	= (word*) MMU::get(AI_DACRATE_REG);
	audio_info->ai_bitrate_reg	= (word*) MMU::get(AI_BITRATE_REG);

	audio_info->CheckInterrupts	= &R4300i::check_interrupt;

	if (!initiateAudio()) return false;

	return true;
}

void AUDIO::closeDLL()
{
	return closeDLL_();
}

void AUDIO::dllAbout()
{
	return dllAbout_(hWnd);
}

void AUDIO::dllConfig()
{
	return dllConfig_(hWnd);
}

void AUDIO::dllTest()
{
	return dllTest_(hWnd);
}

void AUDIO::romClosed()
{
	return romClosed_();
}

void AUDIO::aiDacrateChanged(int systemType)
{
	return aiDacrateChanged_(systemType);
}

void AUDIO::aiLenChanged(void)
{
	return aiLenChanged_();
}

word AUDIO::aiReadLength(void)
{
	return aiReadLength_();
}

void AUDIO::aiUpdate(int wait)
{
	return aiUpdate_(wait);
}

bool AUDIO::initiateAudio()
{
	return initiateAudio_(*audio_info);
}

void AUDIO::processAList(void)
{
	return processAList_();
}

bool AUDIO::isLoaded(void)
{
	return loaded;
}