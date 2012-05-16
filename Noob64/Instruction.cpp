#include "StdAfx.h"

Instruction::Instruction(word w) : instr(w)
{
}

void Instruction::operator=(const word &w)
{
	instr = w;
}

bool Instruction::operator==(const word &w) const
{
	return instr == w;
}

word Instruction::getInstr(void)
{
	return instr;
}

int Instruction::getOpCode(void)
{
	return (instr & 0xfc000000) >> 26;
}

int InstrR::getRs(void)
{
	return (instr & 0x3e00000) >> 21;
}

int InstrR::getRt(void)
{
	return (instr & 0x1F0000) >> 16;
}

int InstrR::getRd(void)
{
	return (instr & 0xF800) >> 11;
}

int InstrR::getSa(void)
{
	return (instr & 0x7C0) >> 6;
}

int InstrR::getFunc(void)
{
	return instr & 0x3F;
}

int InstrI::getRs(void)
{
	return (instr & 0x3e00000) >> 21;
}

int InstrI::getRt(void)
{
	return (instr & 0x1f0000) >> 16;
}

int InstrI::getImmed(void)
{
	return instr & 0xffff;
}

int InstrJ::getAdress(void)
{
	return instr & 0x3ffffff;
}

int InstrC::getFormat(void)
{
	return (instr & 0x3e00000) >> 21;
}

int InstrC::getFt(void)
{
	return (instr & 0x1F0000) >> 16;
}

int InstrC::getFs(void)
{
	return (instr & 0xF800) >> 11;
}

int InstrC::getFd(void)
{
	return (instr & 0x7C0) >> 6;
}

int InstrC::getFunc(void)
{
	return instr & 0x3F;
}