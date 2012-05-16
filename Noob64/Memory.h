typedef unsigned __int8		byte;
typedef unsigned __int16	hword;
typedef unsigned __int32	word;
typedef unsigned __int64	dword;

#include <iostream>
#include <string>
#include <sstream>

class RDRAM
{
public:
	RDRAM();
	~RDRAM();

	static const int size = 256;

	template <typename Type>
	Type read(word address);

	template <typename Type>
	void write(Type data, word address);

	template <typename Type>
	void print_word(word address);

	word config_reg;
	word device_id_reg;
	word delay_reg;
	word mode_reg;
	word ref_interval_reg;
	word ref_row_reg;
	word ras_interval_reg;
	word min_interval_reg;
	word addr_select_reg;
	word device_manuf_reg;

	void debug(void);
	void debug(bool registers, word start, word end);

private:
	byte rdram[size];
};

template <typename Type>
inline void RDRAM::print_word(word address)
{
	int remainder;
	if (remainder = address % 4)
	{
		read<word>(address - remainder);
		if (sizeof(Type) > (4 - remainder))
		{
			read<word>(address + (4 - remainder));
		}
	}
	else
	{
		read<word>(address);
	}
}

template <typename Type>
inline Type RDRAM::read(word address)
{
	Type data = *((Type *)(rdram + address));
	if (DEBUG)
	{
		char buffer1[8];
		itoa(address, buffer1, 16);
		cout << "	" << format_number(string(8 - strlen(buffer1), '0') + buffer1, ' ', 2) << " : ";
		char buffer2[64];
		itoa(data, buffer2, 2);
		cout << format_number(string(sizeof(Type) * 8 - strlen(buffer2), '0') + buffer2, ' ', 4) << endl;
	}
	return data;
}

template <typename Type>
inline void RDRAM::write(Type data, word address)
{
	*((Type *)(rdram + address)) = data;
	if (DEBUG)
	{
		cout << "	*WRITING* " << data << " @ " << address << ":" << endl;
		print_word<Type>(address);
		cout << endl;
	}
}

/*
  00000000-03EFFFFF   RDRAM Memory
  03F00000-03FFFFFF   RDRAM Registers
  04000000-040FFFFF   SP Registers
  04100000-041FFFFF   DP Command Registers
  04200000-042FFFFF   DP Span Registers
  04300000-043FFFFF   MIPS Interface (MI) Registers
  04400000-044FFFFF   Video Interface (VI) Registers
  04500000-045FFFFF   Audio Interface (AI) Registers
  04600000-046FFFFF   Peripheral Interface (PI) Registers
  04700000-047FFFFF   RDRAM Interface (RI) Registers
  04800000-048FFFFF   Serial Interface (SI) Registers
  04900000-04FFFFFF   Unused
  05000000-05FFFFFF   Cartridge Domain 2 Address 1
  06000000-07FFFFFF   Cartridge Domain 1 Address 1
  08000000-0FFFFFFF   Cartridge Domain 2 Address 2
  10000000-1FBFFFFF   Cartridge Domain 1 Address 2
  1FC00000-1FC007BF   PIF Boot ROM
  1FC007C0-1FC007FF   PIF RAM
  1FC00800-1FCFFFFF   Reserved
  1FD00000-7FFFFFFF   Cartridge Domain 1 Address 3
  80000000-FFFFFFFF   External SysAD Device
  */