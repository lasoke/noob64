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

#include "Mi.h"

inline void MI::setInitMode(word w)		{ data.init_mode = w; }
inline void MI::setSpecialInitMode(word w)
{
	if (w & MI_CLR_INIT)		data.init_mode &= ~MI_MODE_INIT;
	if (w & MI_CLR_EBUS)		data.init_mode &= ~MI_MODE_EBUS;
	if (w & MI_CLR_RDRAM)		data.init_mode &= ~MI_MODE_RDRAM;

	if (w & MI_SET_INIT)		data.init_mode |= MI_MODE_INIT;
	if (w & MI_SET_EBUS)		data.init_mode |= MI_MODE_EBUS;
	if (w & MI_SET_RDRAM)		data.init_mode |= MI_MODE_RDRAM;

	if (w & MI_CLR_DP_INTR)		data.intr &= ~MI_INTR_DP;
}
inline void MI::setVersion(word w)			{ data.version = w; }
inline void MI::setIntr(word w)			{ data.intr = w; }
inline void MI::setIntrMask(word w)		{ data.intr_mask = w; }
inline void MI::setSpecialIntrMask(word w)
{
	if (w & MI_INTR_MASK_CLR_SP) data.intr_mask &= ~MI_INTR_MASK_SP;
	if (w & MI_INTR_MASK_CLR_SI) data.intr_mask &= ~MI_INTR_MASK_SI;
	if (w & MI_INTR_MASK_CLR_AI) data.intr_mask &= ~MI_INTR_MASK_AI;
	if (w & MI_INTR_MASK_CLR_VI) data.intr_mask &= ~MI_INTR_MASK_VI;
	if (w & MI_INTR_MASK_CLR_PI) data.intr_mask &= ~MI_INTR_MASK_PI;
	if (w & MI_INTR_MASK_CLR_DP) data.intr_mask &= ~MI_INTR_MASK_DP;

	if (w & MI_INTR_MASK_SET_SP) data.intr_mask |= MI_INTR_MASK_SP;
	if (w & MI_INTR_MASK_SET_SI) data.intr_mask |= MI_INTR_MASK_SI;
	if (w & MI_INTR_MASK_SET_AI) data.intr_mask |= MI_INTR_MASK_AI;
	if (w & MI_INTR_MASK_SET_VI) data.intr_mask |= MI_INTR_MASK_VI;
	if (w & MI_INTR_MASK_SET_PI) data.intr_mask |= MI_INTR_MASK_PI;
	if (w & MI_INTR_MASK_SET_DP) data.intr_mask |= MI_INTR_MASK_DP;
}

inline word MI::getInitMode()				{ return data.init_mode; }
inline word MI::getVersion()				{ return data.version; }
inline word MI::getIntr()					{ return data.intr; }
inline word MI::getIntrMask()				{ return data.intr_mask; }
