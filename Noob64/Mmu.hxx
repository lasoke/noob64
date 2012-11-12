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
		*data = rcp.getRdramRegs().getConfig();
	else if (address == RDRAM_DEVICE_ID_REG)
		*data = rcp.getRdramRegs().getDeviceId();
	else if (address == RDRAM_DELAY_REG)
		*data = rcp.getRdramRegs().getDelay();
	else if (address == RDRAM_MODE_REG)
		*data = rcp.getRdramRegs().getMode();
	else if (address == RDRAM_REF_INTERVAL_REG)
		*data = rcp.getRdramRegs().getRefInterval();
	else if (address == RDRAM_REF_ROW_REG)
		*data = rcp.getRdramRegs().getRefRow();
	else if (address == RDRAM_RAS_INTERVAL_REG)
		*data = rcp.getRdramRegs().getConfig();
	else if (address == RDRAM_MIN_INTERVAL_REG)
		*data = rcp.getRdramRegs().getConfig();
	else if (address == RDRAM_ADDR_SELECT_REG)
		*data = rcp.getRdramRegs().getConfig();
	else if (address == RDRAM_DEVICE_MANUF_REG)
		*data = rcp.getRdramRegs().getConfig();

	else if (address == SP_MEM_ADDR_REG)
		*data = rcp.getSP().getMemAddr();
	else if (address == SP_DRAM_ADDR_REG)
		*data = rcp.getSP().getDramAddr();
	else if (address == SP_RD_LEN_REG)
		*data = rcp.getSP().getRdLen();
	else if (address == SP_WR_LEN_REG)
		*data = rcp.getSP().getWrLen();
	else if (address == SP_STATUS_REG)
		*data = rcp.getSP().getStatus();
	else if (address == SP_DMA_FULL_REG)
		*data = rcp.getSP().getDmaFull();
	else if (address == SP_DMA_BUSY_REG)
		*data = rcp.getSP().getDmaBusy();
	else if (address == SP_SEMAPHORE_REG)
		*data = rcp.getSP().getSemaphore();
	else if (address == SP_PC_REG)
		*data = rcp.getSP().getPc();
	else if (address == SP_IBIST_REG)
		*data = rcp.getSP().getIbist();

	else if (address == DPC_START_REG)
		*data = rcp.getDPC().getStart();
	else if (address == DPC_END_REG)
		*data = rcp.getDPC().getEnd();
	else if (address == DPC_CURRENT_REG)
		*data = rcp.getDPC().getCurrent();
	else if (address == DPC_STATUS_REG)
		*data = rcp.getDPC().getStatus();
	else if (address == DPC_CLOCK_REG)
		*data = rcp.getDPC().getClock();
	else if (address == DPC_BUFBUSY_REG)
		*data = rcp.getDPC().getBufBusy();
	else if (address == DPC_PIPEBUSY_REG)
		*data = rcp.getDPC().getPipeBusy();
	else if (address == DPC_TMEM_REG)
		*data = rcp.getDPC().getTmem();

	else if (address == DPS_TBIST_REG)
		*data = rcp.getDPS().getTbist();
	else if (address == DPS_TEST_MODE_REG)
		*data = rcp.getDPS().getTestMode();
	else if (address == DPS_BUFTEST_ADDR_REG)
		*data = rcp.getDPS().getBufTestAddr();
	else if (address == DPS_BUFTEST_DATA_REG)
		*data = rcp.getDPS().getBufTestData();

	else if (address == MI_INIT_MODE_REG)
		*data = rcp.getMI().getInitMode();
	else if (address == MI_VERSION_REG)
		*data = rcp.getMI().getVersion();
	else if (address == MI_INTR_REG)
		*data = rcp.getMI().getIntr();
	else if (address == MI_INTR_MASK_REG)
		*data = rcp.getMI().getIntrMask();

	else if (address == VI_STATUS_REG)
		*data = rcp.getVI().getStatus();
	else if (address == VI_ORIGIN_REG)
		*data = rcp.getVI().getOrigin();
	else if (address == VI_WIDTH_REG)
		*data = rcp.getVI().getWidth();
	else if (address == VI_INTR_REG)
		*data = rcp.getVI().getIntr();
	else if (address == VI_CURRENT_REG)
	{
		rcp.updateCurrentHalfLine();
		*data = rcp.getHalfline();
	}
	else if (address == VI_BURST_REG)
		*data = rcp.getVI().getBurst();
	else if (address == VI_V_SYNC_REG)
		*data = rcp.getVI().getVsync();
	else if (address == VI_H_SYNC_REG)
		*data = rcp.getVI().getHsync();
	else if (address == VI_LEAP_REG)
		*data = rcp.getVI().getLeap();
	else if (address == VI_H_START_REG)
		*data = rcp.getVI().getHstart();
	else if (address == VI_V_START_REG)
		*data = rcp.getVI().getVstart();
	else if (address == VI_V_BURST_REG)
		*data = rcp.getVI().getVburst();
	else if (address == VI_X_SCALE_REG)
		*data = rcp.getVI().getXscale();
	else if (address == VI_Y_SCALE_REG)
		*data = rcp.getVI().getYscale();

	else if (address == AI_DRAM_ADDR_REG)
		*data = rcp.getAI().getDramAddr();
	else if (address == AI_LEN_REG)
	{
		*data = rcp.getAI().getLen();
		//res = AiReadLength();
	}
	else if (address == AI_CONTROL_REG)
		*data = rcp.getAI().getControl();
	else if (address == AI_STATUS_REG)
		*data = rcp.getAI().getStatus();
	else if (address == AI_DACRATE_REG)
		*data = rcp.getAI().getDacrate();
	else if (address == AI_BITRATE_REG)
		*data = rcp.getAI().getBitrate();

	else if (address == PI_DRAM_ADDR_REG)
		*data = rcp.getPI().getDramAddr();
	else if (address == PI_CART_ADDR_REG)
		*data = rcp.getPI().getCartAddr();
	else if (address == PI_RD_LEN_REG)
		*data = rcp.getPI().getRdLen();
	else if (address == PI_WR_LEN_REG)
		*data = rcp.getPI().getWrLen();
	else if (address == PI_STATUS_REG)
		*data = rcp.getPI().getStatus();
	else if (address == PI_BSD_DOM1_LAT_REG)
		*data = rcp.getPI().getBsdDom1Lat();
	else if (address == PI_BSD_DOM1_PWD_REG)
		*data = rcp.getPI().getBsdDom1Pwd();
	else if (address == PI_BSD_DOM1_PGS_REG)
		*data = rcp.getPI().getBsdDom1Pgs();
	else if (address == PI_BSD_DOM1_RLS_REG)
		*data = rcp.getPI().getBsdDom1Rls();
	else if (address == PI_BSD_DOM2_LAT_REG)
		*data = rcp.getPI().getBsdDom2Lat();
	else if (address == PI_BSD_DOM2_PWD_REG)
		*data = rcp.getPI().getBsdDom2Pwd();
	else if (address == PI_BSD_DOM2_PGS_REG)
		*data = rcp.getPI().getBsdDom2Pgs();
	else if (address == PI_BSD_DOM2_RLS_REG)
		*data = rcp.getPI().getBsdDom2Rls();

	else if (address == RI_MODE_REG)
		*data = rcp.getRI().getMode();
	else if (address == RI_CONFIG_REG)
		*data = rcp.getRI().getConfig();
	else if (address == RI_CURRENT_LOAD_REG)
		*data = rcp.getRI().getCurrentLoad();
	else if (address == RI_SELECT_REG)
		*data = rcp.getRI().getSelect();
	else if (address == RI_REFRESH_REG)
		*data = rcp.getRI().getRefresh();
	else if (address == RI_LATENCY_REG)
		*data = rcp.getRI().getLatency();
	else if (address == RI_RERROR_REG)
		*data = rcp.getRI().getRerror();
	else if (address == RI_WERROR_REG)
		*data = rcp.getRI().getWerror();

	else if (address == SI_DRAM_ADDR_REG)
		*data = rcp.getSI().getDramAddr();
	else if (address == SI_PIF_ADDR_RD64B_REG)
		*data = rcp.getSI().getPifAddrRd64b();
	else if (address == SI_PIF_ADDR_WR64B_REG)
		*data = rcp.getSI().getPifAddrWr64b();
	else if (address == SI_STATUS_REG)
		*data = rcp.getSI().getStatus();
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
		rcp.getRdramRegs().setConfig(data);
	else if (address == RDRAM_DEVICE_ID_REG)
		rcp.getRdramRegs().setDeviceId(data);
	else if (address == RDRAM_DELAY_REG)
		rcp.getRdramRegs().setDelay(data);
	else if (address == RDRAM_MODE_REG)
		rcp.getRdramRegs().setMode(data);
	else if (address == RDRAM_REF_INTERVAL_REG)
		rcp.getRdramRegs().setRefInterval(data);
	else if (address == RDRAM_REF_ROW_REG)
		rcp.getRdramRegs().setRefRow(data);
	else if (address == RDRAM_RAS_INTERVAL_REG)
		rcp.getRdramRegs().setConfig(data);
	else if (address == RDRAM_MIN_INTERVAL_REG)
		rcp.getRdramRegs().setConfig(data);
	else if (address == RDRAM_ADDR_SELECT_REG)
		rcp.getRdramRegs().setConfig(data);
	else if (address == RDRAM_DEVICE_MANUF_REG)
		rcp.getRdramRegs().setConfig(data);

	else if (address == SP_MEM_ADDR_REG)
		rcp.getSP().setMemAddr(data);
	else if (address == SP_DRAM_ADDR_REG)
		rcp.getSP().setDramAddr(data);
	else if (address == SP_RD_LEN_REG)
	{
		rcp.getSP().setRdLen(data);
		rcp.dma_sp_read();	
		rcp.getSP().setDmaBusy(0);
		rcp.getSP().setStatus(rcp.getSP().getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_WR_LEN_REG)
	{
		rcp.getSP().setWrLen(data);
		rcp.dma_sp_write();
		rcp.getSP().setDmaBusy(0);
		rcp.getSP().setStatus(rcp.getSP().getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_STATUS_REG)
	{
		rcp.getSP().setSpecialStatus(data);
		if (data & SP_SET_SIG0) 
		{
			rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_SP);
			rcp.setCheckInterrupt(true);
		}
		if (data & SP_CLR_INTR)
		{ 
			rcp.getMI().setIntr(rcp.getMI().getIntr() & ~MI_INTR_SP);
			rcp.run();
			rcp.setCheckInterrupt(true);
		}
		else
			rcp.run();
	}
	else if (address == SP_DMA_FULL_REG)
		rcp.getSP().setDmaFull(data);
	else if (address == SP_DMA_BUSY_REG)
		rcp.getSP().setDmaBusy(data);
	else if (address == SP_SEMAPHORE_REG)
		rcp.getSP().setSpecialSemaphore(data);
	else if (address == SP_PC_REG)
		rcp.getSP().setPc(data);
	else if (address == SP_IBIST_REG)
		rcp.getSP().setIbist(data);

	else if (address == DPC_START_REG)
		rcp.getDPC().setStart(data);
	else if (address == DPC_END_REG)
		rcp.getDPC().setEnd(data);
	else if (address == DPC_CURRENT_REG)
		rcp.getDPC().setCurrent(data);
	else if (address == DPC_STATUS_REG)
		rcp.getDPC().setStatus(data);
	else if (address == DPC_CLOCK_REG)
		rcp.getDPC().setClock(data);
	else if (address == DPC_BUFBUSY_REG)
		rcp.getDPC().setBufBusy(data);
	else if (address == DPC_PIPEBUSY_REG)
		rcp.getDPC().setPipeBusy(data);
	else if (address == DPC_TMEM_REG)
		rcp.getDPC().setTmem(data);

	else if (address == DPS_TBIST_REG)
		rcp.getDPS().setTbist(data);
	else if (address == DPS_TEST_MODE_REG)
		rcp.getDPS().setTestMode(data);
	else if (address == DPS_BUFTEST_ADDR_REG)
		rcp.getDPS().setBufTestAddr(data);
	else if (address == DPS_BUFTEST_DATA_REG)
		rcp.getDPS().setBufTestData(data);

	else if (address == MI_INIT_MODE_REG)
		rcp.getMI().setSpecialInitMode(data);
	else if (address == MI_VERSION_REG)
		rcp.getMI().setVersion(data);
	else if (address == MI_INTR_REG)
		rcp.getMI().setIntr(data);
	else if (address == MI_INTR_MASK_REG)
		rcp.getMI().setSpecialIntrMask(data);

	else if (address == VI_STATUS_REG)
	{
		rcp.getVI().setStatus(data);
		rcp.getGFX()->viStatusChanged();
	}
	else if (address == VI_ORIGIN_REG)
		rcp.getVI().setOrigin(data);
	else if (address == VI_WIDTH_REG)
	{
		rcp.getVI().setWidth(data);
		rcp.getGFX()->viWidthChanged();
	}
	else if (address == VI_INTR_REG)
		rcp.getVI().setVintr(data);
	else if (address == VI_CURRENT_REG)
	{
		rcp.getMI().setIntr(rcp.getMI().getIntr() & ~MI_INTR_VI);
		rcp.setCheckInterrupt(true);
	}
	else if (address == VI_BURST_REG)
		rcp.getVI().setBurst(data);
	else if (address == VI_V_SYNC_REG)
		rcp.getVI().setVsync(data);
	else if (address == VI_H_SYNC_REG)
		rcp.getVI().setHsync(data);
	else if (address == VI_LEAP_REG)
		rcp.getVI().setLeap(data);
	else if (address == VI_H_START_REG)
		rcp.getVI().setHstart(data);
	else if (address == VI_V_START_REG)
		rcp.getVI().setVstart(data);
	else if (address == VI_V_BURST_REG)
		rcp.getVI().setVburst(data);
	else if (address == VI_X_SCALE_REG)
		rcp.getVI().setXscale(data);
	else if (address == VI_Y_SCALE_REG)
		rcp.getVI().setYscale(data);

	else if (address == AI_DRAM_ADDR_REG)
		rcp.getAI().setDramAddr(data);
	else if (address == AI_LEN_REG)
		rcp.getAI().setLen(data);
	else if (address == AI_CONTROL_REG)
		rcp.getAI().setControl(data);
	else if (address == AI_STATUS_REG)
	{
		rcp.getMI().setIntr(rcp.getMI().getIntr() & ~MI_INTR_AI);
		rcp.setCheckInterrupt(true);
	}
	else if (address == AI_DACRATE_REG)
		rcp.getAI().setDacrate(data);
	else if (address == AI_BITRATE_REG)
		rcp.getAI().setBitrate(data);

	else if (address == PI_DRAM_ADDR_REG)
		rcp.getPI().setDramAddr(data);
	else if (address == PI_CART_ADDR_REG)
		rcp.getPI().setCartAddr(data);
	else if (address == PI_RD_LEN_REG)
	{
		rcp.getPI().setRdLen(data);
		rcp.dma_pi_read();
		rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_PI);
		rcp.getPI().setStatus(rcp.getPI().getStatus() & ~PI_STATUS_DMA_BUSY);
		rcp.setCheckInterrupt(true);
	}
	else if (address == PI_WR_LEN_REG)
	{
		rcp.getPI().setWrLen(data);
		rcp.dma_pi_write();
		rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_PI);
		rcp.getPI().setStatus(rcp.getPI().getStatus() & ~PI_STATUS_DMA_BUSY);
		rcp.setCheckInterrupt(true);
	}
	else if (address == PI_STATUS_REG)
	{
		rcp.getMI().setIntr(rcp.getMI().getIntr() & ~MI_INTR_PI);
		rcp.setCheckInterrupt(true);
	}
	else if (address == PI_BSD_DOM1_LAT_REG)
		rcp.getPI().setBsdDom1Lat(data);
	else if (address == PI_BSD_DOM1_PWD_REG)
		rcp.getPI().setBsdDom1Pwd(data);
	else if (address == PI_BSD_DOM1_PGS_REG)
		rcp.getPI().setBsdDom1Pgs(data);
	else if (address == PI_BSD_DOM1_RLS_REG)
		rcp.getPI().setBsdDom1Rls(data);
	else if (address == PI_BSD_DOM2_LAT_REG)
		rcp.getPI().setBsdDom2Lat(data);
	else if (address == PI_BSD_DOM2_PWD_REG)
		rcp.getPI().setBsdDom2Pwd(data);
	else if (address == PI_BSD_DOM2_PGS_REG)
		rcp.getPI().setBsdDom2Pgs(data);
	else if (address == PI_BSD_DOM2_RLS_REG)
		rcp.getPI().setBsdDom2Rls(data);

	else if (address == RI_MODE_REG)
		rcp.getRI().setMode(data);
	else if (address == RI_CONFIG_REG)
		rcp.getRI().setConfig(data);
	else if (address == RI_CURRENT_LOAD_REG)
		rcp.getRI().setCurrentLoad(data);
	else if (address == RI_SELECT_REG)
		rcp.getRI().setSelect(data);
	else if (address == RI_REFRESH_REG)
		rcp.getRI().setRefresh(data);
	else if (address == RI_LATENCY_REG)
		rcp.getRI().setLatency(data);
	else if (address == RI_RERROR_REG)
		rcp.getRI().setRerror(data);
	else if (address == RI_WERROR_REG)
		rcp.getRI().setWerror(data);

	else if (address == SI_DRAM_ADDR_REG)
		rcp.getSI().setDramAddr(data);
	else if (address == SI_PIF_ADDR_RD64B_REG)
	{
		rcp.getSI().setPifAddrRd64b(data);
		rcp.dma_si_read();
		rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_SI);
		rcp.getSI().setStatus(rcp.getSI().getStatus() | SI_STATUS_INTERRUPT);
		rcp.setCheckInterrupt(true);
	}
	else if (address == SI_PIF_ADDR_WR64B_REG)
	{
		rcp.getSI().setPifAddrWr64b(data);
		rcp.dma_si_write();
		rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_SI);
		rcp.getSI().setStatus(rcp.getSI().getStatus() | SI_STATUS_INTERRUPT);
		rcp.setCheckInterrupt(true);
	}
	else if (address == SI_STATUS_REG)
	{
		rcp.getSI().setSpecialStatus(data);
		rcp.getMI().setIntr(rcp.getMI().getIntr() & ~MI_INTR_SI);
		rcp.setCheckInterrupt(true);
	}
	else
		return false;
	return true;
}

//****************************************************************************
//** VIRTUAL TO PHYSICAL													**
//****************************************************************************
inline char* MMU::virtual_to_physical(word a)
{
	if (rcp.getRDRAM().contains(a))			return rcp.getRDRAM()[a];
	if (rcp.getRdramRegs().contains(a))		return rcp.getRdramRegs()[a];
	if (rcp.getSP().contains(a))			return rcp.getSP()[a];
	if (rcp.getDPC().contains(a))			return rcp.getDPC()[a];
	if (rcp.getDPS().contains(a))			return rcp.getDPS()[a];
	if (rcp.getMI().contains(a))			return rcp.getMI()[a];
	if (rcp.getVI().contains(a))			return rcp.getVI()[a];
	if (rcp.getAI().contains(a))			return rcp.getAI()[a];
	if (rcp.getPI().contains(a))			return rcp.getPI()[a];
	if (rcp.getRI().contains(a))			return rcp.getRI()[a];
	if (rcp.getSI().contains(a))			return rcp.getSI()[a];
	if (rcp.getROM().contains(a))			return rcp.getROM()[a];
	if (rcp.getPifRom().contains(a))		return rcp.getPifRom()[a];
	if (rcp.getPifRam().contains(a))		return rcp.getPifRam()[a];

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

//****************************************************************************
//** IS ADDRESS DEFINED														**
//****************************************************************************
inline bool MMU::is_address_defined(word address) const
{
	if (KSEG0 <= address && address <= KSEG2-1)
		return true;
	/* TODO:
	dword i;
	for (i = 0; i < 64; i++)
	{
		if (FastTlb[i].ValidEntry == false)
			continue;
		if (address >= FastTlb[i].VSTART && address <= FastTlb[i].VEND)
			return true;
	}
	*/
	return false; 
}