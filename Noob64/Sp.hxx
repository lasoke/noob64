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

#include "Sp.h"

inline void SP::setMemAddr(word w)			{ data.mem_addr = w; }
inline void SP::setDramAddr(word w)			{ data.dram_addr = w; }
inline void SP::setRdLen(word w)			{ data.rd_len = w; }
inline void SP::setWrLen(word w)			{ data.wr_len = w; }
inline void SP::setStatus(word w)			{ data.status = w; }
inline void SP::setSpecialStatus(word w)
{ 
	if (w & SP_CLR_HALT)		data.status &= ~SP_STATUS_HALT;
	if (w & SP_CLR_BROKE)		data.status &= ~SP_STATUS_BROKE;
	if (w & SP_CLR_SSTEP)		data.status &= ~SP_STATUS_SSTEP;
	if (w & SP_CLR_INTR_BREAK)	data.status &= ~SP_STATUS_INTR_BREAK;
	if (w & SP_CLR_SIG0)		data.status &= ~SP_STATUS_SIG0;
	if (w & SP_CLR_SIG1)		data.status &= ~SP_STATUS_SIG1;
	if (w & SP_CLR_SIG2)		data.status &= ~SP_STATUS_SIG2;
	if (w & SP_CLR_SIG3)		data.status &= ~SP_STATUS_SIG3;
	if (w & SP_CLR_SIG4)		data.status &= ~SP_STATUS_SIG4;
	if (w & SP_CLR_SIG5)		data.status &= ~SP_STATUS_SIG5;
	if (w & SP_CLR_SIG6)		data.status &= ~SP_STATUS_SIG6;
	if (w & SP_CLR_SIG7)		data.status &= ~SP_STATUS_SIG7;

	if (w & SP_SET_HALT)		data.status |= SP_STATUS_HALT;
	if (w & SP_SET_SSTEP)		data.status |= SP_STATUS_SSTEP;
	if (w & SP_SET_INTR_BREAK)	data.status |= SP_STATUS_INTR_BREAK;
	if (w & SP_SET_SIG0)		data.status |= SP_STATUS_SIG0;
	if (w & SP_SET_SIG1)		data.status |= SP_STATUS_SIG1;
	if (w & SP_SET_SIG2)		data.status |= SP_STATUS_SIG2;
	if (w & SP_SET_SIG3)		data.status |= SP_STATUS_SIG3;
	if (w & SP_SET_SIG4)		data.status |= SP_STATUS_SIG4;
	if (w & SP_SET_SIG5)		data.status |= SP_STATUS_SIG5;
	if (w & SP_SET_SIG6)		data.status |= SP_STATUS_SIG6;
	if (w & SP_SET_SIG7)		data.status |= SP_STATUS_SIG7;
}
inline void SP::setDmaFull(word w)			{ data.dma_full = w; }
inline void SP::setDmaBusy(word w)			{ data.dma_busy = w; }
inline void SP::setSemaphore(word w)		{ data.semaphore = w; }
inline void SP::setSpecialSemaphore(word w){ data.semaphore = 0; }
inline void SP::setPc(word w)				{ data.pc = w & 0xFFC; }
inline void SP::setIbist(word w)			{ data.ibist = w; }

inline byte* SP::getDmem()					{ return data.dmem; }
inline byte* SP::getImem()					{ return data.imem; }
inline word SP::getMemAddr()				{ return data.mem_addr; }
inline word SP::getDramAddr()				{ return data.dram_addr; }
inline word SP::getRdLen()					{ return data.rd_len; }
inline word SP::getWrLen()					{ return data.wr_len; }
inline word SP::getStatus()				{ return data.status; }
inline word SP::getDmaFull()				{ return data.dma_full; }
inline word SP::getDmaBusy()				{ return data.dma_busy; }
inline word SP::getSemaphore()				{ return data.semaphore; }
inline word SP::getPc()					{ return data.pc; }
inline word SP::getIbist()					{ return data.ibist; }