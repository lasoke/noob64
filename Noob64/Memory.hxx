#pragma once

#include "Rsp.h"
#include "Gfx.h"
#include "Memory.h"

//****************************************************************************
//** MEMORY::READ															**
//****************************************************************************
template <typename Type>
Type MEMORY::read(dword address)
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
inline bool MEMORY::read_from_register(word *data, dword address)
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
//** MEMORY::WRITE															**
//****************************************************************************
template <typename Type>
inline void MEMORY::write(Type data, dword address)
{
	if (typeid(Type) == typeid(word) && write_in_register((word) data, address))
		return;

	void *dst = virtual_to_physical(address);
	data = type_to_binary<Type>(data);
	memcpy(dst, &data, sizeof(Type));
}

// Set the value of the registers
inline bool MEMORY::write_in_register(word data, dword address)
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
		sp_regs.setStatus(data);
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
		sp_regs.setSemaphore(data);
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
		mi_regs.setInitMode(data);
	else if (address == MI_VERSION_REG)
		mi_regs.setVersion(data);
	else if (address == MI_INTR_REG)
		mi_regs.setIntr(data);
	else if (address == MI_INTR_MASK_REG)
		mi_regs.setIntrMask(data);

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
		ai_regs.setStatus(data);
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
		si_regs.setStatus(data);
		mi_regs.setIntr(mi_regs.getIntr() & ~MI_INTR_SI);
		check_intr = true;
	}
	else
		return false;
	return true;
}

//****************************************************************************
//** MEMORY::VIRTUAL TO PHYSICAL											**
//****************************************************************************
inline void* MEMORY::virtual_to_physical(dword address)
{
	address = (word) address;
	if (RDRAM::begining <= address && address <= RDRAM::end)
		return (void*) (rdram[address- RDRAM::begining]);
	else if (RDRAM_REGS::begining <= address && address <= RDRAM_REGS::end)
		return (void*) (rdram_regs[address - RDRAM_REGS::begining]);
	else if (SP_REGS::begining <= address && address <= SP_REGS::end)
		return (void*) (sp_regs[address - SP_REGS::begining]);
	else if (DPC_REGS::begining <= address && address <= DPC_REGS::end)
		return (void*) (dpc_regs[address - DPC_REGS::begining]);
	else if (DPS_REGS::begining <= address && address <= DPS_REGS::end)
		return (void*) (dps_regs[address - DPS_REGS::begining]);
	else if (MI_REGS::begining <= address && address <= MI_REGS::end)
		return (void*) (mi_regs[address - MI_REGS::begining]);
	else if (VI_REGS::begining <= address && address <= VI_REGS::end)
		return (void*) (vi_regs[address - VI_REGS::begining]);
	else if (AI_REGS::begining <= address && address <= AI_REGS::end)
		return (void*) (ai_regs[address - AI_REGS::begining]);
	else if (PI_REGS::begining <= address && address <= PI_REGS::end)
		return (void*) (pi_regs[address - PI_REGS::begining]);
	else if (RI_REGS::begining <= address && address <= RI_REGS::end)
		return (void*) (ri_regs[address - RI_REGS::begining]);
	else if (SI_REGS::begining <= address && address <= SI_REGS::end)
		return (void*) (si_regs[address - SI_REGS::begining]);
	else if (ROM::begining <= address && address <= ROM::end)
		return (void*) (rom[address - ROM::begining]);
	else if (PIF_ROM::begining <= address && address <= PIF_ROM::end)
		return (void*) (pif_rom[address - PIF_ROM::begining]);
	else if (PIF_RAM::begining <= address && address <= PIF_RAM::end)
		return (void*) (pif_ram[address - PIF_RAM::begining]);
	else if (0x80000000 <= address && address <= 0x9FFFFFFF) // Mirror 8 of 0x0000 0000 to 0x1FFF FFFF
		return (virtual_to_physical(address - 0x80000000));
	else if (0xA0000000 <= address && address <= 0xBFFFFFFF) // Mirror A of 0x0000 0000 to 0x1FFF FFFF
		return (virtual_to_physical(address - 0xA0000000));
	else
		cerr << endl << "ERROR: Address 0x" << hex << address << " not handled" << endl;
	return 0;
}

bool is_address_defined(dword address);

//****************************************************************************
//** SET METHODS					                                        **
//****************************************************************************

inline void RDRAM_REGS::setConfig(word w)		{ data.config = w; }
inline void RDRAM_REGS::setDeviceId(word w)		{ data.device_id = w; }
inline void RDRAM_REGS::setDelay(word w)		{ data.delay = w; }
inline void RDRAM_REGS::setMode(word w)			{ data.mode = w; }
inline void RDRAM_REGS::setRefInterval(word w)	{ data.ref_interval = w; }
inline void RDRAM_REGS::setRefRow(word w)		{ data.ref_row = w; }
inline void RDRAM_REGS::setRasInterval(word w)	{ data.ras_interval = w; }
inline void RDRAM_REGS::setMinInterval(word w)	{ data.min_interval = w; }
inline void RDRAM_REGS::setAddrSelect(word w)	{ data.addr_select = w; }
inline void RDRAM_REGS::setDeviceManuf(word w)	{ data.device_manuf = w; }

inline void SP_REGS::setMemAddr(word w)			{ data.mem_addr = w; }
inline void SP_REGS::setDramAddr(word w)		{ data.dram_addr = w; }
inline void SP_REGS::setRdLen(word w)			{ data.rd_len = w; }
inline void SP_REGS::setWrLen(word w)			{ data.wr_len = w; }
inline void SP_REGS::setStatus(word w)
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
inline void SP_REGS::setDmaFull(word w)			{ data.dma_full = w; }
inline void SP_REGS::setDmaBusy(word w)			{ data.dma_busy = w; }
inline void SP_REGS::setSemaphore(word w)		{ data.semaphore = 0; }
inline void SP_REGS::setPc(word w)				{ data.pc = w & 0xFFC; }
inline void SP_REGS::setIbist(word w)			{ data.ibist = w; }

inline void DPC_REGS::setStart(word w)			{ data.start = w; }
inline void DPC_REGS::setEnd(word w)			{ data.end = w; }
inline void DPC_REGS::setCurrent(word w)		{ data.current = w; }
inline void DPC_REGS::setStatus(word w)			{ data.status = w; }
inline void DPC_REGS::setClock(word w)			{ data.clock = w; }
inline void DPC_REGS::setBufBusy(word w)		{ data.bufbusy = w; }
inline void DPC_REGS::setPipeBusy(word w)		{ data.pipebusy = w; }
inline void DPC_REGS::setTmem(word w)			{ data.tmem = w; }

inline void DPS_REGS::setTbist(word w)			{ data.tbist = w; }
inline void DPS_REGS::setTestMode(word w)		{ data.test_mode = w; }
inline void DPS_REGS::setBufTestAddr(word w)	{ data.buftest_addr = w; }
inline void DPS_REGS::setBufTestData(word w)	{ data.buftest_data = w; }

inline void MI_REGS::setInitMode(word w)
{
	if (w & MI_CLR_INIT)		data.init_mode &= ~MI_MODE_INIT;
	if (w & MI_CLR_EBUS)		data.init_mode &= ~MI_MODE_EBUS;
	if (w & MI_CLR_RDRAM)		data.init_mode &= ~MI_MODE_RDRAM;

	if (w & MI_SET_INIT)		data.init_mode |= MI_MODE_INIT;
	if (w & MI_SET_EBUS)		data.init_mode |= MI_MODE_EBUS;
	if (w & MI_SET_RDRAM)		data.init_mode |= MI_MODE_RDRAM;

	if (w & MI_CLR_DP_INTR)		data.intr &= ~MI_INTR_DP;
}
inline void MI_REGS::setVersion(word w)			{ data.version = w; }
inline void MI_REGS::setIntr(word w)			{ data.intr = w; }
inline void MI_REGS::setIntrMask(word w)
{
	if (w & MI_INTR_MASK_CLR_SP)		data.intr_mask &= ~MI_INTR_MASK_SP;
	if (w & MI_INTR_MASK_CLR_SI)		data.intr_mask &= ~MI_INTR_MASK_SI;
	if (w & MI_INTR_MASK_CLR_AI)		data.intr_mask &= ~MI_INTR_MASK_AI;
	if (w & MI_INTR_MASK_CLR_VI)		data.intr_mask &= ~MI_INTR_MASK_VI;
	if (w & MI_INTR_MASK_CLR_PI)		data.intr_mask &= ~MI_INTR_MASK_PI;
	if (w & MI_INTR_MASK_CLR_DP)		data.intr_mask &= ~MI_INTR_MASK_DP;

	if (w & MI_INTR_MASK_SET_SP)		data.intr_mask |= MI_INTR_MASK_SP;
	if (w & MI_INTR_MASK_SET_SI)		data.intr_mask |= MI_INTR_MASK_SI;
	if (w & MI_INTR_MASK_SET_AI)		data.intr_mask |= MI_INTR_MASK_AI;
	if (w & MI_INTR_MASK_SET_VI)		data.intr_mask |= MI_INTR_MASK_VI;
	if (w & MI_INTR_MASK_SET_PI)		data.intr_mask |= MI_INTR_MASK_PI;
	if (w & MI_INTR_MASK_SET_DP)		data.intr_mask |= MI_INTR_MASK_DP;
}

inline void VI_REGS::setStatus(word w)
{
	data.status = w;
	//ViStatusChanged
}
inline void VI_REGS::setOrigin(word w)			{ data.origin = w; }
inline void VI_REGS::setWidth(word w)
{
	data.width = w;
	//ViWidthChanged
}
inline void VI_REGS::setVintr(word w)			{ /*TODO*/ }
inline void VI_REGS::setCurrent(word w)			{ data.current = w; }
inline void VI_REGS::setBurst(word w)			{ data.burst = w; }
inline void VI_REGS::setVsync(word w)			{ data.v_sync = w; }
inline void VI_REGS::setHsync(word w)			{ data.h_sync = w; }
inline void VI_REGS::setLeap(word w)			{ data.leap = w; }
inline void VI_REGS::setHstart(word w)			{ data.h_start = w; }
inline void VI_REGS::setVstart(word w)			{ data.v_start = w; }
inline void VI_REGS::setVburst(word w)			{ data.v_burst = w; }
inline void VI_REGS::setXscale(word w)			{ data.x_scale = w; }
inline void VI_REGS::setYscale(word w)			{ data.y_scale = w; }

inline void AI_REGS::setDramAddr(word w)		{ data.dram_addr = w; }
inline void AI_REGS::setLen(word w)
{
	data.len = w;
	//AiLenChanged
}
inline void AI_REGS::setControl(word w)			{ data.control = w & 0x1; }
inline void AI_REGS::setStatus(word w)			{ /*TODO*/ }
inline void AI_REGS::setDacrate(word w)			{ data.dacrate = w; }
inline void AI_REGS::setBitrate(word w)			{ data.bitrate = w; }

inline void PI_REGS::setDramAddr(word w)		{ data.dram_addr = w; }
inline void PI_REGS::setCartAddr(word w)		{ data.cart_addr = w; }
inline void PI_REGS::setRdLen(word w)			{ data.rd_len = w; }
inline void PI_REGS::setWrLen(word w)			{ data.wr_len = w; }
inline void PI_REGS::setStatus(word w)			{ data.status = w; }
inline void PI_REGS::setBsdDom1Lat(word w)		{ data.bsd_dom1_lat = w; }
inline void PI_REGS::setBsdDom1Pwd(word w)		{ data.bsd_dom1_pwd = w; }
inline void PI_REGS::setBsdDom1Pgs(word w)		{ data.bsd_dom1_pgs = w; }
inline void PI_REGS::setBsdDom1Rls(word w)		{ data.bsd_dom1_rls = w; }
inline void PI_REGS::setBsdDom2Lat(word w)		{ data.bsd_dom2_lat = w; }
inline void PI_REGS::setBsdDom2Pwd(word w)		{ data.bsd_dom2_pwd = w; }
inline void PI_REGS::setBsdDom2Pgs(word w)		{ data.bsd_dom2_pgs = w; }
inline void PI_REGS::setBsdDom2Rls(word w)		{ data.bsd_dom2_rls = w; }

inline void RI_REGS::setMode(word w)			{ data.mode = w; }
inline void RI_REGS::setConfig(word w)			{ data.config = w; }
inline void RI_REGS::setCurrentLoad(word w)		{ data.current_load = w; }
inline void RI_REGS::setSelect(word w)			{ data.select = w; }
inline void RI_REGS::setRefresh(word w)			{ data.refresh = w; }
inline void RI_REGS::setLatency(word w)			{ data.latency = w; }
inline void RI_REGS::setRerror(word w)			{ data.rerror = w; }
inline void RI_REGS::setWerror(word w)			{ data.werror = w; }

inline void SI_REGS::setDramAddr(word w)		{ data.dram_addr = w; }
inline void SI_REGS::setPifAddrRd64b(word w)	{ data.pif_addr_rd64b = w; }
inline void SI_REGS::setPifAddrWr64b(word w)	{ data.pif_addr_wr64b = w; }
inline void SI_REGS::setStatus(word w)			{ /*TODO*/ }

//****************************************************************************
//** GET METHODS					                                        **
//****************************************************************************

inline word RDRAM_REGS::getConfig()			{ return data.config; }
inline word RDRAM_REGS::getDeviceId()		{ return data.device_id; }
inline word RDRAM_REGS::getDelay()			{ return data.delay; }
inline word RDRAM_REGS::getMode()			{ return data.mode; }
inline word RDRAM_REGS::getRefInterval()	{ return data.ref_interval; }
inline word RDRAM_REGS::getRefRow()			{ return data.ref_row; }
inline word RDRAM_REGS::getRasInterval()	{ return data.ras_interval; }
inline word RDRAM_REGS::getMinInterval()	{ return data.min_interval; }
inline word RDRAM_REGS::getAddrSelect()		{ return data.addr_select; }
inline word RDRAM_REGS::getDeviceManuf()	{ return data.device_manuf; }

inline byte* SP_REGS::getDmem()				{ return data.dmem; }
inline byte* SP_REGS::getImem()				{ return data.imem; }
inline word SP_REGS::getMemAddr()			{ return data.mem_addr; }
inline word SP_REGS::getDramAddr()			{ return data.dram_addr; }
inline word SP_REGS::getRdLen()				{ return data.rd_len; }
inline word SP_REGS::getWrLen()				{ return data.wr_len; }
inline word SP_REGS::getStatus()			{ return data.status; }
inline word SP_REGS::getDmaFull()			{ return data.dma_full; }
inline word SP_REGS::getDmaBusy()			{ return data.dma_busy; }
inline word SP_REGS::getSemaphore()			{ return data.semaphore; }
inline word SP_REGS::getPc()				{ return data.pc; }
inline word SP_REGS::getIbist()				{ return data.ibist; }

inline word DPC_REGS::getStart()			{ return data.start; }
inline word DPC_REGS::getEnd()				{ return data.end; }
inline word DPC_REGS::getCurrent()			{ return data.current; }
inline word DPC_REGS::getStatus()			{ return data.status; }
inline word DPC_REGS::getClock()			{ return data.clock; }
inline word DPC_REGS::getBufBusy()			{ return data.bufbusy; }
inline word DPC_REGS::getPipeBusy()			{ return data.pipebusy; }
inline word DPC_REGS::getTmem()				{ return data.tmem; }

inline word DPS_REGS::getTbist()			{ return data.tbist; }
inline word DPS_REGS::getTestMode()			{ return data.test_mode; }
inline word DPS_REGS::getBufTestAddr()		{ return data.buftest_addr; }
inline word DPS_REGS::getBufTestData()		{ return data.buftest_data; }

inline word MI_REGS::getInitMode()			{ return data.init_mode; }
inline word MI_REGS::getVersion()			{ return data.version; }
inline word MI_REGS::getIntr()				{ return data.intr; }
inline word MI_REGS::getIntrMask()			{ return data.intr_mask; }

inline word VI_REGS::getStatus()			{ return data.status; }
inline word VI_REGS::getOrigin()			{ return data.origin; }
inline word VI_REGS::getWidth()				{ return data.width; }
inline word VI_REGS::getIntr()				{ return data.intr; }
inline word VI_REGS::getCurrent()			{ return data.current; }
inline word VI_REGS::getBurst()				{ return data.burst; }
inline word VI_REGS::getVsync()				{ return data.v_sync; }
inline word VI_REGS::getHsync()				{ return data.h_sync; }
inline word VI_REGS::getLeap()				{ return data.leap; }
inline word VI_REGS::getHstart()			{ return data.h_start; }
inline word VI_REGS::getVstart()			{ return data.v_start; }
inline word VI_REGS::getVburst()			{ return data.v_burst; }
inline word VI_REGS::getXscale()			{ return data.x_scale; }
inline word VI_REGS::getYscale()			{ return data.y_scale; }

inline word AI_REGS::getDramAddr()			{ return data.dram_addr; }
inline word AI_REGS::getLen()				{ return data.len; }
inline word AI_REGS::getControl()			{ return data.control; }
inline word AI_REGS::getStatus()			{ return data.status; }
inline word AI_REGS::getDacrate()			{ return data.dacrate; }
inline word AI_REGS::getBitrate()			{ return data.bitrate; }

inline word PI_REGS::getDramAddr()			{ return data.dram_addr; }
inline word PI_REGS::getCartAddr()			{ return data.cart_addr; }
inline word PI_REGS::getRdLen()				{ return data.rd_len; }
inline word PI_REGS::getWrLen()				{ return data.wr_len; }
inline word PI_REGS::getStatus()			{ return data.status; }
inline word PI_REGS::getBsdDom1Lat()		{ return data.bsd_dom1_lat; }
inline word PI_REGS::getBsdDom1Pwd()		{ return data.bsd_dom1_pwd; }
inline word PI_REGS::getBsdDom1Pgs()		{ return data.bsd_dom1_pgs; }
inline word PI_REGS::getBsdDom1Rls()		{ return data.bsd_dom1_rls; }
inline word PI_REGS::getBsdDom2Lat()		{ return data.bsd_dom2_lat; }
inline word PI_REGS::getBsdDom2Pwd()		{ return data.bsd_dom2_pwd; }
inline word PI_REGS::getBsdDom2Pgs()		{ return data.bsd_dom2_pgs; }
inline word PI_REGS::getBsdDom2Rls()		{ return data.bsd_dom2_rls; }

inline word RI_REGS::getMode()				{ return data.mode; }
inline word RI_REGS::getConfig()			{ return data.config; }
inline word RI_REGS::getCurrentLoad()		{ return data.current_load; }
inline word RI_REGS::getSelect()			{ return data.select; }
inline word RI_REGS::getRefresh()			{ return data.refresh; }
inline word RI_REGS::getLatency()			{ return data.latency; }
inline word RI_REGS::getRerror()			{ return data.rerror; }
inline word RI_REGS::getWerror()			{ return data.werror; }

inline word SI_REGS::getDramAddr()			{ return data.dram_addr; }
inline word SI_REGS::getPifAddrRd64b()		{ return data.pif_addr_rd64b; }
inline word SI_REGS::getPifAddrWr64b()		{ return data.pif_addr_wr64b; }
inline word SI_REGS::getStatus()			{ return data.status; }
