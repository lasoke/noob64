#pragma once

#define BOOT_CODE_SIZE 1008

class RomLoader
{
public:
	RomLoader(void);
	RomLoader(char* filename);
	word getInstruction(int i);
private:
	byte		PI_BSB_DOM1_LAT_REG;
	byte		PI_BSB_DOM1_PGS_REG;
	byte		PI_BSB_DOM1_PWD_REG;
	byte		PI_BSB_DOM1_PGS_2_REG;
	word		clock;
	word		pc;
	word		release;
	word		CRC1;
	word		CRC2;
	char		name[20];
	word		manufacturer;
	hword		cartridge;
	hword		country;
	word		bootcode[BOOT_CODE_SIZE];
};

