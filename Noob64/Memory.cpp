#include "StdAfx.h"

//****************************************************************************
//** CONSTRUCTORS					                                        **
//****************************************************************************

// MEMORY
MEMORY::MEMORY()
{
	rdram = new RDRAM();
	rdram_regs = new RDRAM_REGS();
	sp_regs = new SP_REGS();
	dpc_regs = new DPC_REGS();
	dps_regs = new DPS_REGS();
	mi_regs = new MI_REGS();
	vi_regs = new VI_REGS();
	ai_regs = new AI_REGS();
	pi_regs = new PI_REGS();
	ri_regs = new RI_REGS();
	si_regs = new SI_REGS();
}

// MEMORY SEGMENT
MEM_SEG::MEM_SEG() :
	ptr(0)
{
}

// RDRAM
RDRAM::RDRAM()
{
	memset(rdram, 0, sizeof(rdram));
	ptr = rdram;
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

void RDRAM::dump(void) const
{
	cout << "*** RDRAM ***" << endl;
	for (unsigned int i = 0; i < 128; i += sizeof(word))
	{
		word data = *((word *)(rdram + i));
		// print address
		char addr[8];
		_itoa_s(i, addr, 16);
		cout << format_number(string(8 - strlen(addr), '0') + addr, ' ', 2) << " : ";
		// print data
		char mem[33];
		_itoa_s(data, mem, 2);
		cout << format_number(string(sizeof(word) * 8 - strlen(mem), '0') + mem, ' ', 8) << endl;
	}
	cout << "*** END OF RDRAM ***"<< endl;
}

void RDRAM_REGS::dump(void) const
{
	cout << "*** RDRAM REGISTERS ***" << endl;
	cout << "	config = "			<< data.config		<< endl;
	cout << "	device_id = "		<< data.device_id	<< endl;
	cout << "	delay = "			<< data.delay		<< endl;
	cout << "	mode = "			<< data.mode			<< endl;
	cout << "	ref_interval = "	<< data.ref_interval << endl;
	cout << "	ref_row = "			<< data.ref_row		<< endl;
	cout << "	ras_interval = "	<< data.ras_interval << endl;
	cout << "	min_interval = "	<< data.min_interval << endl;
	cout << "	addr_select = "		<< data.addr_select	<< endl;
	cout << "	device_manuf = "	<< data.device_manuf << endl;
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
	cout << "	mem_addr_reg = " << data.mem_addr_reg << endl;
	cout << "	dram_addr_reg = " << data.dram_addr_reg << endl;
	cout << "	rd_len_reg = " << data.rd_len_reg << endl;
	cout << "	wr_len_reg = " << data.wr_len_reg << endl;
	cout << "	status_reg = " << data.status_reg << endl;
	cout << "	dma_full_reg = " << data.dma_full_reg << endl;
	cout << "	dma_busy_reg = " << data.dma_busy_reg << endl;
	cout << "	semaphore_reg = " << data.semaphore_reg << endl;
	cout << "	pc_reg = " << data.pc_reg << endl;
	cout << "	ibist_reg = " << data.ibist_reg << endl;
	cout << "*** END OF SP REGISTERS ***" << endl;
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
	cout << "	start_reg = " << data.start_reg << endl;
	cout << "	end_reg = " << data.end_reg << endl;
	cout << "	current_reg = " << data.current_reg << endl;
	cout << "	status_reg = " << data.status_reg << endl;
	cout << "	clock_reg = " << data.clock_reg << endl;
	cout << "	bufbusy_reg = " << data.bufbusy_reg << endl;
	cout << "	pipebusy_reg = " << data.pipebusy_reg << endl;
	cout << "	tmem_reg = " << data.tmem_reg << endl;
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
	cout << "	tbist_reg = " << data.tbist_reg << endl;
	cout << "	test_mode_reg = " << data.test_mode_reg << endl;
	cout << "	buftest_addr_reg = " << data.buftest_addr_reg << endl;
	cout << "	buftest_data_reg = " << data.buftest_data_reg << endl;
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
	cout << "	init_mode_reg = " << data.init_mode_reg << endl;
	cout << "	version_reg = " << data.version_reg << endl;
	cout << "	intr_reg = " << data.intr_reg << endl;
	cout << "	intr_mask_reg = " << data.intr_mask_reg << endl;
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
	cout << "	status_reg = "			<< data.status_reg		<< endl;
	cout << "	origin_reg = "		<< data.origin_reg	<< endl;
	cout << "	width_reg = "			<< data.width_reg		<< endl;
	cout << "	v_intr_reg = "			<< data.v_intr_reg			<< endl;
	cout << "	current_reg = "	<< data.current_reg << endl;
	cout << "	burst_reg = "			<< data.burst_reg		<< endl;
	cout << "	v_sync_reg = "	<< data.v_sync_reg << endl;
	cout << "	h_sync_reg = "	<< data.h_sync_reg << endl;
	cout << "	leap_reg = "		<< data.leap_reg	<< endl;
	cout << "	h_start_reg = "	<< data.h_start_reg << endl;
	cout << "	v_start_reg = "	<< data.v_start_reg << endl;
	cout << "	v_burst_reg = "	<< data.v_burst_reg << endl;
	cout << "	x_scale_reg = "	<< data.x_scale_reg << endl;
	cout << "	y_scale_reg = "	<< data.y_scale_reg << endl;
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
	cout << "	dram_addr_reg = " << data.dram_addr_reg << endl;
	cout << "	len_reg = " << data.len_reg << endl;
	cout << "	control_reg = " << data.control_reg << endl;
	cout << "	status_reg = " << data.status_reg << endl;
	cout << "	dacrate_reg = " << data.dacrate_reg << endl;
	cout << "	bitrate_reg = " << data.bitrate_reg << endl;
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
	cout << "	dram_addr_reg = "			<< data.dram_addr_reg		<< endl;
	cout << "	cart_addr_reg = "		<< data.cart_addr_reg	<< endl;
	cout << "	rd_len_reg = "			<< data.rd_len_reg		<< endl;
	cout << "	wr_len_reg = "			<< data.wr_len_reg			<< endl;
	cout << "	status_reg = "	<< data.status_reg << endl;
	cout << "	bsd_dom1_lat_reg = "			<< data.bsd_dom1_lat_reg		<< endl;
	cout << "	bsd_dom1_pwd_reg = "	<< data.bsd_dom1_pwd_reg << endl;
	cout << "	bsd_dom1_pgs_reg = "	<< data.bsd_dom1_pgs_reg << endl;
	cout << "	bsd_dom1_rls_reg = "		<< data.bsd_dom1_rls_reg	<< endl;
	cout << "	bsd_dom2_lat_reg = "	<< data.bsd_dom2_lat_reg << endl;
	cout << "	bsd_dom2_pwd_reg = "	<< data.bsd_dom2_pwd_reg << endl;
	cout << "	bsd_dom2_pgs_reg = "	<< data.bsd_dom2_pgs_reg << endl;
	cout << "	bsd_dom2_rls_reg = "	<< data.bsd_dom2_rls_reg << endl;
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
	cout << "	mode_reg = "			<< data.mode_reg		<< endl;
	cout << "	config_reg = "		<< data.config_reg	<< endl;
	cout << "	current_load_reg = "			<< data.current_load_reg		<< endl;
	cout << "	select_reg = "			<< data.select_reg			<< endl;
	cout << "	refresh_reg = "	<< data.refresh_reg << endl;
	cout << "	latency_reg = "			<< data.latency_reg		<< endl;
	cout << "	error_reg = "	<< data.error_reg << endl;
	cout << "	werror_reg = "	<< data.werror_reg << endl;
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
	cout << "	dram_addr_reg = "			<< data.dram_addr_reg		<< endl;
	cout << "	pif_addr_rd64b_reg = "		<< data.pif_addr_rd64b_reg	<< endl;
	cout << "	reserved = "			<< data.reserved		<< endl;
	cout << "	reserved2 = "			<< data.reserved2			<< endl;
	cout << "	pif_addr_wr64b_reg = "	<< data.pif_addr_wr64b_reg << endl;
	cout << "	reserved3 = "			<< data.reserved3		<< endl;
	cout << "	status_reg = "	<< data.status_reg << endl;
	cout << "*** END OF SI REGISTERS ***"<< endl;
}