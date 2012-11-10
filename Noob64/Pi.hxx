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

#include "Pi.h"

inline void PI::setDramAddr(word w)		{ data.dram_addr = w; }
inline void PI::setCartAddr(word w)		{ data.cart_addr = w; }
inline void PI::setRdLen(word w)			{ data.rd_len = w; }
inline void PI::setWrLen(word w)			{ data.wr_len = w; }
inline void PI::setStatus(word w)			{ data.status = w; }
inline void PI::setBsdDom1Lat(word w)		{ data.bsd_dom1_lat = w; }
inline void PI::setBsdDom1Pwd(word w)		{ data.bsd_dom1_pwd = w; }
inline void PI::setBsdDom1Pgs(word w)		{ data.bsd_dom1_pgs = w; }
inline void PI::setBsdDom1Rls(word w)		{ data.bsd_dom1_rls = w; }
inline void PI::setBsdDom2Lat(word w)		{ data.bsd_dom2_lat = w; }
inline void PI::setBsdDom2Pwd(word w)		{ data.bsd_dom2_pwd = w; }
inline void PI::setBsdDom2Pgs(word w)		{ data.bsd_dom2_pgs = w; }
inline void PI::setBsdDom2Rls(word w)		{ data.bsd_dom2_rls = w; }

inline word PI::getDramAddr()				{ return data.dram_addr; }
inline word PI::getCartAddr()				{ return data.cart_addr; }
inline word PI::getRdLen()					{ return data.rd_len; }
inline word PI::getWrLen()					{ return data.wr_len; }
inline word PI::getStatus()				{ return data.status; }
inline word PI::getBsdDom1Lat()			{ return data.bsd_dom1_lat; }
inline word PI::getBsdDom1Pwd()			{ return data.bsd_dom1_pwd; }
inline word PI::getBsdDom1Pgs()			{ return data.bsd_dom1_pgs; }
inline word PI::getBsdDom1Rls()			{ return data.bsd_dom1_rls; }
inline word PI::getBsdDom2Lat()			{ return data.bsd_dom2_lat; }
inline word PI::getBsdDom2Pwd()			{ return data.bsd_dom2_pwd; }
inline word PI::getBsdDom2Pgs()			{ return data.bsd_dom2_pgs; }
inline word PI::getBsdDom2Rls()			{ return data.bsd_dom2_rls; }
