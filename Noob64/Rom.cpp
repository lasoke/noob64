#include "StdAfx.h"

ROM::ROM(string filename)
{
	file.open(filename, ios::ate | ios::in | ios::binary);
	if (!file.is_open())
	{
		// TODO: error
		return;
	}
	int size = (int) file.tellg();
	data = (char*) malloc(size);
	file.seekg (0, ios::beg);
    file.read(data, size);
	file.close();
	ptr = data;
	header = (ROM_HEADER*) data;
}

ROM::~ROM()
{
	delete[] data;
}

word ROM::getClock()
{
	return header->clock;
}

word ROM::getPc()
{
	return header->pc;
}

word ROM::getRelease()
{
	return header->release;
}

word ROM::getCRC1()
{
	return header->crc1;
}

word ROM::getCRC2()
{
	return header->crc2;
}

string ROM::getName()
{
	string s = "";
	for(int i = 0; i < sizeof(header->name); i++)
		s += header->name[i];
	return s;
}

word ROM::getManufacturer()
{
	return header->manufacturer;
}

hword ROM::getCartridge()
{
	return header->cartridge;
}

hword ROM::getCountry()
{
	return header->country;
}

void ROM::dump(void) const
{
	cout << "*** ROM ***"				<< endl;
	cout << "name = ";
	for(int i = 0; i < sizeof(header->name); i++)
	{
		cout << header->name[i];
	}
	cout << endl;
	cout << "*** END OF ROM ***"		<< endl;
}


