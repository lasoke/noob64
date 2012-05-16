#pragma once
#include "Memory.h"

inline int getOpCode(word instr)
{
	return (instr & 0xfc000000) >> 26;
}

inline int getRs(word instr)
{
	return (instr & 0x3e00000) >> 21;
}

inline int getRt(word instr)
{
	return (instr & 0x1F0000) >> 16;
}

inline int getRd(word instr)
{
	return (instr & 0xF800) >> 11;
}

inline int getSa(word instr)
{
	return (instr & 0x7C0) >> 6;
}

inline int getFunc(word instr)
{
	return instr & 0x3F;
}

inline int getImmed(word instr)
{
	return instr & 0xffff;
}

inline int getAdress(word instr)
{
	return instr & 0x3ffffff;
}

inline int getFormat(word instr)
{
	return (instr & 0x3e00000) >> 21;
}

inline int getFt(word instr)
{
	return (instr & 0x1F0000) >> 16;
}

inline int getFs(word instr)
{
	return (instr & 0xF800) >> 11;
}

inline int getFd(word instr)
{
	return (instr & 0x7C0) >> 6;
}
