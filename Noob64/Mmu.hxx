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

#include "Mmu.h"

//****************************************************************************
//** READ																	**
//****************************************************************************
template <typename Type>
Type MMU::read(word address)
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
inline bool MMU::read_from_register(word *data, word address)
{
	address &= 0x0FFFFFFF;
	if (address == RDRAM_CONFIG_REG)
		*data = rcp.rdram_regs.getConfig();
	else if (address == RDRAM_DEVICE_ID_REG)
		*data = rcp.rdram_regs.getDeviceId();
	else if (address == RDRAM_DELAY_REG)
		*data = rcp.rdram_regs.getDelay();
	else if (address == RDRAM_MODE_REG)
		*data = rcp.rdram_regs.getMode();
	else if (address == RDRAM_REF_INTERVAL_REG)
		*data = rcp.rdram_regs.getRefInterval();
	else if (address == RDRAM_REF_ROW_REG)
		*data = rcp.rdram_regs.getRefRow();
	else if (address == RDRAM_RAS_INTERVAL_REG)
		*data = rcp.rdram_regs.getConfig();
	else if (address == RDRAM_MIN_INTERVAL_REG)
		*data = rcp.rdram_regs.getConfig();
	else if (address == RDRAM_ADDR_SELECT_REG)
		*data = rcp.rdram_regs.getConfig();
	else if (address == RDRAM_DEVICE_MANUF_REG)
		*data = rcp.rdram_regs.getConfig();

	else if (address == SP_MEM_ADDR_REG)
		*data = rcp.sp.getMemAddr();
	else if (address == SP_DRAM_ADDR_REG)
		*data = rcp.sp.getDramAddr();
	else if (address == SP_RD_LEN_REG)
		*data = rcp.sp.getRdLen();
	else if (address == SP_WR_LEN_REG)
		*data = rcp.sp.getWrLen();
	else if (address == SP_STATUS_REG)
		*data = rcp.sp.getStatus();
	else if (address == SP_DMA_FULL_REG)
		*data = rcp.sp.getDmaFull();
	else if (address == SP_DMA_BUSY_REG)
		*data = rcp.sp.getDmaBusy();
	else if (address == SP_SEMAPHORE_REG)
		*data = rcp.sp.getSemaphore();
	else if (address == SP_PC_REG)
		*data = rcp.sp.getPc();
	else if (address == SP_IBIST_REG)
		*data = rcp.sp.getIbist();

	else if (address == DPC_START_REG)
		*data = rcp.dpc.getStart();
	else if (address == DPC_END_REG)
		*data = rcp.dpc.getEnd();
	else if (address == DPC_CURRENT_REG)
		*data = rcp.dpc.getCurrent();
	else if (address == DPC_STATUS_REG)
		*data = rcp.dpc.getStatus();
	else if (address == DPC_CLOCK_REG)
		*data = rcp.dpc.getClock();
	else if (address == DPC_BUFBUSY_REG)
		*data = rcp.dpc.getBufBusy();
	else if (address == DPC_PIPEBUSY_REG)
		*data = rcp.dpc.getPipeBusy();
	else if (address == DPC_TMEM_REG)
		*data = rcp.dpc.getTmem();

	else if (address == DPS_TBIST_REG)
		*data = rcp.dps.getTbist();
	else if (address == DPS_TEST_MODE_REG)
		*data = rcp.dps.getTestMode();
	else if (address == DPS_BUFTEST_ADDR_REG)
		*data = rcp.dps.getBufTestAddr();
	else if (address == DPS_BUFTEST_DATA_REG)
		*data = rcp.dps.getBufTestData();

	else if (address == MI_INIT_MODE_REG)
		*data = rcp.mi.getInitMode();
	else if (address == MI_VERSION_REG)
		*data = rcp.mi.getVersion();
	else if (address == MI_INTR_REG)
		*data = rcp.mi.getIntr();
	else if (address == MI_INTR_MASK_REG)
		*data = rcp.mi.getIntrMask();

	else if (address == VI_STATUS_REG)
		*data = rcp.vi.getStatus();
	else if (address == VI_ORIGIN_REG)
		*data = rcp.vi.getOrigin();
	else if (address == VI_WIDTH_REG)
		*data = rcp.vi.getWidth();
	else if (address == VI_INTR_REG)
		*data = rcp.vi.getIntr();
	else if (address == VI_CURRENT_REG)
	{
		*data = rcp.vi.getCurrent();
		//UpdateCurrentHalfLine();
	}
	else if (address == VI_BURST_REG)
		*data = rcp.vi.getBurst();
	else if (address == VI_V_SYNC_REG)
		*data = rcp.vi.getVsync();
	else if (address == VI_H_SYNC_REG)
		*data = rcp.vi.getHsync();
	else if (address == VI_LEAP_REG)
		*data = rcp.vi.getLeap();
	else if (address == VI_H_START_REG)
		*data = rcp.vi.getHstart();
	else if (address == VI_V_START_REG)
		*data = rcp.vi.getVstart();
	else if (address == VI_V_BURST_REG)
		*data = rcp.vi.getVburst();
	else if (address == VI_X_SCALE_REG)
		*data = rcp.vi.getXscale();
	else if (address == VI_Y_SCALE_REG)
		*data = rcp.vi.getYscale();

	else if (address == AI_DRAM_ADDR_REG)
		*data = rcp.ai.getDramAddr();
	else if (address == AI_LEN_REG)
	{
		*data = rcp.ai.getLen();
		//res = AiReadLength();
	}
	else if (address == AI_CONTROL_REG)
		*data = rcp.ai.getControl();
	else if (address == AI_STATUS_REG)
		*data = rcp.ai.getStatus();
	else if (address == AI_DACRATE_REG)
		*data = rcp.ai.getDacrate();
	else if (address == AI_BITRATE_REG)
		*data = rcp.ai.getBitrate();

	else if (address == PI_DRAM_ADDR_REG)
		*data = rcp.pi.getDramAddr();
	else if (address == PI_CART_ADDR_REG)
		*data = rcp.pi.getCartAddr();
	else if (address == PI_RD_LEN_REG)
		*data = rcp.pi.getRdLen();
	else if (address == PI_WR_LEN_REG)
		*data = rcp.pi.getWrLen();
	else if (address == PI_STATUS_REG)
		*data = rcp.pi.getStatus();
	else if (address == PI_BSD_DOM1_LAT_REG)
		*data = rcp.pi.getBsdDom1Lat();
	else if (address == PI_BSD_DOM1_PWD_REG)
		*data = rcp.pi.getBsdDom1Pwd();
	else if (address == PI_BSD_DOM1_PGS_REG)
		*data = rcp.pi.getBsdDom1Pgs();
	else if (address == PI_BSD_DOM1_RLS_REG)
		*data = rcp.pi.getBsdDom1Rls();
	else if (address == PI_BSD_DOM2_LAT_REG)
		*data = rcp.pi.getBsdDom2Lat();
	else if (address == PI_BSD_DOM2_PWD_REG)
		*data = rcp.pi.getBsdDom2Pwd();
	else if (address == PI_BSD_DOM2_PGS_REG)
		*data = rcp.pi.getBsdDom2Pgs();
	else if (address == PI_BSD_DOM2_RLS_REG)
		*data = rcp.pi.getBsdDom2Rls();

	else if (address == RI_MODE_REG)
		*data = rcp.ri.getMode();
	else if (address == RI_CONFIG_REG)
		*data = rcp.ri.getConfig();
	else if (address == RI_CURRENT_LOAD_REG)
		*data = rcp.ri.getCurrentLoad();
	else if (address == RI_SELECT_REG)
		*data = rcp.ri.getSelect();
	else if (address == RI_REFRESH_REG)
		*data = rcp.ri.getRefresh();
	else if (address == RI_LATENCY_REG)
		*data = rcp.ri.getLatency();
	else if (address == RI_RERROR_REG)
		*data = rcp.ri.getRerror();
	else if (address == RI_WERROR_REG)
		*data = rcp.ri.getWerror();

	else if (address == SI_DRAM_ADDR_REG)
		*data = rcp.si.getDramAddr();
	else if (address == SI_PIF_ADDR_RD64B_REG)
		*data = rcp.si.getPifAddrRd64b();
	else if (address == SI_PIF_ADDR_WR64B_REG)
		*data = rcp.si.getPifAddrWr64b();
	else if (address == SI_STATUS_REG)
		*data = rcp.si.getStatus();
	else
		return false;
	return true;
}

//****************************************************************************
//** WRITE																	**
//****************************************************************************
template <typename Type>
inline void MMU::write(Type data, word address)
{
	if (typeid(Type) == typeid(word) && write_in_register((word) data, address))
		return;

	void *dst = virtual_to_physical(address);
	data = type_to_binary<Type>(data);
	memcpy(dst, &data, sizeof(Type));
}

// Set the value of the registers
inline bool MMU::write_in_register(word data, word address)
{
	address &= 0x0FFFFFFF;
	if (address == RDRAM_CONFIG_REG)
		rcp.rdram_regs.setConfig(data);
	else if (address == RDRAM_DEVICE_ID_REG)
		rcp.rdram_regs.setDeviceId(data);
	else if (address == RDRAM_DELAY_REG)
		rcp.rdram_regs.setDelay(data);
	else if (address == RDRAM_MODE_REG)
		rcp.rdram_regs.setMode(data);
	else if (address == RDRAM_REF_INTERVAL_REG)
		rcp.rdram_regs.setRefInterval(data);
	else if (address == RDRAM_REF_ROW_REG)
		rcp.rdram_regs.setRefRow(data);
	else if (address == RDRAM_RAS_INTERVAL_REG)
		rcp.rdram_regs.setConfig(data);
	else if (address == RDRAM_MIN_INTERVAL_REG)
		rcp.rdram_regs.setConfig(data);
	else if (address == RDRAM_ADDR_SELECT_REG)
		rcp.rdram_regs.setConfig(data);
	else if (address == RDRAM_DEVICE_MANUF_REG)
		rcp.rdram_regs.setConfig(data);

	else if (address == SP_MEM_ADDR_REG)
		rcp.sp.setMemAddr(data);
	else if (address == SP_DRAM_ADDR_REG)
		rcp.sp.setDramAddr(data);
	else if (address == SP_RD_LEN_REG)
	{
		rcp.sp.setRdLen(data);
		rcp.dma_sp_read();	
		rcp.sp.setDmaBusy(0);
		rcp.sp.setStatus(rcp.sp.getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_WR_LEN_REG)
	{
		rcp.sp.setWrLen(data);
		rcp.dma_sp_write();
		rcp.sp.setDmaBusy(0);
		rcp.sp.setStatus(rcp.sp.getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_STATUS_REG)
	{
		rcp.sp.setSpecialStatus(data);
		if (data & SP_SET_SIG0) 
		{
			rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_SP);
			rcp.setCheckInterrupt(true);
		}
		if (data & SP_CLR_INTR)
		{ 
			rcp.mi.setIntr(rcp.mi.getIntr() & ~MI_INTR_SP);
			// TODO: RunRsp();
			rcp.setCheckInterrupt(true);
		}
		else
			;// TODO: RunRsp();
	}
	else if (address == SP_DMA_FULL_REG)
		rcp.sp.setDmaFull(data);
	else if (address == SP_DMA_BUSY_REG)
		rcp.sp.setDmaBusy(data);
	else if (address == SP_SEMAPHORE_REG)
		rcp.sp.setSpecialSemaphore(data);
	else if (address == SP_PC_REG)
		rcp.sp.setPc(data);
	else if (address == SP_IBIST_REG)
		rcp.sp.setIbist(data);

	else if (address == DPC_START_REG)
		rcp.dpc.setStart(data);
	else if (address == DPC_END_REG)
		rcp.dpc.setEnd(data);
	else if (address == DPC_CURRENT_REG)
		rcp.dpc.setCurrent(data);
	else if (address == DPC_STATUS_REG)
		rcp.dpc.setStatus(data);
	else if (address == DPC_CLOCK_REG)
		rcp.dpc.setClock(data);
	else if (address == DPC_BUFBUSY_REG)
		rcp.dpc.setBufBusy(data);
	else if (address == DPC_PIPEBUSY_REG)
		rcp.dpc.setPipeBusy(data);
	else if (address == DPC_TMEM_REG)
		rcp.dpc.setTmem(data);

	else if (address == DPS_TBIST_REG)
		rcp.dps.setTbist(data);
	else if (address == DPS_TEST_MODE_REG)
		rcp.dps.setTestMode(data);
	else if (address == DPS_BUFTEST_ADDR_REG)
		rcp.dps.setBufTestAddr(data);
	else if (address == DPS_BUFTEST_DATA_REG)
		rcp.dps.setBufTestData(data);

	else if (address == MI_INIT_MODE_REG)
		rcp.mi.setSpecialInitMode(data);
	else if (address == MI_VERSION_REG)
		rcp.mi.setVersion(data);
	else if (address == MI_INTR_REG)
		rcp.mi.setIntr(data);
	else if (address == MI_INTR_MASK_REG)
		rcp.mi.setSpecialIntrMask(data);

	else if (address == VI_STATUS_REG)
		rcp.vi.setStatus(data);
	else if (address == VI_ORIGIN_REG)
		rcp.vi.setOrigin(data);
	else if (address == VI_WIDTH_REG)
		rcp.vi.setWidth(data);
	else if (address == VI_INTR_REG)
	{
		rcp.vi.setVintr(data);
		rcp.mi.setIntr(rcp.mi.getIntr() & ~MI_INTR_VI);
		rcp.setCheckInterrupt(true);
	}
	else if (address == VI_CURRENT_REG)
		rcp.vi.setCurrent(data);
	else if (address == VI_BURST_REG)
		rcp.vi.setBurst(data);
	else if (address == VI_V_SYNC_REG)
		rcp.vi.setVsync(data);
	else if (address == VI_H_SYNC_REG)
		rcp.vi.setHsync(data);
	else if (address == VI_LEAP_REG)
		rcp.vi.setLeap(data);
	else if (address == VI_H_START_REG)
		rcp.vi.setHstart(data);
	else if (address == VI_V_START_REG)
		rcp.vi.setVstart(data);
	else if (address == VI_V_BURST_REG)
		rcp.vi.setVburst(data);
	else if (address == VI_X_SCALE_REG)
		rcp.vi.setXscale(data);
	else if (address == VI_Y_SCALE_REG)
		rcp.vi.setYscale(data);

	else if (address == AI_DRAM_ADDR_REG)
		rcp.ai.setDramAddr(data);
	else if (address == AI_LEN_REG)
		rcp.ai.setLen(data);
	else if (address == AI_CONTROL_REG)
		rcp.ai.setControl(data);
	else if (address == AI_STATUS_REG)
	{
		rcp.mi.setIntr(rcp.mi.getIntr() & ~MI_INTR_AI);
		rcp.setCheckInterrupt(true);
	}
	else if (address == AI_DACRATE_REG)
		rcp.ai.setDacrate(data);
	else if (address == AI_BITRATE_REG)
		rcp.ai.setBitrate(data);

	else if (address == PI_DRAM_ADDR_REG)
		rcp.pi.setDramAddr(data);
	else if (address == PI_CART_ADDR_REG)
		rcp.pi.setCartAddr(data);
	else if (address == PI_RD_LEN_REG)
	{
		rcp.pi.setRdLen(data);
		rcp.dma_pi_read();
		rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_PI);
		rcp.pi.setStatus(rcp.pi.getStatus() & ~PI_STATUS_DMA_BUSY);
		rcp.setCheckInterrupt(true);
	}
	else if (address == PI_WR_LEN_REG)
	{
		rcp.pi.setWrLen(data);
		rcp.dma_pi_write();
		rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_PI);
		rcp.pi.setStatus(rcp.pi.getStatus() & ~PI_STATUS_DMA_BUSY);
		rcp.setCheckInterrupt(true);
	}
	else if (address == PI_STATUS_REG)
	{
		rcp.mi.setIntr(rcp.mi.getIntr() & ~MI_INTR_PI);
		rcp.setCheckInterrupt(true);
	}
	else if (address == PI_BSD_DOM1_LAT_REG)
		rcp.pi.setBsdDom1Lat(data);
	else if (address == PI_BSD_DOM1_PWD_REG)
		rcp.pi.setBsdDom1Pwd(data);
	else if (address == PI_BSD_DOM1_PGS_REG)
		rcp.pi.setBsdDom1Pgs(data);
	else if (address == PI_BSD_DOM1_RLS_REG)
		rcp.pi.setBsdDom1Rls(data);
	else if (address == PI_BSD_DOM2_LAT_REG)
		rcp.pi.setBsdDom2Lat(data);
	else if (address == PI_BSD_DOM2_PWD_REG)
		rcp.pi.setBsdDom2Pwd(data);
	else if (address == PI_BSD_DOM2_PGS_REG)
		rcp.pi.setBsdDom2Pgs(data);
	else if (address == PI_BSD_DOM2_RLS_REG)
		rcp.pi.setBsdDom2Rls(data);

	else if (address == RI_MODE_REG)
		rcp.ri.setMode(data);
	else if (address == RI_CONFIG_REG)
		rcp.ri.setConfig(data);
	else if (address == RI_CURRENT_LOAD_REG)
		rcp.ri.setCurrentLoad(data);
	else if (address == RI_SELECT_REG)
		rcp.ri.setSelect(data);
	else if (address == RI_REFRESH_REG)
		rcp.ri.setRefresh(data);
	else if (address == RI_LATENCY_REG)
		rcp.ri.setLatency(data);
	else if (address == RI_RERROR_REG)
		rcp.ri.setRerror(data);
	else if (address == RI_WERROR_REG)
		rcp.ri.setWerror(data);

	else if (address == SI_DRAM_ADDR_REG)
		rcp.si.setDramAddr(data);
	else if (address == SI_PIF_ADDR_RD64B_REG)
	{
		rcp.si.setPifAddrRd64b(data);
		rcp.dma_si_read();
		rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_SI);
		rcp.si.setStatus(rcp.si.getStatus() | SI_STATUS_INTERRUPT);
		rcp.setCheckInterrupt(true);
	}
	else if (address == SI_PIF_ADDR_WR64B_REG)
	{
		rcp.si.setPifAddrWr64b(data);
		rcp.dma_si_write();
		rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_SI);
		rcp.si.setStatus(rcp.si.getStatus() | SI_STATUS_INTERRUPT);
		rcp.setCheckInterrupt(true);
	}
	else if (address == SI_STATUS_REG)
	{
		rcp.si.setSpecialStatus(data);
		rcp.mi.setIntr(rcp.mi.getIntr() & ~MI_INTR_SI);
		rcp.setCheckInterrupt(true);
	}
	else
		return false;
	return true;
}

//****************************************************************************
//** VIRTUAL TO PHYSICAL													**
//****************************************************************************
inline void* MMU::virtual_to_physical(word a)
{
	if (rcp.rdram.contains(a))			return rcp.rdram[a];
	if (rcp.rdram_regs.contains(a))		return rcp.rdram_regs[a];
	if (rcp.sp.contains(a))		return rcp.sp[a];
	if (rcp.dpc.contains(a))		return rcp.dpc[a];
	if (rcp.dps.contains(a))		return rcp.dps[a];
	if (rcp.mi.contains(a))		return rcp.mi[a];
	if (rcp.vi.contains(a))		return rcp.vi[a];
	if (rcp.ai.contains(a))		return rcp.ai[a];
	if (rcp.pi.contains(a))		return rcp.pi[a];
	if (rcp.ri.contains(a))		return rcp.ri[a];
	if (rcp.si.contains(a))		return rcp.si[a];
	if (rcp.rom.contains(a))			return rcp.rom[a];
	if (rcp.pif_rom.contains(a))		return rcp.pif_rom[a];
	if (rcp.pif_ram.contains(a))		return rcp.pif_ram[a];

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
