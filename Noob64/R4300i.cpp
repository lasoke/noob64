#include "StdAfx.h"

R4300i::R4300i(RomLoader &rdrom, RDRAM &rdram) : rom(rdrom), ram(rdram) , ehandler(*new ExceptionHandler())
{
	for (int i = 0; i < 32; i++)
		r[i] = (dword) 0;
}

void R4300i::decode(const word i)
{
	switch(getOpCode(i)) {
	case 0:
		decode_r(i);
		break;
	case 1:
		decode_i(i);
		break;
	case 2:
		J(getTarget(i));
		break;
	case 3:
		JAL(getTarget(i));
		break;
	case 4:
		BEQ(getRs(i), getRt(i), getImmediate(i));
		break;
	case 5:
		BNE(getRs(i), getRt(i), getImmediate(i));
		break;
	case 6:
		BLEZ(getRs(i), getImmediate(i));
		break;
	case 7:
		BGTZ(getRs(i), getImmediate(i));
		break;
	case 8:
		ADDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 9:
		ADDIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 10:
		SLTI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 11:
		SLTIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 12:
		ANDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 13:
		ORI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 14:
		XORI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 15:
		LUI(getRt(i), getImmediate(i));
		break;
	case 16:
		decode_cop0(i);
		break;
	case 17:
		decode_cop1(i);
		break;
	case 20:
		BEQL(getRs(i), getRt(i), getImmediate(i));
		break;
	case 21:
		BNEL(getRs(i), getRt(i), getImmediate(i));
		break;
	case 22:
		BLEZL(getImmediate(i), getRs(i));
		break;
	case 23:
		BGTZL(getImmediate(i), getRs(i));
		break;
	case 24:
		DADDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 25:
		DADDIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 26:
		LDL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 27:
		LDR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 32:
		LB(getRt(i), getImmediate(i), getRs(i));
		break;
	case 33:
		LH(getRt(i), getImmediate(i), getRs(i));
		break;
	case 34:
		LWL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 35:
		LW(getRt(i), getImmediate(i), getRs(i));
		break;
	case 36:
		LBU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 37:
		LHU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 38:
		LWR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 39:
		LWU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 40:
		SB(getRt(i), getImmediate(i), getRs(i));
		break;
	case 41:
		SH(getRt(i), getImmediate(i), getRs(i));
		break;
	case 42:
		SWL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 43:
		SW(getRt(i), getImmediate(i), getRs(i));
		break;
	case 44:
		SDL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 45:
		SDR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 46:
		SWR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 47:
		CACHE(getRt(i), getImmediate(i), getRs(i));
		break;
	case 48:
		LL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 49:
		LWC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 52:
		LLD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 53:
		LDC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 54:
		//TODO: LDC2
		break;
	case 55:
		LD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 56:
		SC(getRt(i), getImmediate(i), getRs(i));
		break;
	case 57:
		SWC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 60:
		SCD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 61:
		SDC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 62:
		//TODO: SDC2
		break;
	case 63:
		SD(getRt(i), getImmediate(i), getRs(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_r(word i)
{
	switch(getFunct(i)) {
	case 0:
		SLL(getRd(i), getRt(i), getSa(i));
		break;
	case 2:
		SRL(getRd(i), getRt(i), getSa(i));
		break;
	case 3:
		SRA(getRd(i), getRt(i), getSa(i));
		break;
	case 4:
		SLLV(getRd(i), getRt(i), getRs(i));
		break;
	case 6:
		SRLV(getRd(i), getRt(i), getRs(i));
		break;
	case 7:
		SRAV(getRd(i), getRt(i), getRs(i));
		break;
	case 8:
		JR(getRs(i));
		break;
	case 9:
		JALR(getRs(i), getRd(i));
		break;
	case 12:
		SYSCALL(getImmediate(i));
		break;
	case 13:
		BREAK(getImmediate(i));
		break;
	case 15:
		SYNC();
		break;
	case 16:
		MFHI(getRd(i));
		break;
	case 17:
		MTHI(getRs(i));
		break;
	case 18:
		MFLO(getRd(i));
		break;
	case 19:
		MTLO(getRs(i));
		break;
	case 20:
		DSLLV(getRd(i), getRt(i), getRs(i));
		break;
	case 22:
		DSRLV(getRd(i), getRt(i), getRs(i));
		break;
	case 23:
		DSRAV(getRd(i), getRt(i), getRs(i));
		break;
	case 24:
		MULT(getRs(i), getRt(i));
		break;
	case 25:
		MULTU(getRs(i), getRt(i));
		break;
	case 26:
		DIV(getRs(i), getRt(i));
		break;
	case 27:
		DIVU(getRs(i), getRt(i));
		break;
	case 28:
		DMULT(getRs(i), getRt(i));
		break;
	case 29:
		DMULTU(getRs(i), getRt(i));
		break;
	case 30:
		DDIV(getRs(i), getRt(i));
		break;
	case 31:
		DDIVU(getRs(i), getRt(i));
		break;
	case 32:
		ADD(getRd(i), getRs(i), getRt(i));
		break;
	case 33:
		ADDU(getRd(i), getRs(i), getRt(i));
		break;
	case 34:
		SUB(getRd(i), getRs(i), getRt(i));
		break;
	case 35:
		SUBU(getRd(i), getRs(i), getRt(i));
		break;
	case 36:
		AND(getRd(i), getRs(i), getRt(i));
		break;
	case 37:
		OR(getRd(i), getRs(i), getRt(i));
		break;
	case 38:
		XOR(getRd(i), getRs(i), getRt(i));
		break;
	case 39:
		NOR(getRd(i), getRs(i), getRt(i));
		break;
	case 42:
		SLT(getRd(i), getRs(i), getRt(i));
		break;
	case 43:
		SLTU(getRd(i), getRs(i), getRt(i));
		break;
	case 44:
		DADD(getRd(i), getRs(i), getRt(i));
		break;
	case 45:
		DADDU(getRd(i), getRs(i), getRt(i));
		break;
	case 46:
		DSUB(getRd(i), getRs(i), getRt(i));
		break;
	case 47:
		DSUBU(getRd(i), getRs(i), getRt(i));
		break;
	case 48:
		TGE(getRs(i), getRt(i));
		break;
	case 49:
		TGEU(getRs(i), getRt(i));
		break;
	case 50:
		TLT(getRs(i), getRt(i));
		break;
	case 51:
		TLTU(getRs(i), getRt(i));
		break;
	case 52:
		TEQ(getRs(i), getRt(i));
		break;
	case 54:
		TNE(getRs(i), getRt(i));
		break;
	case 56:
		DSLL(getRd(i), getRt(i), getSa(i));
		break;
	case 58:
		DSRL(getRd(i), getRt(i), getSa(i));
		break;
	case 59:
		DSRA(getRd(i), getRt(i), getSa(i));
		break;
	case 60:
		DSLL32(getRd(i), getRt(i), getSa(i));
		break;
	case 62:
		DSRL32(getRd(i), getRt(i), getSa(i));
		break;
	case 63:
		DSRA32(getRd(i), getRt(i), getSa(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_i(word i)
{
	switch(getRt(i)) {
	case 0:
		BLTZ(getImmediate(i), getRs(i));
		break;
	case 1:
		BGEZ(getImmediate(i), getRs(i));
		break;
	case 2:
		BLTZL(getImmediate(i), getRs(i));
		break;
	case 3:
		BGEZL(getImmediate(i), getRs(i));
		break;
	case 8:
		TGEI(getRs(i), getImmediate(i));
		break;
	case 9:
		TGEIU(getRs(i), getImmediate(i));
		break;
	case 10:
		TLTI(getRs(i), getImmediate(i));
		break;
	case 11:
		TLTIU(getRs(i), getImmediate(i));
		break;
	case 12:
		TEQI(getRs(i), getImmediate(i));
		break;
	case 14:
		TNEI(getRs(i), getImmediate(i));
		break;
	case 16:
		BLTZAL(getImmediate(i), getRs(i));
		break;
	case 17:
		BGEZAL(getImmediate(i), getRs(i));
		break;
	case 18:
		BLTZALL(getImmediate(i), getRs(i));
		break;
	case 19:
		BGEZALL(getImmediate(i), getRs(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_cop0(word i)
{
	switch(getRs(i)) {
	case 0:
		MFC0(getRt(i), getRd(i));
		break;
	case 4:
		MTC0(getRt(i), getRd(i));
		break;
	case 16:
		decode_tlb(i);
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_tlb(word i)
{
	switch(getFunct(i)) {
	case 1:
		TLBR();
		break;
	case 2:
		TLBWI();
		break;
	case 6:
		TLBWR();
		break;
	case 8:
		TLBP();
		break;
	case 24:
		ERET();
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_cop1(const word i)
{
	switch(getRs(i)) {
	case 0:
		MFC1(getRt(i), getRd(i));
		break;
	case 1:
		DMFC1(getRt(i), getRd(i));
		break;
	case 2:
		CFC1(getRt(i), getRd(i));
		break;
	case 4:
		MTC1(getRt(i), getRd(i));
		break;
	case 5:
		DMTC1(getRt(i), getRd(i));
		break;
	case 6:
		CTC1(getRt(i), getRd(i));
		break;
	case 8:
		decode_bc1(i);
		break;
	case 16:
		decode_fpu<s>(i);
		break;
	case 17:
		decode_fpu<d>(i);
		break;
	case 20:
		decode_fpu<w>(i);
		break;
	case 21:
		decode_fpu<l>(i);
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_bc1(const word i)
{
	switch(getNdTf(i)) {
	case 0:
		BC1F(getImmediate(i));
		break;
	case 1:
		BC1T(getImmediate(i));
		break;
	case 2:
		BC1FL(getImmediate(i));
		break;
	case 3:
		BC1TL(getImmediate(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

template<typename Type>
inline void R4300i::decode_fpu(const word i)
{
	switch(getFunct(i)) {
	case 0:
		ADD<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 1:
		SUB<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 2:
		MUL<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 3:
		DIV<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 4:
		SQRT<Type>(getSa(i), getRd(i));
		break;
	case 5:
		ABS<Type>(getSa(i), getRd(i));
		break;
	case 6:
		MOV<Type>(getSa(i), getRd(i));
		break;
	case 7:
		NEG<Type>(getSa(i), getRd(i));
		break;
	case 8:
		ROUND<Type, l>(getSa(i), getRd(i));
		break;
	case 9:
		TRUNC<Type, l>(getSa(i), getRd(i));
		break;
	case 10:
		CEIL<Type, l>(getSa(i), getRd(i));
		break;
	case 11:
		FLOOR<Type, l>(getSa(i), getRd(i));
		break;
	case 12:
		ROUND<Type, w>(getSa(i), getRd(i));
		break;
	case 13:
		TRUNC<Type, w>(getSa(i), getRd(i));
		break;
	case 14:
		CEIL<Type, w>(getSa(i), getRd(i));
		break;
	case 15:
		FLOOR<Type, w>(getSa(i), getRd(i));
		break;
	case 32:
		CVT<Type, s>(getSa(i), getRd(i));
		break;
	case 33:
		CVT<Type, d>(getSa(i), getRd(i));
		break;
	case 36:
		CVT<Type, w>(getSa(i), getRd(i));
		break;
	case 37:
		CVT<Type, l>(getSa(i), getRd(i));
		break;
	case 48:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 49:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 50:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 51:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 52:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 53:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 54:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 55:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 56:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 57:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 58:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 59:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 60:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 61:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 62:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 63:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

void R4300i::LB(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LB " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<sbyte>(r[rs] + immed * sizeof(sbyte));
	++pc;
}

void R4300i::LBU(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LBU " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<byte>(r[rs] + immed * sizeof(byte));
	++pc;
}

void R4300i::LD(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LD " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<dword>(r[rs] + immed * sizeof(dword));
	++pc;
}

void R4300i::LDL(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LDL " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	dword tmp = ram.read<dword>(r[rs] + immed * sizeof(dword));
	r[rt] |= (tmp << ((r[rs] + immed * sizeof(dword)) & 7) * 8);
	++pc;
}

void R4300i::LDR(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LDR " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	dword tmp = ram.read<dword>(r[rs] + immed * sizeof(dword));
	r[rt] |= (tmp >> (( 7 - (r[rs] + immed * sizeof(dword)) & 7)) * 8);
	++pc;
}

void R4300i::LH(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LH " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<shword>(r[rs] + immed * sizeof(shword));
	++pc;
}

void R4300i::LHU(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LHU " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<hword>(r[rs] + immed * sizeof(hword));
	++pc;
}

void R4300i::LL(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LL " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = (sdword) ram.read<sword>(r[rs] + immed * sizeof(sword));
	ll = 1;
	++pc;
}

void R4300i::LLD(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LLD " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<sdword>(r[rs] + immed * sizeof(sdword));
	ll = 1;
	++pc;
}

void R4300i::LW(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LW " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<sword>(r[rs] + immed * sizeof(sword));
	++pc;
}

void R4300i::LWL(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LWL " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	word tmp = ram.read<word>(r[rs] + immed * sizeof(word));
	r[rt] |= (tmp << (3 - (r[rs] + immed * sizeof(word)) & 3) * 8);
	++pc;
}

void R4300i::LWR(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LWR " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	word tmp = ram.read<word>(r[rs] + immed * sizeof(word));
	r[rt] |= (tmp >> ((3 - (r[rs] + immed * sizeof(word)) & 3)) * 8);
	++pc;
}

void R4300i::LWU(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "LWU " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = ram.read<word>(r[rs] + immed * sizeof(word));
	++pc;
}

void R4300i::SB(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "SB " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	ram.write<byte>(r[rt] & 0xFF, r[rs] + immed * sizeof(byte));
	++pc;
}

void R4300i::SC(int rt, int immed, int rs)
{
	// TODO: TEST
	if (ll)
	{
#if defined DEBUG
		cout << "SC " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
		ram.write<word>(r[rt] & 0xFFFFFFFF, r[rs] + immed * sizeof(word));
		//maybe something to do here...
		ll = 0;
	}
	else
	{
#if defined DEBUG
		cout << "SC " << rt << " " << immed << "[" << rs << "]  no ll was done before";
#endif // DEBUG
	}
	++pc;
}

void R4300i::SCD(int rt, int immed, int rs)
{
	// TODO: TEST
	if (ll)
	{
#if defined DEBUG
		cout << "SCD " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
		ram.write<dword>(r[rt] & 0xFFFFFFFF, r[rs] + immed * sizeof(dword));
		//maybe something to do here...
		ll = 0;
	}
	else
	{
#if defined DEBUG
		cout << "SCD " << rt << " " << immed << "[" << rs << "]  no ll was done before";
#endif // DEBUG
	}
	++pc;
}

void R4300i::SD(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "SD " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	ram.write<dword>(r[rt], r[rs] + immed * sizeof(dword));
	++pc;
}

void R4300i::SDL(int rt, int immed, int rs)
{
	// TODO: TEST
   dword old_word = 0;
#if defined DEBUG
		cout << "SDL " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	old_word = ram.read<dword>(r[rs] + immed * sizeof(dword));
	old_word = (r[rt] >> (8 * (r[rs] + immed * sizeof(dword)) & 7)) | old_word;
	ram.write<dword>(old_word, r[rs] + immed * sizeof(dword));
	++pc;
}

void R4300i::SDR(int rt, int immed, int rs)
{
	// TODO: TEST
   dword old_word = 0;
#if defined DEBUG
		cout << "SDR " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	old_word = ram.read<dword>(r[rs] + immed * sizeof(dword));
	old_word = (r[rt] << (8 * (7 - (r[rs] + immed * sizeof(dword)) & 7))) | old_word;
	ram.write<dword>(old_word, r[rs] + immed * sizeof(dword));
	++pc;
}

void R4300i::SH(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "SH " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	ram.write<hword>(r[rt] & 0xFFFF, r[rs] + immed * sizeof(hword));
	++pc;
}

void R4300i::SW(int rt, int immed, int rs)
{
	// TODO: TEST
#if defined DEBUG
		cout << "SW " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	ram.write<word>(r[rt] & 0xFFFFFFFF, r[rs] + immed * sizeof(word));
	++pc;
}

void R4300i::SWL(int rt, int immed, int rs)
{
	// TODO: TEST
   word old_word = 0;
#if defined DEBUG
		cout << "SWL " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	old_word = ram.read<word>(r[rs] + immed * sizeof(word));
	old_word = (word) (r[rt] >> (8 * (r[rs] + immed * sizeof(word)) & 3)) | old_word;
	ram.write<word>(old_word, r[rs] + immed * sizeof(word));
	++pc;
}

void R4300i::SWR(int rt, int immed, int rs)
{
	// TODO: TEST
   word old_word = 0;
#if defined DEBUG
		cout << "SWR " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	old_word = ram.read<word>(r[rs] + immed * sizeof(word));
	old_word = (word) (r[rt] << (8 * (3 - (r[rs] + immed * sizeof(word)) & 3))) | old_word;
	ram.write<word>(old_word, r[rs] + immed * sizeof(word));
	++pc;
}

void R4300i::SYNC(void)
{
	// TODO: TEST
#if defined DEBUG
		cout << "SYNC TO DO MAYBE";
#endif // DEBUG
	++pc;
}

void R4300i::ADD(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "ADD " << rd << ", " << rs << " " << rt;
#endif // DEBUG
	if (WORD_MAX - r[rt] < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rd] = (sdword) ((sword) r[rs] + (sword) r[rt]);
	}
	++pc;
}

void R4300i::ADDI(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "ADDI " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	if (WORD_MAX - immed < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rt] = (sdword) ((sword) r[rs] + immed);
	}
	++pc;
}

void R4300i::ADDIU(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "ADDIU " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	if (WORD_MAX - immed < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rt] = (word) r[rs] + immed;
	}
	++pc;
}

void R4300i::ADDU(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "ADDU " << rd << ", " << rs << " " << rt;
#endif // DEBUG
	if (WORD_MAX - (word) r[rt] < (word) r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rd] = (word) r[rs] + (word) r[rt];
	}
	++pc;
}

void R4300i::AND(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "AND " << rd << ", " << rs << " " << rt;
#endif // DEBUG
	r[rd] = r[rs] & r[rt];
	++pc;
}

void R4300i::ANDI(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "ANDI " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	r[rt] = r[rs] & immed;
	++pc;
}

void R4300i::DADD(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "DADD " << rd << ", " << rs << " " << rt;
#endif // DEBUG
	if (DWORD_MAX - r[rt] < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rd] = (sdword) ((sdword) r[rs] + (sdword) r[rt]);
	}
	++pc;
}

void R4300i::DADDI(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "DADDI " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	if (DWORD_MAX - immed < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rt] = (sdword) ((sdword) r[rs] + immed);
	}
	++pc;
}

void R4300i::DADDIU(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "DADDIU " << rt << " " << immed << "[" << rs << "]";
#endif // DEBUG
	if (DWORD_MAX - immed < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rt] = r[rs] + immed;
	}
	++pc;
}

void R4300i::DADDU(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "DADDU " << rd << ", " << rs << " " << rt;
#endif // DEBUG
	if (DWORD_MAX - r[rt] < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rd] = r[rs] + r[rt];
	}
	++pc;
}

void R4300i::DDIV(int rs, int rt)
{
#if defined DEBUG
		cout << "DDIV " << rs << ", " << rt;
#endif // DEBUG
	if (r[rt] == 0)
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		lo = (sdword) r[rs] / (sdword) r[rt];
		hi = (sdword) r[rs] % (sdword) r[rt];
	}
	++pc;
}

void R4300i::DDIVU(int rs, int rt)
{
#if defined DEBUG
		cout << "DDIVU " << rs << ", " << rt;
#endif // DEBUG
	if (r[rt] == 0)
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		lo = r[rs] / r[rt];
		hi = r[rs] % r[rt];
	}
	++pc;
}

void R4300i::DIV(int rs, int rt)
{
#if defined DEBUG
		cout << "DIV " << rs << ", " << rt;
#endif // DEBUG
	if (r[rt] == 0)
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		lo = (sword) r[rs] / (sword) r[rt];
		hi = (sword) r[rs] % (sword) r[rt];
	}
	++pc;
}

void R4300i::DIVU(int rs, int rt)
{
#if defined DEBUG
		cout << "DIVU " << rs << ", " << rt;
#endif // DEBUG
	if (r[rt] == 0)
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		lo = (word) r[rs] / (word) r[rt];
		hi = (word) r[rs] % (word) r[rt];
	}
	++pc;
}

void R4300i::DMULT(int rs, int rt)
{
#if defined DEBUG
		cout << "DMULT " << rs << ", " << rt;
#endif // DEBUG
	dword op1, op2, op3, op4;
    dword result1, result2, result3, result4;
    dword temp1, temp2, temp3, temp4;
    int sign = 0;
   
    if (r[rs] < 0)
    {
		op2 = - (sdword) r[rs];
		sign = 1 - sign;
    }
    else
		op2 = r[rs];
    if (r[rt] < 0)
    {
		op4 = - (sdword) r[rt];
		sign = 1 - sign;
    }
    else
		op4 = r[rt];
   
    op1 = op2 & 0xFFFFFFFF;
    op2 = (op2 >> 32) & 0xFFFFFFFF;
    op3 = op4 & 0xFFFFFFFF;
    op4 = (op4 >> 32) & 0xFFFFFFFF;
   
    temp1 = op1 * op3;
    temp2 = (temp1 >> 32) + op1 * op4;
    temp3 = op2 * op3;
    temp4 = (temp3 >> 32) + op2 * op4;
   
    result1 = temp1 & 0xFFFFFFFF;
    result2 = temp2 + (temp3 & 0xFFFFFFFF);
    result3 = (result2 >> 32) + temp4;
    result4 = (result3 >> 32);
   
    lo = result1 | (result2 << 32);
    hi = (result3 & 0xFFFFFFFF) | (result4 << 32);
    if (sign)
    {
		hi = ~hi;
		if (!lo)
			hi++;
		else
			lo = ~lo + 1;
    }
	++pc;
}

void R4300i::DMULTU(int rs, int rt)
{
#if defined DEBUG
		cout << "DMULTU " << rs << ", " << rt;
#endif // DEBUG
	dword op1, op2, op3, op4;
	dword result1, result2, result3, result4;
    dword temp1, temp2, temp3, temp4;
   
    op1 = r[rs] & 0xFFFFFFFF;
    op2 = (r[rs] >> 32) & 0xFFFFFFFF;
    op3 = r[rt] & 0xFFFFFFFF;
    op4 = (r[rt] >> 32) & 0xFFFFFFFF;
   
    temp1 = op1 * op3;
    temp2 = (temp1 >> 32) + op1 * op4;
    temp3 = op2 * op3;
    temp4 = (temp3 >> 32) + op2 * op4;
   
    result1 = temp1 & 0xFFFFFFFF;
    result2 = temp2 + (temp3 & 0xFFFFFFFF);
    result3 = (result2 >> 32) + temp4;
    result4 = (result3 >> 32);
   
    lo = result1 | (result2 << 32);
    hi = (result3 & 0xFFFFFFFF) | (result4 << 32);
	++pc;
}

void R4300i::DSLL(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "DSLL " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = r[rt] << sa;
	++pc;
}

void R4300i::DSLL32(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "DSLL32 " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = r[rt] << (sa + 32);
	++pc;
}

void R4300i::DSLLV(int rd, int rt, int rs)
{
#if defined DEBUG
		cout << "DSLLV " << rd << " " << rt << " " << rs;
#endif // DEBUG
	r[rd] = r[rt] << r[rs];
	++pc;
}

void R4300i::DSRA(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "DSRA " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = r[rt] >> sa;
	++pc;
}

void R4300i::DSRA32(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "DSRA32 " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = r[rt] >> (sa + 32);
	++pc;
}

void R4300i::DSRAV(int rd, int rt, int rs)
{
#if defined DEBUG
		cout << "DSRAV " << rd << " " << rt << " " << rs;
#endif // DEBUG
	r[rd] = r[rt] >> r[rs];
	++pc;
}

void R4300i::DSRL(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "DSRL " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = r[rt] >> sa;
	++pc;
}

void R4300i::DSRL32(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "DSRL32 " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = r[rt] >> (sa + 32);
	++pc;
}

void R4300i::DSRLV(int rd, int rt, int rs)
{
#if defined DEBUG
		cout << "DSRLV " << rd << " " << rt << " " << rs;
#endif // DEBUG
	r[rd] = r[rt] >> r[rs];
	++pc;
}

void R4300i::DSUB(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "DSUB " << rd << " " << rs << " " << rt;
#endif // DEBUG
	r[rd] = (sdword) r[rs] - (sdword) r[rt];
	++pc;
}

void R4300i::DSUBU(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "DSUBU " << rd << " " << rs << " " << rt;
#endif // DEBUG
	r[rd] = r[rs] - r[rt];
	++pc;
}

void R4300i::LUI(int rt, int immed)
{
#if defined DEBUG
		cout << "LUI " << rt << " " << immed;
#endif // DEBUG
	r[rt] = immed << 16;
	++pc;
}

void R4300i::MFHI(int rd)
{
#if defined DEBUG
		cout << "MFHI " << rd;
#endif // DEBUG
	r[rd] = hi;
	++pc;
}

void R4300i::MFLO(int rd)
{
#if defined DEBUG
		cout << "MFLO " << rd;
#endif // DEBUG
	r[rd] = lo;
	++pc;
}

void R4300i::MTHI(int rs)
{
#if defined DEBUG
		cout << "MTHI " << rs;
#endif // DEBUG
	hi = r[rs];
	++pc;
}

void R4300i::MTLO(int rs)
{
#if defined DEBUG
		cout << "MTLO " << rs;
#endif // DEBUG
	lo = r[rs];
	++pc;
}

void R4300i::MULT(int rs, int rt)
{
#if defined DEBUG
		cout << "MULT " << rs << ", " << rt;
#endif // DEBUG
	sdword temp = r[rs] * r[rt];
	hi = temp >> 32;
	lo = temp;
	++pc;
}

void R4300i::MULTU(int rs, int rt)
{
#if defined DEBUG
		cout << "DMULTU " << rs << ", " << rt;
#endif // DEBUG
	dword temp = r[rs] * r[rt];
	hi = temp >> 32;
	lo = temp;
	++pc;
}

void R4300i::NOR(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "NOR " << rd << " " << rs << " " << rt;
#endif // DEBUG
	r[rd] = ~(r[rs] | r[rt]);
	++pc;
}

void R4300i::OR(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "OR " << rd << " " << rs << " " << rt;
#endif // DEBUG
	r[rd] = r[rs] | r[rt];
	++pc;
}

void R4300i::ORI(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "ORI " << rt << " " << rs << " " << immed;
#endif // DEBUG
	r[rt] = r[rs] | (word) immed;
	++pc;
}

void R4300i::SLL(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "SLL " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = (word) r[rt] << sa;
	++pc;
}

void R4300i::SLLV(int rd, int rt, int rs)
{
#if defined DEBUG
		cout << "SLLV " << rd << " " << rt << " " << rs;
#endif // DEBUG
	r[rd] = (word) r[rt] << (r[rs]&0x1F);
	++pc;
}

void R4300i::SLT(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "SLT " << rd << " " << rs << " " << rt;
#endif // DEBUG
	if ((sword) r[rs] < (sword) r[rt])
		r[rd] = 1;
	else
		r[rd] = 0;
	++pc;
}

void R4300i::SLTI(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "SLTI " << rt << " " << rs << " " << immed;
#endif // DEBUG
	if ((sword) r[rs] < immed)
		r[rt] = 1;
	else
		r[rt] = 0;
	++pc;
}

void R4300i::SLTIU(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "SLTIU " << rt << " " << rs << " " << immed;
#endif // DEBUG
	if (r[rs] < immed)
		r[rt] = 1;
	else
		r[rt] = 0;
	++pc;
}

void R4300i::SLTU(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "SLTU " << rd << " " << rs << " " << rt;
#endif // DEBUG
	if (r[rs] < r[rt])
		r[rd] = 1;
	else
		r[rd] = 0;
	++pc;
}

void R4300i::SRA(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "SRA " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = (sword) r[rt] >> sa;
	++pc;
}

void R4300i::SRAV(int rd, int rt, int rs)
{
#if defined DEBUG
		cout << "SRAV " << rd << " " << rt << " " << rs;
#endif // DEBUG
	r[rd] = (sword) r[rt] >> (r[rs]&0x1F);
	++pc;
}

void R4300i::SRL(int rd, int rt, int sa)
{
#if defined DEBUG
		cout << "SRL " << rd << " " << rt << " " << sa;
#endif // DEBUG
	r[rd] = (word) r[rt] >> sa;
	++pc;
}

void R4300i::SRLV(int rd, int rt, int rs)
{
#if defined DEBUG
		cout << "SRLV " << rd << " " << rt << " " << rs;
#endif // DEBUG
	r[rd] = (word) r[rt] >> (r[rs]&0x1F);
	++pc;
}

void R4300i::SUB(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "SUB " << rd << " " << rs << " " << rt;
#endif // DEBUG
	r[rd] = (sword) r[rs] - (sword) r[rt];
	++pc;
}

void R4300i::SUBU(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "SUBU " << rd << " " << rs << " " << rt;
#endif // DEBUG
	r[rd] = (word) r[rs] - (word) r[rt];
	++pc;
}

void R4300i::XOR(int rd, int rs, int rt)
{
#if defined DEBUG
		cout << "XOR " << rd << " " << rs << " " << rt;
#endif // DEBUG
	r[rd] = r[rs] ^ r[rt];
	++pc;
}

void R4300i::XORI(int rt, int rs, int immed)
{
#if defined DEBUG
		cout << "XORI " << rt << " " << rs << " " << immed;
#endif // DEBUG
	r[rt] = (word) r[rs] ^ immed;
	++pc;
}

void R4300i::BEQ(int rs, int rt, int immed)
{
#if defined DEBUG
		cout << "BEQ " << rs << " " << rt << " " << immed;
#endif // DEBUG
	if (r[rs] == r[rt])
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BEQL(int rs, int rt, int immed)
{
#if defined DEBUG
		cout << "BEQL " << rs << " " << rt << " " << immed;
#endif // DEBUG
	if (r[rs] == r[rt])
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BGEZ(int immed, int rs)
{
#if defined DEBUG
		cout << "BGEZ " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] >= 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BGEZAL(int immed, int rs)
{
#if defined DEBUG
		cout << "BGEZAL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] >= 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		r[31] = pc;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BGEZALL(int immed, int rs)
{
#if defined DEBUG
		cout << "BGEZALL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] >= 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		r[31] = pc;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BGEZL(int immed, int rs)
{
#if defined DEBUG
		cout << "BGEZL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] >= 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BGTZ(int immed, int rs)
{
#if defined DEBUG
		cout << "BGTZ " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] > 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BGTZL(int immed, int rs)
{
#if defined DEBUG
		cout << "BGTZL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] > 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BLEZ(int immed, int rs)
{
#if defined DEBUG
		cout << "BLEZ " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] <= 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BLEZL(int immed, int rs)
{
#if defined DEBUG
		cout << "BLEZL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] <= 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BLTZ(int immed, int rs)
{
#if defined DEBUG
		cout << "BLTZ " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] < 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BLTZAL(int immed, int rs)
{
#if defined DEBUG
		cout << "BLTZAL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] < 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		r[31] = pc;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BLTZALL(int immed, int rs)
{
#if defined DEBUG
		cout << "BLTZALL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] < 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		r[31] = pc;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BLTZL(int immed, int rs)
{
#if defined DEBUG
		cout << "BLTZL " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] < 0)
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BNE(int rs, int rt, int immed)
{
#if defined DEBUG
		cout << "BNE " << rs << " " << rt << " " << immed;
#endif // DEBUG
	if (r[rs] != r[rt])
	{
		dword pc_tmp = pc + immed;
		++pc;
		decode(rom.getInstruction(pc));
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::BNEL(int rs, int rt, int immed)
{
#if defined DEBUG
		cout << "BNEL " << rs << " " << rt << " " << immed;
#endif // DEBUG
	if (r[rs] != r[rt])
	{
		dword pc_tmp = pc + immed;
		++pc;
		delay_slot = 1;
		decode(rom.getInstruction(pc));
		delay_slot = 0;
		pc = pc_tmp;
	}
	else
	{
		++pc;
	}
}

void R4300i::J(int address)
{
#if defined DEBUG
		cout << "J " << address;
#endif // DEBUG
	++pc;
	delay_slot = 1;
	decode(rom.getInstruction(pc));
	delay_slot = 0;
	pc = address;
}

void R4300i::JAL(int address)
{
#if defined DEBUG
		cout << "JAL " << address;
#endif // DEBUG
	++pc;
	delay_slot = 1;
	decode(rom.getInstruction(pc));
	delay_slot = 0;
	r[31] = pc;
	pc = address;
}

void R4300i::JALR(int rs, int rd)
{
#if defined DEBUG
		cout << "JALR " << rs << " " << rd;
#endif // DEBUG
	++pc;
	delay_slot = 1;
	decode(rom.getInstruction(pc));
	delay_slot = 0;
	r[rd] = pc;
	pc = r[rs];
}

void R4300i::JR(int rs)
{
#if defined DEBUG
		cout << "JR " << rs;
#endif // DEBUG
	++pc;
	delay_slot = 1;
	decode(rom.getInstruction(pc));
	delay_slot = 0;
	pc = r[rs];
}

void R4300i::BREAK(int immed)
{
#if defined DEBUG
		cout << "SYSCALL " << immed;
#endif // DEBUG
	ehandler.interruption();
}

void R4300i::SYSCALL(int immed)
{
#if defined DEBUG
		cout << "SYSCALL " << immed;
#endif // DEBUG
	ehandler.syscall();
}

void R4300i::TEQ(int rs, int rt)
{
#if defined DEBUG
		cout << "TEQ " << rs << " " << rt;
#endif // DEBUG
	if (r[rt] == r[rs])
		ehandler.trap();
	++pc;
}

void R4300i::TEQI(int rs, int immed)
{
#if defined DEBUG
		cout << "TEQI " << rs << " " << immed;
#endif // DEBUG
	if (r[rs] == immed)
		ehandler.trap();
	++pc;
}

void R4300i::TGE(int rs, int rt)
{
#if defined DEBUG
		cout << "TGE " << rs << " " << rt;
#endif // DEBUG
	if (r[rs] >= r[rt])
		ehandler.trap();
	++pc;
}

void R4300i::TGEI(int rs, int immed)
{
#if defined DEBUG
		cout << "TGEI " << rs << " " << immed;
#endif // DEBUG
	if (r[rs] >= immed)
		ehandler.trap();
	++pc;
}

void R4300i::TGEIU(int rs, int immed)
{
#if defined DEBUG
		cout << "TGEIU " << rs << " " << immed;
#endif // DEBUG
	if (r[rs] >= immed)
		ehandler.trap();
	++pc;
}

void R4300i::TGEU(int rs, int rt)
{
#if defined DEBUG
		cout << "TGEU " << rs << " " << rt;
#endif // DEBUG
	if (r[rs] >= r[rt])
		ehandler.trap();
	++pc;
}

void R4300i::TLT(int rs, int rt)
{
#if defined DEBUG
		cout << "TLT " << rs << " " << rt;
#endif // DEBUG
	if (r[rs] < r[rt])
		ehandler.trap();
	++pc;
}

void R4300i::TLTI(int rs, int immed)
{
#if defined DEBUG
		cout << "TLTI " << rs << " " << immed;
#endif // DEBUG
	if ((sdword) r[rs] < immed)
		ehandler.trap();
	++pc;
}

void R4300i::TLTIU(int rs, int immed)
{
#if defined DEBUG
		cout << "TLTIU " << rs << " " << immed;
#endif // DEBUG
	if (r[rs] < immed)
		ehandler.trap();
	++pc;
}

void R4300i::TLTU(int rs, int rt)
{
#if defined DEBUG
		cout << "TLTU " << rs << " " << rt;
#endif // DEBUG
	if (r[rs] < r[rt])
		ehandler.trap();
	++pc;
}

void R4300i::TNE(int rs, int rt)
{
#if defined DEBUG
		cout << "TNE " << rs << " " << rt;
#endif // DEBUG
	if (r[rs] != r[rt])
		ehandler.trap();
	++pc;
}

void R4300i::TNEI(int rs, int immed)
{
#if defined DEBUG
		cout << "TNEI " << rs << " " << immed;
#endif // DEBUG
	if (r[rs] != immed)
		ehandler.trap();
	++pc;
}

void R4300i::CACHE(int rt, int immed, int rs)
{
#if defined DEBUG
		cout << "CACHE " << rt << " " << immed << " " << rs;
#endif // DEBUG
	++pc;
}

int jump_marker = 0;

void R4300i::ERET(void)
{
#if defined DEBUG
		cout << "ERET";
#endif // DEBUG
   if (Status & 0x4)
     {
#if defined DEBUG
		cout << " : ERROR IN ERET";
#endif // DEBUG
     }
   else
     {
	Status &= 0xFFFFFFFD;
	pc = EPC;
     }
   ll = 0;
}

void R4300i::MFC0(int rt, int fs)
{
#if defined DEBUG
		cout << "MFC0 " << rt << " " << fs;
#endif // DEBUG
	r[rt] = cop0[fs];
	++pc;
}

void R4300i::MTC0(int rt, int fs)
{
#if defined DEBUG
		cout << "MTC0 " << rt << " " << fs;
#endif // DEBUG
		switch(fs)
     {
      case 0:    // Index
	Index = r[rt] & 0x8000003F;
	if ((Index & 0x3F) > 31) 
	     cout << " il y a plus de 32 TLB";
	break;
      case 1:    // Random
	break;
      case 2:    // EntryLo0
	EntryLo0 = r[rt] & 0x3FFFFFFF;
	break;
      case 3:    // EntryLo1
 	EntryLo1 = r[rt] & 0x3FFFFFFF;
	break;
      case 4:    // Context
	Context = (r[rt] & 0xFF800000) | (Context & 0x007FFFF0);
	break;
      case 5:    // PageMask
	PageMask = r[rt] & 0x01FFE000;
	break;
      case 6:    // Wired
	Wired = (word) r[rt];
	Random = 31;
	break;
      case 8:    // BadVAddr
	break;
      case 9:    // Count)
	break;
      case 10:   // EntryHi
	EntryHi = r[rt] & 0xFFFFE0FF;
	break;
      case 11:   // Compare
	break;
      case 12:   // Status
	if((r[rt] & 0x04000000) != (Status & 0x04000000))
	  {
	     if (r[rt] & 0x04000000)
	       {
		  int i;
		  for (i=0; i<32; i++)
		    {
		       //reg_cop1_double[i]=(double*)&reg_cop1_fgr_64[i];
		       //reg_cop1_simple[i]=(float*)&reg_cop1_fgr_64[i];
		    }
	       }
	     else
	       {
		  int i;
		  for (i=0; i<32; i++)
		    {
		       if(!(i&1))
				   ;
			// reg_cop1_double[i]=(double*)&reg_cop1_fgr_64[i>>1];
#ifndef _BIG_ENDIAN
		     //  reg_cop1_simple[i]=(float*)&reg_cop1_fgr_64[i>>1]+(i&1);
#else
		    //   reg_cop1_simple[i]=(float*)&reg_cop1_fgr_64[i>>1]+(1-(i&1));
#endif
		    }
	       }
	  }
	Status = (word) r[rt];
	break;
      case 13:   // Cause
	if (r[rt]!=0)
	     cout << " écriture dans Cause";
	else Cause = (word) r[rt];
	break;
      case 14:   // EPC
	EPC = (word) r[rt];
	break;
      case 15:  // PRevID
	break;
      case 16:  // Config
	Config = (word) r[rt];
	break;
      case 18:  // WatchLo
	WatchLo = r[rt] & 0xFFFFFFFF;
	break;
      case 19:  // WatchHi
	WatchHi = r[rt] & 0xFFFFFFFF;
	break;
      case 27: // CacheErr
	break;
      case 28: // TagLo
	TagLo = r[rt] & 0x0FFFFFC0;
	break;
      case 29: // TagHi
	TagHi =0;
	break;
      default:
	cout << "unknown mtc0 write";
     }
   ++pc;
}

void R4300i::TLBP(void)
{
   int i;
   Index |= 0x80000000;
   for (i=0; i<32; i++)
     {
	if (((tlb_e[i].vpn2 & (~tlb_e[i].mask)) ==
	     (((EntryHi & 0xFFFFE000) >> 13) & (~tlb_e[i].mask))) &&
	    ((tlb_e[i].g) ||
	     (tlb_e[i].asid == (EntryHi & 0xFF))))
	  {
	     Index = i;
	     break;
	  }
     }
   ++pc;
}

void R4300i::TLBR(void)
{  
   int index;
   index = Index & 0x1F;
   PageMask = tlb_e[index].mask << 13;
   EntryHi = ((tlb_e[index].vpn2 << 13) | tlb_e[index].asid);
   EntryLo0 = (tlb_e[index].pfn_even << 6) | (tlb_e[index].c_even << 3)
     | (tlb_e[index].d_even << 2) | (tlb_e[index].v_even << 1)
       | tlb_e[index].g;
   EntryLo1 = (tlb_e[index].pfn_odd << 6) | (tlb_e[index].c_odd << 3)
     | (tlb_e[index].d_odd << 2) | (tlb_e[index].v_odd << 1)
       | tlb_e[index].g;
   ++pc;
}

void R4300i::TLBWI(void)
{
   unsigned int i;
   if (tlb_e[Index&0x3F].v_even)
     {
	for (i=tlb_e[Index&0x3F].start_even; i<tlb_e[Index&0x3F].end_even; i++)
	  {
	     tlb_LUT_r[i>>12] = 0;
	     invalid_code[i>>12] = 1;
	  }
	if (tlb_e[Index&0x3F].d_even)
	  for (i=tlb_e[Index&0x3F].start_even; i<tlb_e[Index&0x3F].end_even; i++)
	    tlb_LUT_w[i>>12] = 0;
     }
   if (tlb_e[Index&0x3F].v_odd)
     {
	for (i=tlb_e[Index&0x3F].start_odd; i<tlb_e[Index&0x3F].end_odd; i++)
	  {
	     tlb_LUT_r[i>>12] = 0;
	     invalid_code[i>>12] = 1;
	  }
	if (tlb_e[Index&0x3F].d_odd)
	  for (i=tlb_e[Index&0x3F].start_odd; i<tlb_e[Index&0x3F].end_odd; i++)
	    tlb_LUT_w[i>>12] = 0;
     }
   tlb_e[Index&0x3F].g = (EntryLo0 & EntryLo1 & 1);
   tlb_e[Index&0x3F].pfn_even = (EntryLo0 & 0x3FFFFFC0) >> 6;
   tlb_e[Index&0x3F].pfn_odd = (EntryLo1 & 0x3FFFFFC0) >> 6;
   tlb_e[Index&0x3F].c_even = (EntryLo0 & 0x38) >> 3;
   tlb_e[Index&0x3F].c_odd = (EntryLo1 & 0x38) >> 3;
   tlb_e[Index&0x3F].d_even = (EntryLo0 & 0x4) >> 2;
   tlb_e[Index&0x3F].d_odd = (EntryLo1 & 0x4) >> 2;
   tlb_e[Index&0x3F].v_even = (EntryLo0 & 0x2) >> 1;
   tlb_e[Index&0x3F].v_odd = (EntryLo1 & 0x2) >> 1;
   tlb_e[Index&0x3F].asid = (EntryHi & 0xFF);
   tlb_e[Index&0x3F].vpn2 = (EntryHi & 0xFFFFE000) >> 13;
   tlb_e[Index&0x3F].r = (EntryHi & 0xC000000000000000LL) >> 62;
   tlb_e[Index&0x3F].mask = (PageMask & 0x1FFE000) >> 13;
   
   tlb_e[Index&0x3F].start_even = tlb_e[Index&0x3F].vpn2 << 13;
   tlb_e[Index&0x3F].end_even = tlb_e[Index&0x3F].start_even+
     (tlb_e[Index&0x3F].mask << 12) + 0xFFF;
   tlb_e[Index&0x3F].phys_even = tlb_e[Index&0x3F].pfn_even << 12;
   
   if (tlb_e[Index&0x3F].v_even)
     {
	if (tlb_e[Index&0x3F].start_even < tlb_e[Index&0x3F].end_even &&
	    !(tlb_e[Index&0x3F].start_even >= 0x80000000 &&
	    tlb_e[Index&0x3F].end_even < 0xC0000000) &&
	    tlb_e[Index&0x3F].phys_even < 0x20000000)
	  {
	     for (i=tlb_e[Index&0x3F].start_even;i<tlb_e[Index&0x3F].end_even;i++)
	       tlb_LUT_r[i>>12] = 0x80000000 | 
	       (tlb_e[Index&0x3F].phys_even + (i - tlb_e[Index&0x3F].start_even));
	     if (tlb_e[Index&0x3F].d_even)
	       for (i=tlb_e[Index&0x3F].start_even;i<tlb_e[Index&0x3F].end_even;i++)
		 tlb_LUT_w[i>>12] = 0x80000000 | 
	       (tlb_e[Index&0x3F].phys_even + (i - tlb_e[Index&0x3F].start_even));
	  }
     }
   tlb_e[Index&0x3F].start_odd = tlb_e[Index&0x3F].end_even+1;
   tlb_e[Index&0x3F].end_odd = tlb_e[Index&0x3F].start_odd+
     (tlb_e[Index&0x3F].mask << 12) + 0xFFF;
   tlb_e[Index&0x3F].phys_odd = tlb_e[Index&0x3F].pfn_odd << 12;
   
   if (tlb_e[Index&0x3F].v_odd)
     {
	if (tlb_e[Index&0x3F].start_odd < tlb_e[Index&0x3F].end_odd &&
	    !(tlb_e[Index&0x3F].start_odd >= 0x80000000 &&
	    tlb_e[Index&0x3F].end_odd < 0xC0000000) &&
	    tlb_e[Index&0x3F].phys_odd < 0x20000000)
	  {
	     for (i=tlb_e[Index&0x3F].start_odd;i<tlb_e[Index&0x3F].end_odd;i++)
	       tlb_LUT_r[i>>12] = 0x80000000 | 
	       (tlb_e[Index&0x3F].phys_odd + (i - tlb_e[Index&0x3F].start_odd));
	     if (tlb_e[Index&0x3F].d_odd)
	       for (i=tlb_e[Index&0x3F].start_odd;i<tlb_e[Index&0x3F].end_odd;i++)
		 tlb_LUT_w[i>>12] = 0x80000000 | 
	       (tlb_e[Index&0x3F].phys_odd + (i - tlb_e[Index&0x3F].start_odd));
	  }
     }
   ++pc;
}

void R4300i::TLBWR(void)
{
   unsigned int i;
   Random = (Count/2 % (32 - Wired)) + Wired;
   if (tlb_e[Random].v_even)
     {
	for (i=tlb_e[Random].start_even; i<tlb_e[Random].end_even; i++)
	  {
	     tlb_LUT_r[i>>12] = 0;
	     invalid_code[i>>12] = 1;
	  }
	if (tlb_e[Random].d_even)
	  for (i=tlb_e[Random].start_even; i<tlb_e[Random].end_even; i++)
	    tlb_LUT_w[i>>12] = 0;
     }
   if (tlb_e[Random].v_odd)
     {
	for (i=tlb_e[Random].start_odd; i<tlb_e[Random].end_odd; i++)
	  {
	     tlb_LUT_r[i>>12] = 0;
	     invalid_code[i>>12] = 1;
	  }
	if (tlb_e[Random].d_odd)
	  for (i=tlb_e[Random].start_odd; i<tlb_e[Random].end_odd; i++)
	    tlb_LUT_w[i>>12] = 0;
     }
   tlb_e[Random].g = (EntryLo0 & EntryLo1 & 1);
   tlb_e[Random].pfn_even = (EntryLo0 & 0x3FFFFFC0) >> 6;
   tlb_e[Random].pfn_odd = (EntryLo1 & 0x3FFFFFC0) >> 6;
   tlb_e[Random].c_even = (EntryLo0 & 0x38) >> 3;
   tlb_e[Random].c_odd = (EntryLo1 & 0x38) >> 3;
   tlb_e[Random].d_even = (EntryLo0 & 0x4) >> 2;
   tlb_e[Random].d_odd = (EntryLo1 & 0x4) >> 2;
   tlb_e[Random].v_even = (EntryLo0 & 0x2) >> 1;
   tlb_e[Random].v_odd = (EntryLo1 & 0x2) >> 1;
   tlb_e[Random].asid = (EntryHi & 0xFF);
   tlb_e[Random].vpn2 = (EntryHi & 0xFFFFE000) >> 13;
   tlb_e[Random].r = (EntryHi & 0xC000000000000000LL) >> 62;
   tlb_e[Random].mask = (PageMask & 0x1FFE000) >> 13;
   
   tlb_e[Random].start_even = tlb_e[Random].vpn2 << 13;
   tlb_e[Random].end_even = tlb_e[Random].start_even+
     (tlb_e[Random].mask << 12) + 0xFFF;
   tlb_e[Random].phys_even = tlb_e[Random].pfn_even << 12;
   
   if (tlb_e[Random].v_even)
     {
	if (tlb_e[Random].start_even < tlb_e[Random].end_even &&
	    !(tlb_e[Random].start_even >= 0x80000000 &&
	    tlb_e[Random].end_even < 0xC0000000) &&
	    tlb_e[Random].phys_even < 0x20000000)
	  {
	     for (i=tlb_e[Random].start_even;i<tlb_e[Random].end_even;i++)
	       tlb_LUT_r[i>>12] = 0x80000000 | 
	       (tlb_e[Random].phys_even + (i - tlb_e[Random].start_even));
	     if (tlb_e[Random].d_even)
	       for (i=tlb_e[Random].start_even;i<tlb_e[Random].end_even;i++)
		 tlb_LUT_w[i>>12] = 0x80000000 | 
	       (tlb_e[Random].phys_even + (i - tlb_e[Random].start_even));
	  }
     }
   tlb_e[Random].start_odd = tlb_e[Random].end_even+1;
   tlb_e[Random].end_odd = tlb_e[Random].start_odd+
     (tlb_e[Random].mask << 12) + 0xFFF;
   tlb_e[Random].phys_odd = tlb_e[Random].pfn_odd << 12;
   
   if (tlb_e[Random].v_odd)
     {
	if (tlb_e[Random].start_odd < tlb_e[Random].end_odd &&
	    !(tlb_e[Random].start_odd >= 0x80000000 &&
	    tlb_e[Random].end_odd < 0xC0000000) &&
	    tlb_e[Random].phys_odd < 0x20000000)
	  {
	     for (i=tlb_e[Random].start_odd;i<tlb_e[Random].end_odd;i++)
	       tlb_LUT_r[i>>12] = 0x80000000 | 
	       (tlb_e[Random].phys_odd + (i - tlb_e[Random].start_odd));
	     if (tlb_e[Random].d_odd)
	       for (i=tlb_e[Random].start_odd;i<tlb_e[Random].end_odd;i++)
		 tlb_LUT_w[i>>12] = 0x80000000 | 
	       (tlb_e[Random].phys_odd + (i - tlb_e[Random].start_odd));
	  }
     }
   ++pc;
}

template<typename Type>
void R4300i::ABS(int fd, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::ADD(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::BC1F(int immed)
{
	// TODO
}

void R4300i::BC1FL(int immed)
{
	// TODO
}

void R4300i::BC1T(int immed)
{
	// TODO
}

void R4300i::BC1TL(int immed)
{
	// TODO
}

template<typename Type>
void R4300i::C(int fs, int ft, int cond)
{
	// TODO
	/*
	switch (cond) {
	case 0:
		F<Type>(f[fs], f[ft]);
	case 1:
		UN<Type>(f[fs], f[ft]);
	case 2:
		EQ<Type>(f[fs], f[ft]);
		//...
	default:
		// ERROR
		;
	}
	*/
}

template<typename Type, typename toType>
void R4300i::CEIL(int fd, int fs)
{
	// TODO
}

void R4300i::CFC1(int rt, int fs)
{
	// TODO
}

void R4300i::CTC1(int rt, int fs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::CVT(int fd, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::DIV(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::DMFC1(int rt, int fs)
{
	// TODO
}

void R4300i::DMTC1(int rt, int fs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::FLOOR(int fd, int fs)
{
	// TODO
}

void R4300i::LDC1(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::LWC1(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::MFC1(int rt, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::MOV(int fd, int fs)
{
	// TODO
}

void R4300i::MTC1(int rt, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::MUL(int fd, int fs, int ft)
{
	// TODO
}

template<typename Type>
void R4300i::NEG(int fd, int fs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::ROUND(int fd, int fs)
{
	// TODO
}

void R4300i::SDC1(int ft, int immed, int rs)
{
	// TODO
}

template<typename Type>
void R4300i::SQRT(int fd, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::SUB(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::SWC1(int ft, int immed, int rs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::TRUNC(int fd, int fs)
{
	// TODO
}

void R4300i::NOP(void)
{
	// TODO
}

void R4300i::MOVE(int rd, int rs)
{
	// TODO
}

void R4300i::NEG(int rd, int rt)
{
	// TODO
}

void R4300i::NEGU(int rd, int rs)
{
	// TODO
}

void R4300i::BNEZ(int immed, int rs)
{
	// TODO
}

void R4300i::BNEZL(int immed, int rs)
{
	// TODO
}

void R4300i::BEQZ(int immed, int rs)
{
	// TODO
}

void R4300i::BEQZL(int immed, int rs)
{
	// TODO
}

void R4300i::B(int immed)
{
	// TODO
}

void R4300i::BAL(int immed)
{
	// TODO
}

void R4300i::LI(int rt, int immed)
{
	// TODO
}

void R4300i::S_S(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::L_S(int ft, int immed, int rs)
{
	// TODO
}

template<typename Type>
bool R4300i::F(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::UN(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::EQ(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::UEQ(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::OLT(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::ULT(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::OLE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::ULE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::SF(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGLE(Type a, Type b)
{
	// TODO
	return true;
}


template<typename Type>
bool R4300i::SEQ(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGL(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool LT(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::LE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGT(Type a, Type b)
{
	// TODO
	return true;
}

