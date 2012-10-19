#include "StdAfx.h"

//****************************************************************************
//** MEMORY																	**
//****************************************************************************
MEMORY::MEMORY() :
	rdram		(*new RDRAM()),
	rdram_regs	(*new RDRAM_REGS()),
	sp_regs		(*new SP_REGS()),
	dpc_regs	(*new DPC_REGS()),
	dps_regs	(*new DPS_REGS()),
	mi_regs		(*new MI_REGS()),
	vi_regs		(*new VI_REGS()),
	ai_regs		(*new AI_REGS()),
	pi_regs		(*new PI_REGS()),
	ri_regs		(*new RI_REGS()),
	si_regs		(*new SI_REGS()),
	pif_rom		(*new PIF_ROM()),
	pif_ram		(*new PIF_RAM())
{
	memset(SRAM, 0, sizeof(SRAM));
	cic_chip = 0;
	check_intr = false;
}

// MEMORY SEGMENT
MEM_SEG::MEM_SEG() :
	ptr(0)
{
}

char* MEM_SEG::operator[] (const dword address) const
{
	return (char*) ptr + address;
}

//****************************************************************************
//** SEGMENTS CONSTRUCTORS					                                **
//****************************************************************************

// RDRAM
RDRAM::RDRAM()
{
	memset(data, 0, sizeof(data));
	ptr = (char*) data;
}

// RDRAM REGISTERS
RDRAM_REGS::RDRAM_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// SP REGISTERS
SP_REGS::SP_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// DPC REGISTERS
DPC_REGS::DPC_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// DPS REGISTERS
DPS_REGS::DPS_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// MI REGISTERS
MI_REGS::MI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// VI REGISTERS
VI_REGS::VI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// AI REGISTERS
AI_REGS::AI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// PI REGISTERS
PI_REGS::PI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// RI REGISTERS
RI_REGS::RI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// SI REGISTERS
SI_REGS::SI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// PIF_ROM REGISTERS
PIF_ROM::PIF_ROM()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// PIF_RAM REGISTERS
PIF_RAM::PIF_RAM()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

//****************************************************************************
//** DUMP METHODS					                                        **
//****************************************************************************

void RDRAM::dump(void) const
{
	cout << "*** RDRAM ***" << endl;
	dump_array(begining, data, 0x40000, 16);
	cout << "*** END OF RDRAM ***"<< endl;
}

void RDRAM::dump_range(word from, word to) const
{
	if (from >= to)
		return;
	cout << "*** RDRAM ***" << endl;
	dump_array(from, data + from - begining, (to - from), 16);
	cout << "*** END OF RDRAM ***"<< endl;
}

void RDRAM_REGS::dump(void) const
{
	cout << "*** RDRAM REGISTERS ***"					<< endl;
	cout << "config = "			<< data.config			<< endl;
	cout << "device_id = "		<< data.device_id		<< endl;
	cout << "delay = "			<< data.delay			<< endl;
	cout << "mode = "			<< data.mode			<< endl;
	cout << "ref_interval = "	<< data.ref_interval	<< endl;
	cout << "ref_row = "		<< data.ref_row			<< endl;
	cout << "ras_interval = "	<< data.ras_interval	<< endl;
	cout << "min_interval = "	<< data.min_interval	<< endl;
	cout << "addr_select = "	<< data.addr_select		<< endl;
	cout << "device_manuf = "	<< data.device_manuf	<< endl;
	cout << "*** END OF RDRAM REGISTERS ***"			<< endl;
}

void SP_REGS::dump(void) const
{	
	cout << "*** SP REGISTERS ***"						<< endl;
	cout << "dmem ="									<< endl;
	dump_array(begining, data.dmem, 0x1000, 16);
	cout << "imem ="									<< endl;
	dump_array(begining + 0x1000, data.imem, 0x1000, 16);
	cout << "mem_addr = "	<< data.mem_addr			<< endl;
	cout << "dram_addr = "	<< data.dram_addr			<< endl;
	cout << "rd_len = "		<< data.rd_len				<< endl;
	cout << "wr_len = "		<< data.wr_len				<< endl;
	cout << "status = "		<< data.status				<< endl;
	cout << "dma_full = "	<< data.dma_full			<< endl;
	cout << "dma_busy = "	<< data.dma_busy			<< endl;
	cout << "semaphore = "	<< data.semaphore			<< endl;
	cout << "pc = "			<< data.pc					<< endl;
	cout << "ibist = "		<< data.ibist				<< endl;
	cout << "*** END OF SP REGISTERS ***"				<< endl;
}

void SP_REGS::dump_range_dmem(word from, word to) const
{
	if (from >= to)
		return;
	cout << "*** SP_REG->DMEM ***" << endl;
	dump_array(from, data.dmem + from - begining, (to - from), 16);
	cout << "*** END OF SP_REG->DMEM ***"<< endl;
}

void SP_REGS::dump_range_imem(word from, word to) const
{
	if (from >= to)
		return;
	cout << "*** SP_REG->DMEM ***" << endl;
	dump_array(from, data.imem + from - begining, (to - from), 16);
	cout << "*** END OF SP_REG->DMEM ***"<< endl;
}

void DPC_REGS::dump(void) const
{
	cout << "*** DPC REGISTERS ***"						<< endl;
	cout << "start = "		<< data.start				<< endl;
	cout << "end = "		<< data.end					<< endl;
	cout << "current = "	<< data.current				<< endl;
	cout << "status = "		<< data.status				<< endl;
	cout << "clock = "		<< data.clock				<< endl;
	cout << "bufbusy = "	<< data.bufbusy				<< endl;
	cout << "pipebusy = "	<< data.pipebusy			<< endl;
	cout << "tmem = "		<< data.tmem				<< endl;
	cout << "*** END OF DPC REGISTERS ***"				<< endl;
}

void DPS_REGS::dump(void) const
{
	cout << "*** DPS REGISTERS ***"						<< endl;
	cout << "tbist = "			<< data.tbist			<< endl;
	cout << "test_mode = "		<< data.test_mode		<< endl;
	cout << "buftest_addr = "	<< data.buftest_addr	<< endl;
	cout << "buftest_data = "	<< data.buftest_data	<< endl;
	cout << "*** END OF DPS REGISTERS ***"				<< endl;
}

void MI_REGS::dump(void) const
{
	cout << "*** MI REGISTERS ***"						<< endl;
	cout << "init_mode = "	<< data.init_mode			<< endl;
	cout << "version = "	<< data.version				<< endl;
	cout << "intr = "		<< data.intr				<< endl;
	cout << "intr_mask = "	<< data.intr_mask			<< endl;
	cout << "*** END OF MI REGISTERS ***"				<< endl;
}

void VI_REGS::dump(void) const
{
	cout << "*** VI REGISTERS ***"						<< endl;
	cout << "status = "		<< data.status				<< endl;
	cout << "origin = "		<< data.origin				<< endl;
	cout << "width = "		<< data.width				<< endl;
	cout << "v_intr = "		<< data.v_intr				<< endl;
	cout << "current = "	<< data.current				<< endl;
	cout << "burst = "		<< data.burst				<< endl;
	cout << "v_sync = "		<< data.v_sync				<< endl;
	cout << "h_sync = "		<< data.h_sync				<< endl;
	cout << "leap = "		<< data.leap				<< endl;
	cout << "h_start = "	<< data.h_start				<< endl;
	cout << "v_start = "	<< data.v_start				<< endl;
	cout << "v_burst = "	<< data.v_burst				<< endl;
	cout << "x_scale = "	<< data.x_scale				<< endl;
	cout << "y_scale = "	<< data.y_scale				<< endl;
	cout << "*** END OF VI REGISTERS ***"				<< endl;
}

void AI_REGS::dump(void) const
{
	cout << "*** AI REGISTERS ***"						<< endl;
	cout << "dram_addr = "	<< data.dram_addr			<< endl;
	cout << "len = "		<< data.len					<< endl;
	cout << "control = "	<< data.control				<< endl;
	cout << "status = "		<< data.status				<< endl;
	cout << "dacrate = "	<< data.dacrate				<< endl;
	cout << "bitrate = "	<< data.bitrate				<< endl;
	cout << "*** END OF AI REGISTERS ***"				<< endl;
}

void PI_REGS::dump(void) const
{
	cout << "*** PI REGISTERS ***"						<< endl;
	cout << "dram_addr = "		<< data.dram_addr		<< endl;
	cout << "cart_addr = "		<< data.cart_addr		<< endl;
	cout << "rd_len = "			<< data.rd_len			<< endl;
	cout << "wr_len = "			<< data.wr_len			<< endl;
	cout << "status = "			<< data.status			<< endl;
	cout << "bsd_dom1_lat = "	<< data.bsd_dom1_lat	<< endl;
	cout << "bsd_dom1_pwd = "	<< data.bsd_dom1_pwd	<< endl;
	cout << "bsd_dom1_pgs = "	<< data.bsd_dom1_pgs	<< endl;
	cout << "bsd_dom1_rls = "	<< data.bsd_dom1_rls	<< endl;
	cout << "bsd_dom2_lat = "	<< data.bsd_dom2_lat	<< endl;
	cout << "bsd_dom2_pwd = "	<< data.bsd_dom2_pwd	<< endl;
	cout << "bsd_dom2_pgs = "	<< data.bsd_dom2_pgs	<< endl;
	cout << "bsd_dom2_rls = "	<< data.bsd_dom2_rls	<< endl;
	cout << "*** END OF PI REGISTERS ***"<< endl;
}

void RI_REGS::dump(void) const
{
	cout << "*** RI REGISTERS ***"						<< endl;
	cout << "mode = "			<< data.mode			<< endl;
	cout << "config = "			<< data.config			<< endl;
	cout << "current_load = "	<< data.current_load	<< endl;
	cout << "select = "			<< data.select			<< endl;
	cout << "refresh = "		<< data.refresh			<< endl;
	cout << "latency = "		<< data.latency			<< endl;
	cout << "error = "			<< data.rerror			<< endl;
	cout << "werror = "			<< data.werror			<< endl;
	cout << "*** END OF RI REGISTERS ***"				<< endl;
}

void SI_REGS::dump(void) const
{
	cout << "*** SI REGISTERS ***"						<< endl;
	cout << "dram_addr = "		<< data.dram_addr		<< endl;
	cout << "pif_addr_rd64b = "	<< data.pif_addr_rd64b	<< endl;
	cout << "reserved = "		<< data.reserved		<< endl;
	cout << "reserved2 = "		<< data.reserved2		<< endl;
	cout << "pif_addr_wr64b = "	<< data.pif_addr_wr64b	<< endl;
	cout << "reserved3 = "		<< data.reserved3		<< endl;
	cout << "status = "			<< data.status			<< endl;
	cout << "*** END OF SI REGISTERS ***"				<< endl;
}

void PIF_ROM::dump(void) const
{
	cout << "*** SI REGISTERS ***" << endl;
	dump_array(begining, data, 0x3E, 16);
	cout << "*** END OF SI REGISTERS ***"<< endl;
}

void PIF_RAM::dump(void) const
{
	cout << "*** SI REGISTERS ***" << endl;
	dump_array(begining, data, 0x2, 16);
	cout << "*** END OF SI REGISTERS ***"<< endl;
}

//****************************************************************************
//** SET METHODS					                                        **
//****************************************************************************

void RDRAM_REGS::setConfig(word arg)
{
	data.config = arg;
}
void RDRAM_REGS::setDeviceId(word arg)
{
	data.device_id = arg;
}
void RDRAM_REGS::setDelay(word arg)
{
	data.delay = arg;
}
void RDRAM_REGS::setMode(word arg)
{
	data.mode = arg;
}
void RDRAM_REGS::setRefInterval(word arg)
{
	data.ref_interval = arg;
}
void RDRAM_REGS::setRefRow(word arg)
{
	data.ref_row = arg;
}
void RDRAM_REGS::setRasInterval(word arg)
{
	data.ras_interval = arg;
}
void RDRAM_REGS::setMinInterval(word arg)
{
	data.min_interval = arg;
}
void RDRAM_REGS::setAddrSelect(word arg)
{
	data.addr_select = arg;
}
void RDRAM_REGS::setDeviceManuf(word arg)
{
	data.device_manuf = arg;
}

void SP_REGS::setMemAddr(word arg)
{
	data.mem_addr = arg;
}
void SP_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
void SP_REGS::setRdLen(word arg)
{
	data.rd_len = arg;
}
void SP_REGS::setWrlen(word arg)
{
	data.wr_len = arg;
}
void SP_REGS::setStatus(word arg)
{
	data.status = arg;
}
void SP_REGS::setDmaFull(word arg)
{
	data.dma_full = arg;
}
void SP_REGS::setDmaBusy(word arg)
{
	data.dma_busy = arg;
}
void SP_REGS::setSemaphore(word arg)
{
	data.semaphore = arg;
}
void SP_REGS::setPc(word arg)
{
	data.pc = arg;
}
void SP_REGS::setIbist(word arg)
{
	data.ibist = arg;
}

void DPC_REGS::setStart(word arg)
{
	data.start = arg;
}
void DPC_REGS::setEnd(word arg)
{
	data.end = arg;
}
void DPC_REGS::setCurrent(word arg)
{
	data.current = arg;
}
void DPC_REGS::setStatus(word arg)
{
	data.status = arg;
}
void DPC_REGS::setClock(word arg)
{
	data.clock = arg;
}
void DPC_REGS::setBufBusy(word arg)
{
	data.bufbusy = arg;
}
void DPC_REGS::setPipeBusy(word arg)
{
	data.pipebusy = arg;
}
void DPC_REGS::setTmem(word arg)
{
	data.tmem = arg;
}

void DPS_REGS::setTbist(word arg)
{
	data.tbist = arg;
}
void DPS_REGS::setTestMode(word arg)
{
	data.test_mode = arg;
}
void DPS_REGS::setBufTestAddr(word arg)
{
	data.buftest_addr = arg;
}
void DPS_REGS::setBuftestData(word arg)
{
	data.buftest_data = arg;
}

void MI_REGS::setInitMode(word arg)
{
	data.init_mode = arg;
}
void MI_REGS::setVersion(word arg)
{
	data.version = arg;
}
void MI_REGS::setIntr(word arg)
{
	data.intr = arg;
}
void MI_REGS::setIntrMask(word arg)
{
	data.intr_mask = arg;
}

void VI_REGS::setStatus(word arg)
{
	data.status = arg;
}
void VI_REGS::setOrigin(word arg)
{
	data.origin = arg;
}
void VI_REGS::setWidth(word arg)
{
	data.width = arg;
}
void VI_REGS::setVintr(word arg)
{
	data.v_intr = arg;
}
void VI_REGS::setCurrent(word arg)
{
	data.current = arg;
}
void VI_REGS::setBurst(word arg)
{
	data.burst = arg;
}
void VI_REGS::setVsync(word arg)
{
	data.v_sync = arg;
}
void VI_REGS::setHsync(word arg)
{
	data.h_sync = arg;
}
void VI_REGS::setLeap(word arg)
{
	data.leap = arg;
}
void VI_REGS::setHstart(word arg)
{
	data.h_start = arg;
}
void VI_REGS::setVstart(word arg)
{
	data.v_start = arg;
}
void VI_REGS::setVburst(word arg)
{
	data.v_burst = arg;
}
void VI_REGS::setXscale(word arg)
{
	data.x_scale = arg;
}
void VI_REGS::setYscale(word arg)
{
	data.y_scale = arg;
}

void AI_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
void AI_REGS::setLen(word arg)
{
	data.len = arg;
}
void AI_REGS::setControl(word arg)
{
	data.control = arg;
}
void AI_REGS::setStatus(word arg)
{
	data.status = arg;
}
void AI_REGS::setDacrate(word arg)
{
	data.dacrate = arg;
}
void AI_REGS::setBitrate(word arg)
{
	data.bitrate = arg;
}

void PI_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
void PI_REGS::setCartAddr(word arg)
{
	data.cart_addr = arg;
}
void PI_REGS::setRdLen(word arg)
{
	data.rd_len = arg;
}
void PI_REGS::setWrLen(word arg)
{
	data.wr_len = arg;
}
void PI_REGS::setStatus(word arg)
{
	data.status = arg;
}
void PI_REGS::setBsdDom1Lat(word arg)
{
	data.bsd_dom1_lat = arg;
}
void PI_REGS::setBsdDom1pwd(word arg)
{
	data.bsd_dom1_pwd = arg;
}
void PI_REGS::setBsdDom1Pgs(word arg)
{
	data.bsd_dom1_pgs = arg;
}
void PI_REGS::setBsdDom1Rls(word arg)
{
	data.bsd_dom1_rls = arg;
}
void PI_REGS::setBsdDom2Lat(word arg)
{
	data.bsd_dom2_lat = arg;
}
void PI_REGS::setBsdDom2Pwd(word arg)
{
	data.bsd_dom2_pwd = arg;
}
void PI_REGS::setBsdDom2Pgs(word arg)
{
	data.bsd_dom2_pgs = arg;
}
void PI_REGS::setBsdDom2Rls(word arg)
{
	data.bsd_dom2_rls = arg;
}

void RI_REGS::setMode(word arg)
{
	data.mode = arg;
}
void RI_REGS::setConfig(word arg)
{
	data.config = arg;
}
void RI_REGS::setCurrentLoad(word arg)
{
	data.current_load = arg;
}
void RI_REGS::setSelect(word arg)
{
	data.select = arg;
}
void RI_REGS::setRefresh(word arg)
{
	data.refresh = arg;
}
void RI_REGS::setLatency(word arg)
{
	data.latency = arg;
}
void RI_REGS::setError(word arg)
{
	data.error = arg;
}
void RI_REGS::setWerror(word arg)
{
	data.werror = arg;
}

void SI_REGS::setDramAddr(word arg)
{
	data.dram_addr = arg;
}
void SI_REGS::setPifAddrRd64b(word arg)
{
	data.pif_addr_rd64b = arg;
}
void SI_REGS::setPifAddrWr64b(word arg)
{
	data.pif_addr_wr64b = arg;
}
void SI_REGS::setStatus(word arg)
{
	data.status = arg;
}


void MEMORY::dma_pi_read()
{
	word invDramAddr = type_to_binary<word>(pi_regs.getDramAddr());
	word invCartAddr = type_to_binary<word>(pi_regs.getCartAddr());
	word invRdLen = type_to_binary<word>(pi_regs.getRdLen());

	memcpy((*rom)[0] + (invCartAddr & 0xFFFFFFF),
		rdram[0] + (invDramAddr & 0xFFFFFFF),
		(invRdLen & 0xFFFFFFF) + 1);
	
	write<word>(pi_regs.getStatus() & ~PI_STATUS_DMA_BUSY, 0x04600010);
	write<word>(mi_regs.getIntr() | MI_INTR_PI, 0x04300008);
	check_intr = true;

	cout << "*** pi_read ***" << endl;
}

void MEMORY::dma_pi_write()
{
	word invDramAddr = type_to_binary<word>(pi_regs.getDramAddr());
	word invCartAddr = type_to_binary<word>(pi_regs.getCartAddr());
	word invWrLen = type_to_binary<word>(pi_regs.getWrLen());

	memcpy(rdram[0] + (invDramAddr & 0xFFFFFFF),
		(*rom)[0] + (invCartAddr & 0xFFFFFFF),
		(invWrLen & 0xFFFFFFF) + 1);
	
	write<word>(pi_regs.getStatus() & ~PI_STATUS_DMA_BUSY, 0x04600010);
	write<word>(mi_regs.getIntr() | MI_INTR_PI, 0x04300008);
	check_intr = true;

	cout << "*** pi_write ***" << endl;
	//dump_array(invDramAddr, (const byte *) rdram[0] + (invDramAddr & 0xFFFFFF) + 0xFFF1000, (invWrLen & 0xFFF) + 1, 16);
	//cout << "*** END OF RDRAM ***"<< endl;
}

void MEMORY::dma_sp_write()
{
	word invMemAddr = type_to_binary<word>(sp_regs.getMemAddr());
	word invDramAddr = type_to_binary<word>(sp_regs.getDramAddr());
	word invWrLen = type_to_binary<word>(sp_regs.getWrLen());

	if ((invWrLen & 0x1000) > 0)
	{
		memcpy(rdram[0] + (invDramAddr & 0xFFFFFFF),
			(sp_regs.getImem()) + (invMemAddr & 0xFFF),
			(invWrLen & 0xFFF) + 1);

		cout << "*** sp_imem_write ***" << endl;
		//dump_array(sp_regs.getDramAddr(), (const byte*) rdram.ptr + (sp_regs.getDramAddr() & 0xFFFFFF), (sp_regs.getWrLen() & 0xFFF) + 1, 16);
		//cout << "*** END OF RDRAM ***"<< endl;
	}
	else
	{
		memcpy(rdram[0] + (invDramAddr & 0xFFFFFFF),
			sp_regs.getDmem() + (invMemAddr & 0xFFF),
			(invWrLen & 0xFFF) + 1);

		cout << "*** sp_dmem_write ***" << endl;
		//dump_array(sp_regs.getDramAddr(), (const byte*) rdram.ptr + (sp_regs.getDramAddr() & 0xFFFFFF), (sp_regs.getWrLen() & 0xFFF) + 1, 16);
		//cout << "*** END OF RDRAM ***"<< endl;
	}
	
	write<word>(0, 0x04040018);
	write<word>(si_regs.getStatus() & ~SP_STATUS_DMA_BUSY, 0x04040010);
}

void MEMORY::dma_sp_read()
{
	word invMemAddr = type_to_binary<word>(sp_regs.getMemAddr());
	word invDramAddr = type_to_binary<word>(sp_regs.getDramAddr());
	word invWrLen = type_to_binary<word>(sp_regs.getWrLen());

	if ((invWrLen & 0x1000) > 0)
	{
		memcpy((sp_regs.getImem()) + (invMemAddr & 0xFFF),
			rdram.ptr + (invDramAddr & 0xFFFFFFF),
			(invWrLen & 0xFFF) + 1);

		cout << "*** sp_imem_read ***" << endl;
		//dump_array(sp_regs.getMemAddr(), sp_regs.getImem() + (sp_regs.getMemAddr() & 0xFFF), (sp_regs.getRdLen() & 0xFFF) + 1, 16);
		//cout << "*** END OF RDRAM ***"<< endl;
	}
	else
	{
		memcpy(sp_regs.getDmem() + (invMemAddr & 0xFFF),
			rdram.ptr + (invDramAddr & 0xFFFFFFF),
			(invWrLen & 0xFFF) + 1);

		cout << "*** sp_dmem_read ***" << endl;
		//dump_array(sp_regs.getMemAddr(), sp_regs.getDmem() + (sp_regs.getMemAddr() & 0xFFF), (sp_regs.getRdLen() & 0xFFF) + 1, 16);
		//cout << "*** END OF RDRAM ***"<< endl;
	}
			
	write<word>(0, 0x04040018);
	write<word>(si_regs.getStatus() & ~SP_STATUS_DMA_BUSY, 0x04040010);
}

void MEMORY::dma_si_write()
{
	word invDramAddr = type_to_binary<word>(si_regs.getDramAddr());
	word invPifAddrWr64b = type_to_binary<word>(si_regs.getPifAddrWr64b());

	if (si_regs.getPifAddrWr64b() != 0x1FC007C0)
	{
		cout << "unknown SI use" << endl;
	}

	memcpy(rdram[0] + (invDramAddr & 0xFFFFFFF), pif_ram[0] + (invPifAddrWr64b & 0xFF), 64);

	write<word>(mi_regs.getIntr() | MI_INTR_SI, 0x04300008);
	write<word>(si_regs.getStatus() | SI_STATUS_INTERRUPT, 0x04800018);
	check_intr = true;

	cout << "*** si_write ***" << endl;
	//dump_array(si_regs.getDramAddr(), (const byte*) rdram.ptr + si_regs.getDramAddr(), 64, 16);
	//cout << "*** END OF RDRAM ***"<< endl;
}

void MEMORY::dma_si_read()
{
	word invDramAddr = type_to_binary<word>(si_regs.getDramAddr());
	word invPifAddrRd64b = type_to_binary<word>(si_regs.getPifAddrRd64b());

	if (si_regs.getPifAddrRd64b() != 0x1FC007C0)
	{
		cout << "unknown SI use" << endl;
	}

	memcpy(pif_ram[0] + (invPifAddrRd64b & 0xFF), rdram[0] + (invDramAddr & 0xFFFFFFF), 64);
	
	write<word>(mi_regs.getIntr() | MI_INTR_SI, 0x04300008);
	write<word>(si_regs.getStatus() | SI_STATUS_INTERRUPT, 0x04800018);
	check_intr = true;

	cout << "*** si_read ***" << endl;
	//dump_array(si_regs.getPifAddrRd64b(), (byte*) pif_ram.ptr + si_regs.getPifAddrRd64b(), 64, 16);
	//cout << "*** END OF RDRAM ***"<< endl;
}

bool is_address_defined(dword address)
{
	if (0x80000000 <= address && address <= 0xBFFFFFFF)
		return true;
	/*
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
