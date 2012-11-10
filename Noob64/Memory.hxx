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

#include "Rsp.h"
#include "Gfx.h"
#include "Rom.h"
#include "Rdram.h"
#include "RdramRegs.h"
#include "Sp.h"
#include "Dpc.h"
#include "Dps.h"
#include "Ai.h"
#include "Mi.h"
#include "Vi.h"
#include "Pi.h"
#include "Ri.h"
#include "Si.h"
#include "PifRom.h"
#include "PifRam.h"

inline bool MEM_SEG::contains(word address) const				{ return begining <= address && address <= end; }

inline bool MEMORY::isCheckInterrupt() const					{ return check_intr; }
inline void MEMORY::setCheckInterrupt(bool isCheckInterrupt)	{ check_intr = isCheckInterrupt; }

//****************************************************************************
//** READ															**
//****************************************************************************
template <typename Type>
Type MEMORY::read(word address)
{
	Type res;
	if (typeid(Type) == typeid(word) && read_from_register((word *) &res, address))
		return res;
	byte dst[sizeof(Type)];
	memcpy(dst, virtual_to_physical(address), sizeof(Type));
	res = binary_to_type<Type>(dst);
	return res;
}

// Get the value contains in the registes
inline bool MEMORY::read_from_register(word *data, word address)
{
	address &= 0x0FFFFFFF;
	if (address == RDRAM_CONFIG_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_DEVICE_ID_REG)
		*data = rdram_regs.getDeviceId();
	else if (address == RDRAM_DELAY_REG)
		*data = rdram_regs.getDelay();
	else if (address == RDRAM_MODE_REG)
		*data = rdram_regs.getMode();
	else if (address == RDRAM_REF_INTERVAL_REG)
		*data = rdram_regs.getRefInterval();
	else if (address == RDRAM_REF_ROW_REG)
		*data = rdram_regs.getRefRow();
	else if (address == RDRAM_RAS_INTERVAL_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_MIN_INTERVAL_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_ADDR_SELECT_REG)
		*data = rdram_regs.getConfig();
	else if (address == RDRAM_DEVICE_MANUF_REG)
		*data = rdram_regs.getConfig();

	else if (address == SP_MEM_ADDR_REG)
		*data = sp_regs.getMemAddr();
	else if (address == SP_DRAM_ADDR_REG)
		*data = sp_regs.getDramAddr();
	else if (address == SP_RD_LEN_REG)
		*data = sp_regs.getRdLen();
	else if (address == SP_WR_LEN_REG)
		*data = sp_regs.getWrLen();
	else if (address == SP_STATUS_REG)
		*data = sp_regs.getStatus();
	else if (address == SP_DMA_FULL_REG)
		*data = sp_regs.getDmaFull();
	else if (address == SP_DMA_BUSY_REG)
		*data = sp_regs.getDmaBusy();
	else if (address == SP_SEMAPHORE_REG)
		*data = sp_regs.getSemaphore();
	else if (address == SP_PC_REG)
		*data = sp_regs.getPc();
	else if (address == SP_IBIST_REG)
		*data = sp_regs.getIbist();

	else if (address == DPC_START_REG)
		*data = dpc_regs.getStart();
	else if (address == DPC_END_REG)
		*data = dpc_regs.getEnd();
	else if (address == DPC_CURRENT_REG)
		*data = dpc_regs.getCurrent();
	else if (address == DPC_STATUS_REG)
		*data = dpc_regs.getStatus();
	else if (address == DPC_CLOCK_REG)
		*data = dpc_regs.getClock();
	else if (address == DPC_BUFBUSY_REG)
		*data = dpc_regs.getBufBusy();
	else if (address == DPC_PIPEBUSY_REG)
		*data = dpc_regs.getPipeBusy();
	else if (address == DPC_TMEM_REG)
		*data = dpc_regs.getTmem();

	else if (address == DPS_TBIST_REG)
		*data = dps_regs.getTbist();
	else if (address == DPS_TEST_MODE_REG)
		*data = dps_regs.getTestMode();
	else if (address == DPS_BUFTEST_ADDR_REG)
		*data = dps_regs.getBufTestAddr();
	else if (address == DPS_BUFTEST_DATA_REG)
		*data = dps_regs.getBufTestData();

	else if (address == MI_INIT_MODE_REG)
		*data = mi_regs.getInitMode();
	else if (address == MI_VERSION_REG)
		*data = mi_regs.getVersion();
	else if (address == MI_INTR_REG)
		*data = mi_regs.getIntr();
	else if (address == MI_INTR_MASK_REG)
		*data = mi_regs.getIntrMask();

	else if (address == VI_STATUS_REG)
		*data = vi_regs.getStatus();
	else if (address == VI_ORIGIN_REG)
		*data = vi_regs.getOrigin();
	else if (address == VI_WIDTH_REG)
		*data = vi_regs.getWidth();
	else if (address == VI_INTR_REG)
		*data = vi_regs.getIntr();
	else if (address == VI_CURRENT_REG)
	{
		*data = vi_regs.getCurrent();
		//UpdateCurrentHalfLine();
	}
	else if (address == VI_BURST_REG)
		*data = vi_regs.getBurst();
	else if (address == VI_V_SYNC_REG)
		*data = vi_regs.getVsync();
	else if (address == VI_H_SYNC_REG)
		*data = vi_regs.getHsync();
	else if (address == VI_LEAP_REG)
		*data = vi_regs.getLeap();
	else if (address == VI_H_START_REG)
		*data = vi_regs.getHstart();
	else if (address == VI_V_START_REG)
		*data = vi_regs.getVstart();
	else if (address == VI_V_BURST_REG)
		*data = vi_regs.getVburst();
	else if (address == VI_X_SCALE_REG)
		*data = vi_regs.getXscale();
	else if (address == VI_Y_SCALE_REG)
		*data = vi_regs.getYscale();

	else if (address == AI_DRAM_ADDR_REG)
		*data = ai_regs.getDramAddr();
	else if (address == AI_LEN_REG)
	{
		*data = ai_regs.getLen();
		//res = AiReadLength();
	}
	else if (address == AI_CONTROL_REG)
		*data = ai_regs.getControl();
	else if (address == AI_STATUS_REG)
		*data = ai_regs.getStatus();
	else if (address == AI_DACRATE_REG)
		*data = ai_regs.getDacrate();
	else if (address == AI_BITRATE_REG)
		*data = ai_regs.getBitrate();

	else if (address == PI_DRAM_ADDR_REG)
		*data = pi_regs.getDramAddr();
	else if (address == PI_CART_ADDR_REG)
		*data = pi_regs.getCartAddr();
	else if (address == PI_RD_LEN_REG)
		*data = pi_regs.getRdLen();
	else if (address == PI_WR_LEN_REG)
		*data = pi_regs.getWrLen();
	else if (address == PI_STATUS_REG)
		*data = pi_regs.getStatus();
	else if (address == PI_BSD_DOM1_LAT_REG)
		*data = pi_regs.getBsdDom1Lat();
	else if (address == PI_BSD_DOM1_PWD_REG)
		*data = pi_regs.getBsdDom1Pwd();
	else if (address == PI_BSD_DOM1_PGS_REG)
		*data = pi_regs.getBsdDom1Pgs();
	else if (address == PI_BSD_DOM1_RLS_REG)
		*data = pi_regs.getBsdDom1Rls();
	else if (address == PI_BSD_DOM2_LAT_REG)
		*data = pi_regs.getBsdDom2Lat();
	else if (address == PI_BSD_DOM2_PWD_REG)
		*data = pi_regs.getBsdDom2Pwd();
	else if (address == PI_BSD_DOM2_PGS_REG)
		*data = pi_regs.getBsdDom2Pgs();
	else if (address == PI_BSD_DOM2_RLS_REG)
		*data = pi_regs.getBsdDom2Rls();

	else if (address == RI_MODE_REG)
		*data = ri_regs.getMode();
	else if (address == RI_CONFIG_REG)
		*data = ri_regs.getConfig();
	else if (address == RI_CURRENT_LOAD_REG)
		*data = ri_regs.getCurrentLoad();
	else if (address == RI_SELECT_REG)
		*data = ri_regs.getSelect();
	else if (address == RI_REFRESH_REG)
		*data = ri_regs.getRefresh();
	else if (address == RI_LATENCY_REG)
		*data = ri_regs.getLatency();
	else if (address == RI_RERROR_REG)
		*data = ri_regs.getRerror();
	else if (address == RI_WERROR_REG)
		*data = ri_regs.getWerror();

	else if (address == SI_DRAM_ADDR_REG)
		*data = si_regs.getDramAddr();
	else if (address == SI_PIF_ADDR_RD64B_REG)
		*data = si_regs.getPifAddrRd64b();
	else if (address == SI_PIF_ADDR_WR64B_REG)
		*data = si_regs.getPifAddrWr64b();
	else if (address == SI_STATUS_REG)
		*data = si_regs.getStatus();
	else
		return false;
	return true;
}

//****************************************************************************
//** WRITE																	**
//****************************************************************************
template <typename Type>
inline void MEMORY::write(Type data, word address)
{
	if (typeid(Type) == typeid(word) && write_in_register((word) data, address))
		return;

	void *dst = virtual_to_physical(address);
	data = type_to_binary<Type>(data);
	memcpy(dst, &data, sizeof(Type));
}

// Set the value of the registers
inline bool MEMORY::write_in_register(word data, word address)
{
	address &= 0x0FFFFFFF;
	if (address == RDRAM_CONFIG_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_DEVICE_ID_REG)
		rdram_regs.setDeviceId(data);
	else if (address == RDRAM_DELAY_REG)
		rdram_regs.setDelay(data);
	else if (address == RDRAM_MODE_REG)
		rdram_regs.setMode(data);
	else if (address == RDRAM_REF_INTERVAL_REG)
		rdram_regs.setRefInterval(data);
	else if (address == RDRAM_REF_ROW_REG)
		rdram_regs.setRefRow(data);
	else if (address == RDRAM_RAS_INTERVAL_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_MIN_INTERVAL_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_ADDR_SELECT_REG)
		rdram_regs.setConfig(data);
	else if (address == RDRAM_DEVICE_MANUF_REG)
		rdram_regs.setConfig(data);

	else if (address == SP_MEM_ADDR_REG)
		sp_regs.setMemAddr(data);
	else if (address == SP_DRAM_ADDR_REG)
		sp_regs.setDramAddr(data);
	else if (address == SP_RD_LEN_REG)
	{
		sp_regs.setRdLen(data);
		dma_sp_read();	
		sp_regs.setDmaBusy(0);
		sp_regs.setStatus(sp_regs.getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_WR_LEN_REG)
	{
		sp_regs.setWrLen(data);
		dma_sp_write();
		sp_regs.setDmaBusy(0);
		sp_regs.setStatus(sp_regs.getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_STATUS_REG)
	{
		sp_regs.setSpecialStatus(data);
		if (data & SP_SET_SIG0) 
		{
			mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_SP);
			check_intr = true;
		}
		if (data & SP_CLR_INTR)
		{ 
			mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_SP);
			//	RunRsp();
			check_intr = true;
		}
		else
			;//	RunRsp();
	}
	else if (address == SP_DMA_FULL_REG)
		sp_regs.setDmaFull(data);
	else if (address == SP_DMA_BUSY_REG)
		sp_regs.setDmaBusy(data);
	else if (address == SP_SEMAPHORE_REG)
		sp_regs.setSpecialSemaphore(data);
	else if (address == SP_PC_REG)
		sp_regs.setPc(data);
	else if (address == SP_IBIST_REG)
		sp_regs.setIbist(data);

	else if (address == DPC_START_REG)
		dpc_regs.setStart(data);
	else if (address == DPC_END_REG)
		dpc_regs.setEnd(data);
	else if (address == DPC_CURRENT_REG)
		dpc_regs.setCurrent(data);
	else if (address == DPC_STATUS_REG)
		dpc_regs.setStatus(data);
	else if (address == DPC_CLOCK_REG)
		dpc_regs.setClock(data);
	else if (address == DPC_BUFBUSY_REG)
		dpc_regs.setBufBusy(data);
	else if (address == DPC_PIPEBUSY_REG)
		dpc_regs.setPipeBusy(data);
	else if (address == DPC_TMEM_REG)
		dpc_regs.setTmem(data);

	else if (address == DPS_TBIST_REG)
		dps_regs.setTbist(data);
	else if (address == DPS_TEST_MODE_REG)
		dps_regs.setTestMode(data);
	else if (address == DPS_BUFTEST_ADDR_REG)
		dps_regs.setBufTestAddr(data);
	else if (address == DPS_BUFTEST_DATA_REG)
		dps_regs.setBufTestData(data);

	else if (address == MI_INIT_MODE_REG)
		mi_regs.setSpecialInitMode(data);
	else if (address == MI_VERSION_REG)
		mi_regs.setVersion(data);
	else if (address == MI_INTR_REG)
		mi_regs.setIntr(data);
	else if (address == MI_INTR_MASK_REG)
		mi_regs.setSpecialIntrMask(data);

	else if (address == VI_STATUS_REG)
		vi_regs.setStatus(data);
	else if (address == VI_ORIGIN_REG)
		vi_regs.setOrigin(data);
	else if (address == VI_WIDTH_REG)
		vi_regs.setWidth(data);
	else if (address == VI_INTR_REG)
	{
		vi_regs.setVintr(data);
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_VI);
		check_intr = true;
	}
	else if (address == VI_CURRENT_REG)
		vi_regs.setCurrent(data);
	else if (address == VI_BURST_REG)
		vi_regs.setBurst(data);
	else if (address == VI_V_SYNC_REG)
		vi_regs.setVsync(data);
	else if (address == VI_H_SYNC_REG)
		vi_regs.setHsync(data);
	else if (address == VI_LEAP_REG)
		vi_regs.setLeap(data);
	else if (address == VI_H_START_REG)
		vi_regs.setHstart(data);
	else if (address == VI_V_START_REG)
		vi_regs.setVstart(data);
	else if (address == VI_V_BURST_REG)
		vi_regs.setVburst(data);
	else if (address == VI_X_SCALE_REG)
		vi_regs.setXscale(data);
	else if (address == VI_Y_SCALE_REG)
		vi_regs.setYscale(data);

	else if (address == AI_DRAM_ADDR_REG)
		ai_regs.setDramAddr(data);
	else if (address == AI_LEN_REG)
		ai_regs.setLen(data);
	else if (address == AI_CONTROL_REG)
		ai_regs.setControl(data);
	else if (address == AI_STATUS_REG)
	{
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_AI);
		check_intr = true;
	}
	else if (address == AI_DACRATE_REG)
		ai_regs.setDacrate(data);
	else if (address == AI_BITRATE_REG)
		ai_regs.setBitrate(data);

	else if (address == PI_DRAM_ADDR_REG)
		pi_regs.setDramAddr(data);
	else if (address == PI_CART_ADDR_REG)
		pi_regs.setCartAddr(data);
	else if (address == PI_RD_LEN_REG)
	{
		pi_regs.setRdLen(data);
		dma_pi_read();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_PI);
		pi_regs.setStatus(pi_regs.getStatus() & ~PI_STATUS_DMA_BUSY);
		check_intr = true;
	}
	else if (address == PI_WR_LEN_REG)
	{
		pi_regs.setWrLen(data);
		dma_pi_write();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_PI);
		pi_regs.setStatus(pi_regs.getStatus() & ~PI_STATUS_DMA_BUSY);
		check_intr = true;
	}
	else if (address == PI_STATUS_REG)
	{
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_PI);
		check_intr = true;
	}
	else if (address == PI_BSD_DOM1_LAT_REG)
		pi_regs.setBsdDom1Lat(data);
	else if (address == PI_BSD_DOM1_PWD_REG)
		pi_regs.setBsdDom1Pwd(data);
	else if (address == PI_BSD_DOM1_PGS_REG)
		pi_regs.setBsdDom1Pgs(data);
	else if (address == PI_BSD_DOM1_RLS_REG)
		pi_regs.setBsdDom1Rls(data);
	else if (address == PI_BSD_DOM2_LAT_REG)
		pi_regs.setBsdDom2Lat(data);
	else if (address == PI_BSD_DOM2_PWD_REG)
		pi_regs.setBsdDom2Pwd(data);
	else if (address == PI_BSD_DOM2_PGS_REG)
		pi_regs.setBsdDom2Pgs(data);
	else if (address == PI_BSD_DOM2_RLS_REG)
		pi_regs.setBsdDom2Rls(data);

	else if (address == RI_MODE_REG)
		ri_regs.setMode(data);
	else if (address == RI_CONFIG_REG)
		ri_regs.setConfig(data);
	else if (address == RI_CURRENT_LOAD_REG)
		ri_regs.setCurrentLoad(data);
	else if (address == RI_SELECT_REG)
		ri_regs.setSelect(data);
	else if (address == RI_REFRESH_REG)
		ri_regs.setRefresh(data);
	else if (address == RI_LATENCY_REG)
		ri_regs.setLatency(data);
	else if (address == RI_RERROR_REG)
		ri_regs.setRerror(data);
	else if (address == RI_WERROR_REG)
		ri_regs.setWerror(data);

	else if (address == SI_DRAM_ADDR_REG)
		si_regs.setDramAddr(data);
	else if (address == SI_PIF_ADDR_RD64B_REG)
	{
		si_regs.setPifAddrRd64b(data);
		dma_si_read();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_SI);
		si_regs.setStatus(si_regs.getStatus() | SI_STATUS_INTERRUPT);
		check_intr = true;
	}
	else if (address == SI_PIF_ADDR_WR64B_REG)
	{
		si_regs.setPifAddrWr64b(data);
		dma_si_write();
		mi_regs.setIntr(mi_regs.getIntr() | MI_INTR_SI);
		si_regs.setStatus(si_regs.getStatus() | SI_STATUS_INTERRUPT);
		check_intr = true;
	}
	else if (address == SI_STATUS_REG)
	{
		si_regs.setSpecialStatus(data);
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_SI);
		check_intr = true;
	}
	else
		return false;
	return true;
}

//****************************************************************************
//** VIRTUAL TO PHYSICAL													**
//****************************************************************************
inline void* MEMORY::virtual_to_physical(word a)
{
	if (rdram.contains(a))		return rdram[a];
	if (rdram_regs.contains(a))	return rdram_regs[a];
	if (sp_regs.contains(a))	return sp_regs[a];
	if (dpc_regs.contains(a))	return dpc_regs[a];
	if (dps_regs.contains(a))	return dps_regs[a];
	if (mi_regs.contains(a))	return mi_regs[a];
	if (vi_regs.contains(a))	return vi_regs[a];
	if (ai_regs.contains(a))	return ai_regs[a];
	if (pi_regs.contains(a))	return pi_regs[a];
	if (ri_regs.contains(a))	return ri_regs[a];
	if (si_regs.contains(a))	return si_regs[a];
	if (rom.contains(a))		return rom[a];
	if (pif_rom.contains(a))	return pif_rom[a];
	if (pif_ram.contains(a))	return pif_ram[a];

	if (KSEG0 <= a && a <= KSEG1-1)		// Mirror of 0x0000 0000 to 0x1FFF FFFF
		return (virtual_to_physical(a-KSEG0));
	if (KSEG1 <= a && a <= KSEG2-1)		// Mirror of 0x0000 0000 to 0x1FFF FFFF
		return (virtual_to_physical(a-KSEG1));
	if (KSEG2 <= a && a <= KSEG3-1)		// TLB mapped
		throw TLB_NOT_HANDLED;
	if (KSEG3 <= a && a <= 0xFFFFFFFF)	// TLB mapped
		throw TLB_NOT_HANDLED;

	cerr << endl << "ERROR: Virtual address 0x" << hex << a << " not handled" << endl;
	throw VIRTUAL_ADDRESS_ERROR;
}









