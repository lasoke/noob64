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

inline int getFunct(word instr)
{
	return instr & 0x3F;
}

inline int getImmediate(word instr)
{
	return instr & 0xffff;
}

inline int getTarget(word instr)
{
	return instr & 0x3ffffff;
}

inline int getCond(word instr)
{
	return instr & 0xF;
}

inline int getNd(word instr)
{
	return (instr & 0x20000) >> 17;
}

inline int getTf(word instr)
{
	return (instr & 0x10000) >> 16;
}

inline int getNdTf(word instr)
{
	return (instr & 0x30000) >> 16;
}


