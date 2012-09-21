#pragma once

//getOpCode retreives the Op code from an instruction
inline int getOpCode(word instr)
{
	return (instr & 0xfc000000) >> 26;
}

//getRs retreives the source register from an instruction
inline int getRs(word instr)
{
	return (instr & 0x3e00000) >> 21;
}

//getRt retreives the target register from an instruction
inline int getRt(word instr)
{
	return (instr & 0x1F0000) >> 16;
}

//getRd retreives the destination register from an instruction
inline int getRd(word instr)
{
	return (instr & 0xF800) >> 11;
}

//getSa retreives the shift amount from an instruction
inline int getSa(word instr)
{
	return (instr & 0x7C0) >> 6;
}

//getFunct retreives the function from the instruction
inline int getFunct(word instr)
{
	return instr & 0x3F;
}

//getImmediate retreives the immediate from the instruction
inline int getImmediate(word instr)
{
	return instr & 0xffff;
}

//getTarget retreives the jump target address from the instruction
inline int getTarget(word instr)
{
	return instr & 0x3ffffff;
}

//getCond retreives the jump condition from the instruction
inline int getCond(word instr)
{
	return instr & 0xF;
}

//getNd retreives the nd from the instruction useful for the bc instruction
inline int getNd(word instr)
{
	return (instr & 0x20000) >> 17;
}

//getTf retreives the tf from the instruction useful for the bc instruction
inline int getTf(word instr)
{
	return (instr & 0x10000) >> 16;
}

//getNdTf retreives the nd and tf from the instruction useful for the bc instruction
inline int getNdTf(word instr)
{
	return (instr & 0x30000) >> 16;
}


