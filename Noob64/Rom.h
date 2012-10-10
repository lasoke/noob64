#pragma once

#define HEADER_SIZE		0xFFF
#define BOOT_CODE_SIZE	1008

class ROM : public MEM_SEG
{
public:
	ROM(void);
	ROM(char* filename);
	static const word begining = 0xB0000000;
	static const word end /* TODO */ = 0x0;
	void dump(void) const;

	word getClock();
	word getPc();
	word getRelease();
	word getCRC1();
	word getCRC2();
	string getName();
	word getManufacturer();
	hword getCartridge();
	hword getCountry();

private:
	struct { // ROM Header
	   byte		PI_BSB_DOM1_LAT_REG;
	   byte		PI_BSB_DOM1_PGS_REG;
	   byte		PI_BSB_DOM1_PWD_REG;
	   byte		PI_BSB_DOM1_PGS_2_REG;
	   word		clock;
	   word		pc;
	   word		release;
	   word		CRC1;
	   word		CRC2;
	   word		Unknown[2];
	   byte		name[20];
	   word		unknown;
	   word		manufacturer;
	   hword	cartridge;
	   hword	country;
	   word		bootcode[BOOT_CODE_SIZE];
	} header;
};

