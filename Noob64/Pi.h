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
 * chwing money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#pragma once

#include "Rcp.h"

#define PI_SEG_BEG				0x04600000
#define PI_SEG_END				0x046FFFFF

#define PI_DRAM_ADDR_REG		0x04600000
#define PI_CART_ADDR_REG		0x04600004
#define PI_RD_LEN_REG			0x04600008
#define PI_WR_LEN_REG			0x0460000C
#define PI_STATUS_REG			0x04600010
#define PI_BSD_DOM1_LAT_REG		0x04600014
#define PI_BSD_DOM1_PWD_REG		0x04600018
#define PI_BSD_DOM1_PGS_REG		0x0460001C
#define PI_BSD_DOM1_RLS_REG		0x04600020
#define PI_BSD_DOM2_LAT_REG		0x04600024
#define PI_BSD_DOM2_PWD_REG		0x04600028
#define PI_BSD_DOM2_PGS_REG		0x0460002C
#define PI_BSD_DOM2_RLS_REG		0x04600030

#define	PI_STATUS_DMA_BUSY		0x01
#define	PI_STATUS_IO_BUSY		0x02
#define	PI_STATUS_ERROR			0x04

#define	PI_SET_RESET			0x01
#define	PI_CLR_INTR				0x02

//****************************************************************************
//** Peripheral Interface (PI) Registers									**
//****************************************************************************

class PI : public MEM_SEG
{
public:
	PI();

	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getCartAddr();
	inline void setCartAddr(word);
	inline word getRdLen();
	inline void setRdLen(word);
	inline word getWrLen();
	inline void setWrLen(word);
	inline word getStatus();
	inline void setStatus(word);
	inline word getBsdDom1Lat();
	inline void setBsdDom1Lat(word);
	inline word getBsdDom1Pwd();
	inline void setBsdDom1Pwd(word);
	inline word getBsdDom1Pgs();
	inline void setBsdDom1Pgs(word);
	inline word getBsdDom1Rls();
	inline void setBsdDom1Rls(word);
	inline word getBsdDom2Lat();
	inline void setBsdDom2Lat(word);
	inline word getBsdDom2Pwd();
	inline void setBsdDom2Pwd(word);
	inline word getBsdDom2Pgs();
	inline void setBsdDom2Pgs(word);
	inline word getBsdDom2Rls();
	inline void setBsdDom2Rls(word);

private:
	struct	{
		word dram_addr;
		word cart_addr;
		word rd_len;
		word wr_len;
		word status;
		word bsd_dom1_lat;
		word bsd_dom1_pwd;
		word bsd_dom1_pgs;
		word bsd_dom1_rls;
		word bsd_dom2_lat;
		word bsd_dom2_pwd;
		word bsd_dom2_pgs;
		word bsd_dom2_rls;
		byte unused[0xFFFCC];
	} data;
};