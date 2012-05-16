#pragma once
#include "Memory.h"

class Instruction
{
public:
	Instruction(word w);
	void operator=(const word &w);
	bool operator==(const word &w) const;
	word getInstr(void);
	int getOpCode(void);
protected:
	word instr;
};

class InstrR : Instruction
{
public:
	int getRs(void);
	int getRt(void);
	int getRd(void);
	int getSa(void);
	int getFunc(void);
private:

};

class InstrI : Instruction
{
public:
	int getRs(void);
	int getRt(void);
	int getImmed(void);
private:

};

class InstrJ : Instruction
{
public:
	int getAdress(void);
private:

};

class InstrC : Instruction
{
public:
	int getFormat(void);
	int getFt(void);
	int getFs(void);
	int getFd(void);
	int getFunc(void);
private:

};
