#include "StdAfx.h"

inline void decode_r(InstrR &instr)
{
}

inline void decode_i(InstrI &instr)
{
}

inline void decode_j(InstrJ &instr)
{
}

void decode(const word instr)
{
	Instruction* i = new Instruction(instr);
	switch(i->getOpCode()) {
	case 0:
		decode_r((InstrR&) i);
		break;
	//case ?:
	//	decode_i((InstrI&) i);
	//	break;
	//case ?:
	//	decode_j((InstrJ&) i);
	//	break;
	default: /* Unknown instruction */
		char mem[64];
		itoa(instr, mem, 2);
		cerr << "	Unknown instruction: " << format_number(string(32 - strlen(mem), '0') + mem, ' ', 4) << endl;
		exit(0);
	}
}