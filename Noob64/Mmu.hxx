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

inline char* MMU::get(const word address)
{
	return virtual_to_physical(address);
}

//****************************************************************************
//** READ																	**
//****************************************************************************
template <typename Type>
Type MMU::read(word address) { return read<Type>(address, true); }

template <typename Type>
Type MMU::read(word address, bool trigger_event)
{
	Type res;
	if (trigger_event && typeid(Type) == typeid(word) && read_from_register((word *) &res, address))
		return res;

	memcpy(&res, virtual_to_physical(address), sizeof(Type));
	res = binary_to_type<Type>(res);
	return res;
}

// Get the value contains in the registes
inline bool MMU::read_from_register(word *data, word address)
{
	address &= 0x0FFFFFFF;
	if (address == RDRAM_CONFIG_REG)				*data = RCP::getRdramRegs()->getConfig();
	else if (address == RDRAM_DEVICE_ID_REG)		*data = RCP::getRdramRegs()->getDeviceId();
	else if (address == RDRAM_DELAY_REG)			*data = RCP::getRdramRegs()->getDelay();
	else if (address == RDRAM_MODE_REG)				*data = RCP::getRdramRegs()->getMode();
	else if (address == RDRAM_REF_INTERVAL_REG)		*data = RCP::getRdramRegs()->getRefInterval();
	else if (address == RDRAM_REF_ROW_REG)			*data = RCP::getRdramRegs()->getRefRow();
	else if (address == RDRAM_RAS_INTERVAL_REG)		*data = RCP::getRdramRegs()->getConfig();
	else if (address == RDRAM_MIN_INTERVAL_REG)		*data = RCP::getRdramRegs()->getConfig();
	else if (address == RDRAM_ADDR_SELECT_REG)		*data = RCP::getRdramRegs()->getConfig();
	else if (address == RDRAM_DEVICE_MANUF_REG)		*data = RCP::getRdramRegs()->getConfig();

	else if (address == SP_MEM_ADDR_REG)			*data = RCP::getSP()->getMemAddr();
	else if (address == SP_DRAM_ADDR_REG)			*data = RCP::getSP()->getDramAddr();
	else if (address == SP_RD_LEN_REG)				*data = RCP::getSP()->getRdLen();
	else if (address == SP_WR_LEN_REG)				*data = RCP::getSP()->getWrLen();
	else if (address == SP_STATUS_REG)				*data = RCP::getSP()->getStatus();
	else if (address == SP_DMA_FULL_REG)			*data = RCP::getSP()->getDmaFull();
	else if (address == SP_DMA_BUSY_REG)			*data = RCP::getSP()->getDmaBusy();
	else if (address == SP_SEMAPHORE_REG)			*data = RCP::getSP()->getSpecialSemaphore();
	else if (address == SP_PC_REG)					*data = RCP::getSP()->getPc();
	else if (address == SP_IBIST_REG)				*data = RCP::getSP()->getIbist();

	else if (address == DPC_START_REG)				*data = RCP::getDPC()->getStart();
	else if (address == DPC_END_REG)				*data = RCP::getDPC()->getEnd();
	else if (address == DPC_CURRENT_REG)			*data = RCP::getDPC()->getCurrent();
	else if (address == DPC_STATUS_REG)				*data = RCP::getDPC()->getStatus();
	else if (address == DPC_CLOCK_REG)				*data = RCP::getDPC()->getClock();
	else if (address == DPC_BUFBUSY_REG)			*data = RCP::getDPC()->getBufBusy();
	else if (address == DPC_PIPEBUSY_REG)			*data = RCP::getDPC()->getPipeBusy();
	else if (address == DPC_TMEM_REG)				*data = RCP::getDPC()->getTmem();

	else if (address == DPS_TBIST_REG)				*data = RCP::getDPS()->getTbist();
	else if (address == DPS_TEST_MODE_REG)			*data = RCP::getDPS()->getTestMode();
	else if (address == DPS_BUFTEST_ADDR_REG)		*data = RCP::getDPS()->getBufTestAddr();
	else if (address == DPS_BUFTEST_DATA_REG)		*data = RCP::getDPS()->getBufTestData();

	else if (address == MI_INIT_MODE_REG)			*data = RCP::getMI()->getInitMode();
	else if (address == MI_VERSION_REG)				*data = RCP::getMI()->getVersion();
	else if (address == MI_INTR_REG)				*data = RCP::getMI()->getIntr();
	else if (address == MI_INTR_MASK_REG)			*data = RCP::getMI()->getIntrMask();

	else if (address == VI_STATUS_REG)				*data = RCP::getVI()->getStatus();
	else if (address == VI_ORIGIN_REG)				*data = RCP::getVI()->getOrigin();
	else if (address == VI_WIDTH_REG)				*data = RCP::getVI()->getWidth();
	else if (address == VI_INTR_REG)				*data = RCP::getVI()->getIntr();
	else if (address == VI_CURRENT_REG)
	{
		RCP::update_current_halfLine();
		*data = RCP::getHalfline();
	}
	else if (address == VI_BURST_REG)				*data = RCP::getVI()->getBurst();
	else if (address == VI_V_SYNC_REG)				*data = RCP::getVI()->getVsync();
	else if (address == VI_H_SYNC_REG)				*data = RCP::getVI()->getHsync();
	else if (address == VI_LEAP_REG)				*data = RCP::getVI()->getLeap();
	else if (address == VI_H_START_REG)				*data = RCP::getVI()->getHstart();
	else if (address == VI_V_START_REG)				*data = RCP::getVI()->getVstart();
	else if (address == VI_V_BURST_REG)				*data = RCP::getVI()->getVburst();
	else if (address == VI_X_SCALE_REG)				*data = RCP::getVI()->getXscale();
	else if (address == VI_Y_SCALE_REG)				*data = RCP::getVI()->getYscale();

	else if (address == AI_DRAM_ADDR_REG)			*data = RCP::getAI()->getDramAddr();
	else if (address == AI_LEN_REG)
	{
		*data = RCP::getAI()->getLen();
		//res = AiReadLength();
	}
	else if (address == AI_CONTROL_REG)				*data = RCP::getAI()->getControl();
	else if (address == AI_STATUS_REG)				*data = RCP::getAI()->getStatus();
	else if (address == AI_DACRATE_REG)				*data = RCP::getAI()->getDacrate();
	else if (address == AI_BITRATE_REG)				*data = RCP::getAI()->getBitrate();

	else if (address == PI_DRAM_ADDR_REG)			*data = RCP::getPI()->getDramAddr();
	else if (address == PI_CART_ADDR_REG)			*data = RCP::getPI()->getCartAddr();
	else if (address == PI_RD_LEN_REG)				*data = RCP::getPI()->getRdLen();
	else if (address == PI_WR_LEN_REG)				*data = RCP::getPI()->getWrLen();
	else if (address == PI_STATUS_REG)				*data = RCP::getPI()->getStatus();
	else if (address == PI_BSD_DOM1_LAT_REG)		*data = RCP::getPI()->getBsdDom1Lat();
	else if (address == PI_BSD_DOM1_PWD_REG)		*data = RCP::getPI()->getBsdDom1Pwd();
	else if (address == PI_BSD_DOM1_PGS_REG)		*data = RCP::getPI()->getBsdDom1Pgs();
	else if (address == PI_BSD_DOM1_RLS_REG)		*data = RCP::getPI()->getBsdDom1Rls();
	else if (address == PI_BSD_DOM2_LAT_REG)		*data = RCP::getPI()->getBsdDom2Lat();
	else if (address == PI_BSD_DOM2_PWD_REG)		*data = RCP::getPI()->getBsdDom2Pwd();
	else if (address == PI_BSD_DOM2_PGS_REG)		*data = RCP::getPI()->getBsdDom2Pgs();
	else if (address == PI_BSD_DOM2_RLS_REG)		*data = RCP::getPI()->getBsdDom2Rls();

	else if (address == RI_MODE_REG)				*data = RCP::getRI()->getMode();
	else if (address == RI_CONFIG_REG)				*data = RCP::getRI()->getConfig();
	else if (address == RI_CURRENT_LOAD_REG)		*data = RCP::getRI()->getCurrentLoad();
	else if (address == RI_SELECT_REG)				*data = RCP::getRI()->getSelect();
	else if (address == RI_REFRESH_REG)				*data = RCP::getRI()->getRefresh();
	else if (address == RI_LATENCY_REG)				*data = RCP::getRI()->getLatency();
	else if (address == RI_RERROR_REG)				*data = RCP::getRI()->getRerror();
	else if (address == RI_WERROR_REG)				*data = RCP::getRI()->getWerror();

	else if (address == SI_DRAM_ADDR_REG)			*data = RCP::getSI()->getDramAddr();
	else if (address == SI_PIF_ADDR_RD64B_REG)		*data = RCP::getSI()->getPifAddrRd64b();
	else if (address == SI_PIF_ADDR_WR64B_REG)		*data = RCP::getSI()->getPifAddrWr64b();
	else if (address == SI_STATUS_REG)				*data = RCP::getSI()->getStatus();
	else return false;

	return true;
}

//****************************************************************************
//** WRITE																	**
//****************************************************************************
template <typename Type>
inline void MMU::write(Type data, word address) { return write<Type>(data, address, true); }

template <typename Type>
inline void MMU::write(Type data, word address, bool trigger_event)
{
	if (trigger_event && typeid(Type) == typeid(word) && write_in_register((word) data, address))
		return;

	char *dst = virtual_to_physical(address);
	data = type_to_binary<Type>(data);
	memcpy(dst, &data, sizeof(Type));
}

// Set the value of the registers
inline bool MMU::write_in_register(word data, word address)
{
	address &= 0x0FFFFFFF;

	if (address == RDRAM_CONFIG_REG)				RCP::getRdramRegs()->setConfig(data);
	else if (address == RDRAM_DEVICE_ID_REG)		RCP::getRdramRegs()->setDeviceId(data);
	else if (address == RDRAM_DELAY_REG)			RCP::getRdramRegs()->setDelay(data);
	else if (address == RDRAM_MODE_REG)				RCP::getRdramRegs()->setMode(data);
	else if (address == RDRAM_REF_INTERVAL_REG)		RCP::getRdramRegs()->setRefInterval(data);
	else if (address == RDRAM_REF_ROW_REG)			RCP::getRdramRegs()->setRefRow(data);
	else if (address == RDRAM_RAS_INTERVAL_REG)		RCP::getRdramRegs()->setConfig(data);
	else if (address == RDRAM_MIN_INTERVAL_REG)		RCP::getRdramRegs()->setConfig(data);
	else if (address == RDRAM_ADDR_SELECT_REG)		RCP::getRdramRegs()->setConfig(data);
	else if (address == RDRAM_DEVICE_MANUF_REG)		RCP::getRdramRegs()->setConfig(data);

	else if (address == SP_MEM_ADDR_REG)			RCP::getSP()->setMemAddr(data);
	else if (address == SP_DRAM_ADDR_REG)			RCP::getSP()->setDramAddr(data);
	else if (address == SP_RD_LEN_REG)
	{
		RCP::getSP()->setRdLen(data);
		RCP::dma_sp_read();	
		RCP::getSP()->setDmaBusy(0);
		RCP::getSP()->setStatus(RCP::getSP()->getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_WR_LEN_REG)
	{
		RCP::getSP()->setWrLen(data);
		RCP::dma_sp_write();
		RCP::getSP()->setDmaBusy(0);
		RCP::getSP()->setStatus(RCP::getSP()->getStatus() & ~SP_STATUS_DMA_BUSY);
	}
	else if (address == SP_STATUS_REG)
	{
		RCP::getSP()->setSpecialStatus(data);
		if (data & SP_SET_SIG0)
		{
			RCP::getMI()->setIntr(RCP::getMI()->getIntr() | MI_INTR_SP);
			R4300i::check_interrupt();
		}
		if (data & SP_CLR_INTR)
		{
			RCP::getMI()->setIntr(RCP::getMI()->getIntr() & ~MI_INTR_SP);
			R4300i::check_interrupt();
		}
		RCP::run_rsp();
	}
	else if (address == SP_DMA_FULL_REG)			RCP::getSP()->setDmaFull(data);
	else if (address == SP_DMA_BUSY_REG)			RCP::getSP()->setDmaBusy(data);
	else if (address == SP_SEMAPHORE_REG)			RCP::getSP()->setSpecialSemaphore(data);
	else if (address == SP_PC_REG)					RCP::getSP()->setPc(data);
	else if (address == SP_IBIST_REG)				RCP::getSP()->setIbist(data);

	else if (address == DPC_START_REG)				RCP::getDPC()->setStart(data);
	else if (address == DPC_END_REG)				RCP::getDPC()->setEnd(data);
	else if (address == DPC_CURRENT_REG)			RCP::getDPC()->setCurrent(data);
	else if (address == DPC_STATUS_REG)				RCP::getDPC()->setStatus(data);
	else if (address == DPC_CLOCK_REG)				RCP::getDPC()->setClock(data);
	else if (address == DPC_BUFBUSY_REG)			RCP::getDPC()->setBufBusy(data);
	else if (address == DPC_PIPEBUSY_REG)			RCP::getDPC()->setPipeBusy(data);
	else if (address == DPC_TMEM_REG)				RCP::getDPC()->setTmem(data);

	else if (address == DPS_TBIST_REG)				RCP::getDPS()->setTbist(data);
	else if (address == DPS_TEST_MODE_REG)			RCP::getDPS()->setTestMode(data);
	else if (address == DPS_BUFTEST_ADDR_REG)		RCP::getDPS()->setBufTestAddr(data);
	else if (address == DPS_BUFTEST_DATA_REG)		RCP::getDPS()->setBufTestData(data);

	else if (address == MI_INIT_MODE_REG)			RCP::getMI()->setSpecialInitMode(data);
	else if (address == MI_VERSION_REG)				RCP::getMI()->setVersion(data);
	else if (address == MI_INTR_REG)				RCP::getMI()->setIntr(data);
	else if (address == MI_INTR_MASK_REG)			RCP::getMI()->setSpecialIntrMask(data);

	else if (address == VI_STATUS_REG)
	{
		RCP::getVI()->setStatus(data);
		GFX::viStatusChanged();
	}
	else if (address == VI_ORIGIN_REG)				RCP::getVI()->setOrigin(data);
	else if (address == VI_WIDTH_REG)
	{
		RCP::getVI()->setWidth(data);
		GFX::viWidthChanged();
	}
	else if (address == VI_INTR_REG)				RCP::getVI()->setVintr(data);
	else if (address == VI_CURRENT_REG)
	{
		RCP::getMI()->setIntr(RCP::getMI()->getIntr() & ~MI_INTR_VI);
		R4300i::check_interrupt();
	}
	else if (address == VI_BURST_REG)				RCP::getVI()->setBurst(data);
	else if (address == VI_V_SYNC_REG)				RCP::getVI()->setVsync(data);
	else if (address == VI_H_SYNC_REG)				RCP::getVI()->setHsync(data);
	else if (address == VI_LEAP_REG)				RCP::getVI()->setLeap(data);
	else if (address == VI_H_START_REG)				RCP::getVI()->setHstart(data);
	else if (address == VI_V_START_REG)				RCP::getVI()->setVstart(data);
	else if (address == VI_V_BURST_REG)				RCP::getVI()->setVburst(data);
	else if (address == VI_X_SCALE_REG)				RCP::getVI()->setXscale(data);
	else if (address == VI_Y_SCALE_REG)				RCP::getVI()->setYscale(data);

	else if (address == AI_DRAM_ADDR_REG)			RCP::getAI()->setDramAddr(data);
	else if (address == AI_LEN_REG)					RCP::getAI()->setLen(data);
	else if (address == AI_CONTROL_REG)				RCP::getAI()->setControl(data);
	else if (address == AI_STATUS_REG)
	{
		RCP::getMI()->setIntr(RCP::getMI()->getIntr() & ~MI_INTR_AI);
		R4300i::check_interrupt();
	}
	else if (address == AI_DACRATE_REG)				RCP::getAI()->setDacrate(data);
	else if (address == AI_BITRATE_REG)				RCP::getAI()->setBitrate(data);

	else if (address == PI_DRAM_ADDR_REG)			RCP::getPI()->setDramAddr(data);
	else if (address == PI_CART_ADDR_REG)			RCP::getPI()->setCartAddr(data);
	else if (address == PI_RD_LEN_REG)	{
		RCP::getPI()->setRdLen(data);
		RCP::dma_pi_read();
	}
	else if (address == PI_WR_LEN_REG)
	{
		RCP::getPI()->setWrLen(data);
		RCP::dma_pi_write();
	}
	else if (address == PI_STATUS_REG)
	{
		RCP::getMI()->setIntr(RCP::getMI()->getIntr() & ~MI_INTR_PI);
		R4300i::check_interrupt();
	}
	else if (address == PI_BSD_DOM1_LAT_REG)		RCP::getPI()->setBsdDom1Lat(data);
	else if (address == PI_BSD_DOM1_PWD_REG)		RCP::getPI()->setBsdDom1Pwd(data);
	else if (address == PI_BSD_DOM1_PGS_REG)		RCP::getPI()->setBsdDom1Pgs(data);
	else if (address == PI_BSD_DOM1_RLS_REG)		RCP::getPI()->setBsdDom1Rls(data);
	else if (address == PI_BSD_DOM2_LAT_REG)		RCP::getPI()->setBsdDom2Lat(data);
	else if (address == PI_BSD_DOM2_PWD_REG)		RCP::getPI()->setBsdDom2Pwd(data);
	else if (address == PI_BSD_DOM2_PGS_REG)		RCP::getPI()->setBsdDom2Pgs(data);
	else if (address == PI_BSD_DOM2_RLS_REG)		RCP::getPI()->setBsdDom2Rls(data);

	else if (address == RI_MODE_REG)				RCP::getRI()->setMode(data);
	else if (address == RI_CONFIG_REG)				RCP::getRI()->setConfig(data);
	else if (address == RI_CURRENT_LOAD_REG)		RCP::getRI()->setCurrentLoad(data);
	else if (address == RI_SELECT_REG)				RCP::getRI()->setSelect(data);
	else if (address == RI_REFRESH_REG)				RCP::getRI()->setRefresh(data);
	else if (address == RI_LATENCY_REG)				RCP::getRI()->setLatency(data);
	else if (address == RI_RERROR_REG)				RCP::getRI()->setRerror(data);
	else if (address == RI_WERROR_REG)				RCP::getRI()->setWerror(data);

	else if (address == SI_DRAM_ADDR_REG)			RCP::getSI()->setDramAddr(data);
	else if (address == SI_PIF_ADDR_RD64B_REG)
	{
		RCP::getSI()->setPifAddrWr64b(data);
		RCP::dma_si_write();
	}
	else if (address == SI_PIF_ADDR_WR64B_REG)
	{
		RCP::getSI()->setPifAddrRd64b(data);
		RCP::dma_si_read();
	}
	else if (address == SI_STATUS_REG)
	{
		RCP::getSI()->setSpecialStatus(data);
		RCP::getMI()->setIntr(RCP::getMI()->getIntr() & ~MI_INTR_SI);
		R4300i::check_interrupt();
	}
	else return false;

	return true;
}

//****************************************************************************
//** VIRTUAL TO PHYSICAL													**
//****************************************************************************
inline char* MMU::virtual_to_physical(word a)
{
	if (RCP::getRDRAM()->contains(a))		return (*RCP::getRDRAM())[a];
	if (RCP::getRdramRegs()->contains(a))	return (*RCP::getRdramRegs())[a];
	if (RCP::getSP()->contains(a))			return (*RCP::getSP())[a];
	if (RCP::getDPC()->contains(a))			return (*RCP::getDPC())[a];
	if (RCP::getDPS()->contains(a))			return (*RCP::getDPS())[a];
	if (RCP::getMI()->contains(a))			return (*RCP::getMI())[a];
	if (RCP::getVI()->contains(a))			return (*RCP::getVI())[a];
	if (RCP::getAI()->contains(a))			return (*RCP::getAI())[a];
	if (RCP::getPI()->contains(a))			return (*RCP::getPI())[a];
	if (RCP::getRI()->contains(a))			return (*RCP::getRI())[a];
	if (RCP::getSI()->contains(a))			return (*RCP::getSI())[a];
	if (RCP::getROM()->contains(a))			return (*RCP::getROM())[a];
	if (RCP::getPifRom()->contains(a))		return (*RCP::getPifRom())[a];
	if (RCP::getPifRam()->contains(a))		return (*RCP::getPifRam())[a];

	if (KSEG0 <= a && a <= KSEG1-1)			return (virtual_to_physical(a-KSEG0)); // Mirror of 0x00000000 to 0x1FFFFFFF
	if (KSEG1 <= a && a <= KSEG2-1)			return (virtual_to_physical(a-KSEG1)); // Mirror of 0x00000000 to 0x1FFFFFFF
	if (KSEG2 <= a && a <= KSEG3-1)			throw TLB_NOT_HANDLED; // TLB mapped
	if (KSEG3 <= a && a <= 0xFFFFFFFF)		throw TLB_NOT_HANDLED; // TLB mapped

	cerr << endl << "ERROR: Virtual address 0x" << hex << a << " not handled" << endl;
	throw VIRTUAL_ADDRESS_ERROR;
}

//****************************************************************************
//** IS ADDRESS DEFINED														**
//****************************************************************************
inline bool MMU::is_address_defined(word address)
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