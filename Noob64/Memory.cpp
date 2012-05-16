#include "StdAfx.h"

RDRAM::RDRAM() :
	config_reg(0),
	device_id_reg(0),
	delay_reg(0),
	mode_reg(0),
	ref_interval_reg(0),
	ref_row_reg(0),
	ras_interval_reg(0),
	min_interval_reg(0),
	addr_select_reg(0),
	device_manuf_reg(0)
{
	for (int i = 0; i < size; i++)
		rdram[i] = 0;
}

void RDRAM::debug(void)
{
	debug(true, 0, 0);
}

void RDRAM::debug(bool registers, word start, word end)
{
	cout << "*** [" << typeid(this).name() << "] DEBUGING ***" << endl;
	cout << endl;
	if (registers)
	{
		cout << "	config_reg = "			<< config_reg		<< endl;
		cout << "	device_id_reg = "		<< device_id_reg	<< endl;
		cout << "	delay_reg = "			<< delay_reg		<< endl;
		cout << "	mode_reg = "			<< mode_reg			<< endl;
		cout << "	ref_interval_reg = "	<< ref_interval_reg << endl;
		cout << "	ref_row_reg = "			<< ref_row_reg		<< endl;
		cout << "	ras_interval_reg = "	<< ras_interval_reg << endl;
		cout << "	min_interval_reg = "	<< min_interval_reg << endl;
		cout << "	addr_select_reg = "		<< addr_select_reg	<< endl;
		cout << "	device_manuf_reg = "	<< device_manuf_reg << endl;
		cout << endl;
	}
	for (int i = start; i < end; i += sizeof(word))
		read<word>(i);
	cout << endl;
	cout << "*** END OF [" << typeid(this).name() << "] DEBUGING ***"<< endl;
}

