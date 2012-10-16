#pragma once

// Format a number
string format_number(string s, char c, int frequency);

// Prints an address in the standard representation
string print_addr(dword address);

// Returns the word contained at the address pointed by ptr
byte getByte(char **ptr);

//print the memory contains in the array data
void dump_array(word start_addr, const byte *data, unsigned int size, int type);

//****************************************************************************
//** CONVERTS A BYTE ARRAY TO ITS Type REPRESENTATION						**
//****************************************************************************
template <typename Type>
inline Type binary_to_type(const byte *address)
{
	Type result = 0;
	for (unsigned int i = 0; i < sizeof(result); i++)
		result = (result << 8) + address[i];
	return result;
}

//****************************************************************************
//** CONVERTS A Type TO ITS BINARY REPRESENTATION							**
//****************************************************************************
template <typename Type>
inline Type type_to_binary(Type data)
{
	byte *tab = (byte*) &data;
	byte b;
	unsigned size = sizeof(data);
	for (unsigned int i = 0; i < size / 2; i++)
	{
		b = tab[i];
		tab[i] = tab[size-1-i];
		tab[size-1-i] = b;
	}
	return data;
}