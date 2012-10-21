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

#include "StdAfx.h"

string format_number(string s, char c, int frequency)
{
	int length = s.length();
	string::iterator i = s.end();
	while (length - frequency > 0)
	{
		i -= frequency;
		length -= frequency;
		s.insert(i, c);
	}
	return s;
}

string print_addr(word address)
{
	char addr[16];
	memset(addr, 0, 16);
	_itoa_s(address, addr, 16, 16);
	return "\n" + format_number(string(8 - strlen(addr), '0') + addr, ' ', 4) + " : ";
}

byte getByte(char **ptr)
{
	word value = 0;
	char ch = **ptr;

    while (ch == ' ' || ch == '\t' || ch == '\n')
        ch = *(++*ptr);

    for (int i = 0; i < 2; i++)
	{
        if (ch >= '0' && ch <= '9')
            value = (value << 4) + (ch - '0');
        else if (ch >= 'A' && ch <= 'F')
            value = (value << 4) + (ch - 'A' + 10);
        else if (ch >= 'a' && ch <= 'f')
            value = (value << 4) + (ch - 'a' + 10);
        else
            return value;
        ch = *(++*ptr);
    }
	return value;
}

void dump_array(word start_addr, const byte *data, unsigned int size, int type)
{
	word line = 0;
	for (unsigned int i = 0; i < size; i += (sizeof(word) * 4))
	{
		// print address
		char addr[8];
		_itoa_s(start_addr + i, addr, 16);
		cout << format_number(string(8 - strlen(addr), '0') + addr, ' ', 2) << " : ";
		// print data
		for (unsigned int j = 0; j < 4; ++j)
		{
			line = binary_to_type<word>(data + i + j * 4);
			char mem[32];
			_itoa_s(line, mem, type);
			cout << format_number(string(sizeof(word) * 2 - strlen(mem), '0') + mem, ' ', 8) << " ";
		}
		cout << endl;
	}
}