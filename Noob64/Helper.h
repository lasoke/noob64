#pragma once

//format a number
string format_number(string s, char c, int frequency);

//returns the word contained at the address pointed by ptr
word getWord(char **ptr);

inline dword extend_sign_word(dword d)
{
	if (d & 0x0000000080000000LL)
		return d |= 0xFFFFFFFF00000000LL;
	return d &= 0xFFFFFFFF;
}

inline dword extend_sign_halfword(dword d)
{
	if (d & 0x80)
		return d |= 0xFFFFFFFFFFFFFF00LL;
	return d &= 0xFF;
}

inline dword extend_sign_byte(dword d)
{
	if (d & 0x8000)
		return d |= 0xFFFFFFFFFFFF0000LL;
	return d &= 0xFFFF;
}