#include "StdAfx.h"

//****************************************************************************
//** CONSTRUCTORS					                                        **
//****************************************************************************

// MEMORY
MEMORY::MEMORY()
{
	rdram		= new RDRAM();
	rdram_regs	= new RDRAM_REGS();
	sp_regs		= new SP_REGS();
	dpc_regs	= new DPC_REGS();
	dps_regs	= new DPS_REGS();
	mi_regs		= new MI_REGS();
	vi_regs		= new VI_REGS();
	ai_regs		= new AI_REGS();
	pi_regs		= new PI_REGS();
	ri_regs		= new RI_REGS();
	si_regs		= new SI_REGS();
	pif_rom		= new PIF_ROM();
	pif_ram		= new PIF_RAM();
	memset(SRAM, 0, sizeof(SRAM));
	CIC_Chip = 0;
}

// MEMORY SEGMENT
MEM_SEG::MEM_SEG() :
	ptr(0)
{
}

// RDRAM
RDRAM::RDRAM()
{
	memset(data, 0, sizeof(data));
	ptr = data;
}

// RDRAM REGISTERS
RDRAM_REGS::RDRAM_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}



//****************************************************************************
//** DUMP METHODS					                                        **
//****************************************************************************

//

void RDRAM::dump(void) const
{
	cout << "*** RDRAM ***" << endl;
	dump_array(0x0, data, 0x40000);
	cout << "*** END OF RDRAM ***"<< endl;
}

void RDRAM::dump_range(word from, word to) const
{
	if (from >= to)
		return;
	cout << "*** RDRAM ***" << endl;
	dump_array(from, data + from - begining, (to - from));
	cout << "*** END OF RDRAM ***"<< endl;
}

void RDRAM_REGS::dump(void) const
{
	cout << "*** RDRAM REGISTERS ***" << endl;
	cout << "config = "		<< data.config		<< endl;
	cout << "device_id = "	<< data.device_id	<< endl;
	cout << "delay = "		<< data.delay		<< endl;
	cout << "mode = "		<< data.mode			<< endl;
	cout << "ref_interval = "<< data.ref_interval << endl;
	cout << "ref_row = "		<< data.ref_row		<< endl;
	cout << "ras_interval = "<< data.ras_interval << endl;
	cout << "min_interval = "<< data.min_interval << endl;
	cout << "addr_select = "	<< data.addr_select	<< endl;
	cout << "device_manuf = "<< data.device_manuf << endl;
	cout << "*** END OF RDRAM REGISTERS ***"<< endl;
}

// SP REGISTERS
SP_REGS::SP_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void SP_REGS::dump(void) const
{	
	cout << "*** SP REGISTERS ***" << endl;
	cout << "dmem =" << endl;
	dump_array(begining, data.dmem, 0x1000);
	cout << "imem =" << endl;
	dump_array(begining + 0x1000, data.imem, 0x1000);
	cout << "mem_addr = " << data.mem_addr << endl;
	cout << "dram_addr = " << data.dram_addr << endl;
	cout << "rd_len = " << data.rd_len << endl;
	cout << "wr_len = " << data.wr_len << endl;
	cout << "status = " << data.status << endl;
	cout << "dma_full = " << data.dma_full << endl;
	cout << "dma_busy = " << data.dma_busy << endl;
	cout << "semaphore = " << data.semaphore << endl;
	cout << "pc = " << data.pc << endl;
	cout << "ibist = " << data.ibist << endl;
	cout << "*** END OF SP REGISTERS ***" << endl;
}

void SP_REGS::dump_range_dmem(word from, word to) const
{
	if (from >= to)
		return;
	cout << "*** SP_REG->DMEM ***" << endl;
	dump_array(from, data.dmem + from - begining, (to - from));
	cout << "*** END OF SP_REG->DMEM ***"<< endl;
}

void SP_REGS::dump_range_imem(word from, word to) const
{
	if (from >= to)
		return;
	cout << "*** SP_REG->DMEM ***" << endl;
	dump_array(from, data.imem + from - begining, (to - from));
	cout << "*** END OF SP_REG->DMEM ***"<< endl;
}

// DPC REGISTERS
DPC_REGS::DPC_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void DPC_REGS::dump(void) const
{
	cout << "*** DPC REGISTERS ***" << endl;
	cout << "start = " << data.start << endl;
	cout << "end = " << data.end << endl;
	cout << "current = " << data.current << endl;
	cout << "status = " << data.status << endl;
	cout << "clock = " << data.clock << endl;
	cout << "bufbusy = " << data.bufbusy << endl;
	cout << "pipebusy = " << data.pipebusy << endl;
	cout << "tmem = " << data.tmem << endl;
	cout << "*** END OF DPC REGISTERS ***" << endl;
}

// DPC REGISTERS
DPS_REGS::DPS_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void DPS_REGS::dump(void) const
{
	cout << "*** DPS REGISTERS ***" << endl;
	cout << "tbist = " << data.tbist << endl;
	cout << "test_mode = " << data.test_mode << endl;
	cout << "buftest_addr = " << data.buftest_addr << endl;
	cout << "buftest_data = " << data.buftest_data << endl;
	cout << "*** END OF DPS REGISTERS ***" << endl;
}

// DPC REGISTERS
MI_REGS::MI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void MI_REGS::dump(void) const
{
	cout << "*** MI REGISTERS ***" << endl;
	cout << "init_mode = " << data.init_mode << endl;
	cout << "version = " << data.version << endl;
	cout << "intr = " << data.intr << endl;
	cout << "intr_mask = " << data.intr_mask << endl;
	cout << "*** END OF MI REGISTERS ***" << endl;
}

// DPC REGISTERS
VI_REGS::VI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void VI_REGS::dump(void) const
{
	cout << "*** VI REGISTERS ***" << endl;
	cout << "status = "<< data.status		<< endl;
	cout << "origin = "<< data.origin	<< endl;
	cout << "width = "<< data.width		<< endl;
	cout << "v_intr = "<< data.v_intr			<< endl;
	cout << "current = "<< data.current << endl;
	cout << "burst = "<< data.burst		<< endl;
	cout << "v_sync = "<< data.v_sync << endl;
	cout << "h_sync = "<< data.h_sync << endl;
	cout << "leap = "<< data.leap	<< endl;
	cout << "h_start = "<< data.h_start << endl;
	cout << "v_start = "<< data.v_start << endl;
	cout << "v_burst = "<< data.v_burst << endl;
	cout << "x_scale = "<< data.x_scale << endl;
	cout << "y_scale = "<< data.y_scale << endl;
	cout << "*** END OF VI REGISTERS ***"<< endl;
}

// DPC REGISTERS
AI_REGS::AI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void AI_REGS::dump(void) const
{
	cout << "*** AI REGISTERS ***" << endl;
	cout << "dram_addr = " << data.dram_addr << endl;
	cout << "len = " << data.len << endl;
	cout << "control = " << data.control << endl;
	cout << "status = " << data.status << endl;
	cout << "dacrate = " << data.dacrate << endl;
	cout << "bitrate = " << data.bitrate << endl;
	cout << "*** END OF AI REGISTERS ***" << endl;
}

// DPC REGISTERS
PI_REGS::PI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void PI_REGS::dump(void) const
{
	cout << "*** PI REGISTERS ***" << endl;
	cout << "dram_addr = "		<< data.dram_addr		<< endl;
	cout << "cart_addr = "	<< data.cart_addr	<< endl;
	cout << "rd_len = "		<< data.rd_len		<< endl;
	cout << "wr_len = "		<< data.wr_len			<< endl;
	cout << "status = "<< data.status << endl;
	cout << "bsd_dom1_lat = "		<< data.bsd_dom1_lat		<< endl;
	cout << "bsd_dom1_pwd = "<< data.bsd_dom1_pwd << endl;
	cout << "bsd_dom1_pgs = "<< data.bsd_dom1_pgs << endl;
	cout << "bsd_dom1_rls = "	<< data.bsd_dom1_rls	<< endl;
	cout << "bsd_dom2_lat = "<< data.bsd_dom2_lat << endl;
	cout << "bsd_dom2_pwd = "<< data.bsd_dom2_pwd << endl;
	cout << "bsd_dom2_pgs = "<< data.bsd_dom2_pgs << endl;
	cout << "bsd_dom2_rls = "<< data.bsd_dom2_rls << endl;
	cout << "*** END OF PI REGISTERS ***"<< endl;
}

// DPC REGISTERS
RI_REGS::RI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void RI_REGS::dump(void) const
{
	cout << "*** RI REGISTERS ***" << endl;
	cout << "mode = "		<< data.mode		<< endl;
	cout << "config = "	<< data.config	<< endl;
	cout << "current_load = "		<< data.current_load		<< endl;
	cout << "select = "		<< data.select			<< endl;
	cout << "refresh = "<< data.refresh << endl;
	cout << "latency = "		<< data.latency		<< endl;
	cout << "error = "<< data.error << endl;
	cout << "werror = "<< data.werror << endl;
	cout << "*** END OF RI REGISTERS ***"<< endl;
}

// DPC REGISTERS
SI_REGS::SI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void SI_REGS::dump(void) const
{
	cout << "*** SI REGISTERS ***" << endl;
	cout << "dram_addr = "		<< data.dram_addr		<< endl;
	cout << "pif_addr_rd64b = "	<< data.pif_addr_rd64b	<< endl;
	cout << "reserved = "		<< data.reserved		<< endl;
	cout << "reserved2 = "		<< data.reserved2			<< endl;
	cout << "pif_addr_wr64b = "<< data.pif_addr_wr64b << endl;
	cout << "reserved3 = "		<< data.reserved3		<< endl;
	cout << "status = "<< data.status << endl;
	cout << "*** END OF SI REGISTERS ***"<< endl;
}

// DPC REGISTERS
PIF_ROM::PIF_ROM()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void PIF_ROM::dump(void) const
{
	cout << "*** SI REGISTERS ***" << endl;
	dump_array(0x0, data, 0x3E);
	cout << "*** END OF SI REGISTERS ***"<< endl;
}

// DPC REGISTERS
PIF_RAM::PIF_RAM()
{
	memset(&data, 0, sizeof(data));
	ptr = &data;
}

void PIF_RAM::dump(void) const
{
	cout << "*** SI REGISTERS ***" << endl;
	dump_array(0x0, data, 0x2);
	cout << "*** END OF SI REGISTERS ***"<< endl;
}

void MEMORY::dma_pi_read()
{
	/*
	int i;
	for (i=0; i < ((pi_regs->data.rd_len_reg & 0xFFF) + 1); i++)
		pi_regs->[(pi_regs->data.mem_addr_reg & 0xFFF) + i] =
		rdram->data[(pi_regs->data.dram_addr_reg & 0xFFFFFF) + i];
	*/
}

void MEMORY::dma_pi_write()
{
	/*
	int i;
	for (i=0; i < ((pi_regs->data.rd_len_reg & 0xFFF) + 1); i++)
		pi_regs->[(pi_regs->data.mem_addr_reg & 0xFFF) + i] =
		rdram->data[(pi_regs->data.dram_addr_reg & 0xFFFFFF) + i];
		*/
}

void MEMORY::dma_sp_write()
{
	if ((sp_regs->data.mem_addr & 0x1000) > 0)
	{
		memcpy(sp_regs->data.imem + (sp_regs->data.mem_addr & 0xFFF),
			rdram->data + (sp_regs->data.dram_addr & 0xFFFFFF),
			(sp_regs->data.rd_len & 0xFFF) + 1);
	}
	else
	{
		memcpy(sp_regs->data.dmem + (sp_regs->data.mem_addr & 0xFFF),
			rdram->data + (sp_regs->data.dram_addr & 0xFFFFFF),
			(sp_regs->data.rd_len & 0xFFF) + 1);
	}
}

void MEMORY::dma_sp_read()
{
	if ((sp_regs->data.mem_addr & 0x1000) > 0)
	{
		memcpy(rdram->data + (sp_regs->data.dram_addr & 0xFFFFFF),
			sp_regs->data.imem + (sp_regs->data.mem_addr & 0xFFF),
			(sp_regs->data.wr_len & 0xFFF) + 1);
	}
	else
	{
		memcpy(rdram->data + (sp_regs->data.dram_addr & 0xFFFFFF),
			sp_regs->data.dmem + (sp_regs->data.mem_addr & 0xFFF),
			(sp_regs->data.wr_len & 0xFFF) + 1);
	}
}

void MEMORY::dma_si_write()
{
	if (si_regs->data.pif_addr_wr64b != 0x1FC007C0)
	{
		cout << "unknown SI use" << endl;
	}

	memcpy(pif_ram->data, rdram->data + si_regs->data.dram_addr, 64);
}

void MEMORY::dma_si_read()
{
	if (si_regs->data.pif_addr_rd64b != 0x1FC007C0)
	{
		cout << "unknown SI use" << endl;
	}

	memcpy(rdram->data + si_regs->data.dram_addr, pif_ram->data, 64);
}