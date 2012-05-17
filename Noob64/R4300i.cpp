#include "StdAfx.h"
#include "R4300i.h"

R4300i::R4300i(void) : ehandler(*new ExceptionHandler())
{
}

void R4300i::decode(const word i)
{
	switch(getOpCode(i)) {
	case 0: // 000000
		decode_r(i);
		break;
	case 1: // 000001
		decode_regimm(i);
		break;
	case 2: // 000010
		J(getAdress(i));
		break;
	case 3: // 000011
		JAL(getAdress(i));
		break;
	case 4: // 000100
		BEQ(getRs(i), getRt(i), getImmed(i));
		break;
	case 5: // 000101
		BNE(getRs(i), getRt(i), getImmed(i));
		break;
	case 6: // 000110
		BLEZ(getRs(i), getImmed(i));
		break;
	case 7: // 000111
		BGTZ(getRs(i), getImmed(i));
		break;
	case 8: // 001000
		ADDI(getRt(i), getRs(i), getImmed(i));
		break;
	case 9: // 001001
		ADDIU(getRt(i), getRs(i), getImmed(i));
		break;
	case 10: // 001010
		SLTI(getRt(i), getRs(i), getImmed(i));
		break;
	case 11: // 001011
		SLTIU(getRt(i), getRs(i), getImmed(i));
		break;
	case 12: // 001100
		ANDI(getRt(i), getRs(i), getImmed(i));
		break;
	case 13: // 001101
		ORI(getRt(i), getRs(i), getImmed(i));
		break;
	case 14: // 001110
		XORI(getRt(i), getRs(i), getImmed(i));
		break;
	case 15: // 001111
		LUI(getRt(i), getImmed(i));
		break;
	case 16: // 010000
		decode_cop0(i);
		break;
	case 17: // 010001
		decode_cop1(i);
		break;
	case 20: // 010100
		break;
	case 21: // 010101
		break;
	case 22: // 010110
		break;
	case 23: // 010111
		break;
	case 24: // 011000
		break;
	case 25: // 011001
		break;
	case 26: // 011010
		break;
	case 27: // 011011
		break;
	case 32: // 100000
		break;
	case 33: // 100001
		break;
	case 34: // 100010
		break;
	case 35: // 100011
		break;
	case 36: // 100100
		break;
	case 37: // 100101
		break;
	case 38: // 100110
		break;
	case 39: // 100111
		break;
	case 40: // 101000
		break;
	case 41: // 101001
		break;
	case 42: // 101010
		break;
	case 43: // 101011
		break;
	case 44: // 101100
		break;
	case 45: // 101101
		break;
	case 46: // 101110
		break;
	case 47: // 101111
		break;
	case 48: // 110000
		break;
	case 49: // 110001
		break;
	case 52: // 110100
		break;
	case 53: // 110101
		break;
	case 54: // 110110
		break;
	case 55: // 110111
		break;
	case 56: // 111000
		break;
	case 57: // 111001
		break;
	case 60: // 111100
		break;
	case 61: // 111101
		break;
	case 62: // 111110
		break;
	case 63: // 111111
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_r(word i)
{
	switch(getFunc(i)) {
	case 0: // 000000
		//SLL;
		break;
	case 2: // 000010
		//SRL;
		break;
	case 3: // 000011
		//SRA;
		break;
	case 4: // 000100
		//SLLV;
		break;
	case 6: // 000110
		//SRLV;
		break;
	case 7: // 000111
		//SRAV;
		break;
	case 8: // 001000
		//JR;
		break;
	case 9: // 001001
		//JALR;
		break;
	case 12: // 001100
		//SYSCALL;
		break;
	case 13: // 001101
		//BREAK;
		break;
	case 15: // 001111
		//SYNC;
		break;
	case 16: // 010000
		//MFHI;
		break;
	case 17: // 010001
		//MTHI;
		break;
	case 18: // 010010
		//MFLO;
		break;
	case 19: // 010011
		//MTLO;
		break;
	case 20: // 010100
		//DSLLV;
		break;
	case 22: // 010110
		//DSRLV;
		break;
	case 23: // 010111
		//DSRAV;
		break;
	case 24: // 011000
		//MULT;
		break;
	case 25: // 011001
		//MULTU;
		break;
	case 26: // 011010
		//DIV;
		break;
	case 27: // 011011
		//DIVU;
		break;
	case 28: // 011100
		//DMULT;
		break;
	case 29: // 011101
		//DMULTU;
		break;
	case 30: // 011110
		//DDIV;
		break;
	case 31: // 011111
		//DDIVU;
		break;
	case 32: // 100000
		//ADD;
		break;
	case 33: // 100001
		//ADDU;
		break;
	case 34: // 100010
		//SUB;
		break;
	case 35: // 100011
		//SUBU;
		break;
	case 36: // 100100
		//AND;
		break;
	case 37: // 100101
		//OR;
		break;
	case 38: // 100110
		//XOR;
		break;
	case 39: // 100111
		//NOR;
		break;
	case 42: // 101010
		//SLT;
		break;
	case 43: // 101011
		//SLTU;
		break;
	case 44: // 101100
		//DADD;
		break;
	case 45: // 101101
		//DADDU;
		break;
	case 46: // 101110
		//DSUB;
		break;
	case 47: // 101111
		//DSUBU;
		break;
	case 48: // 110000
		//TGE;
		break;
	case 49: // 110001
		//TGEU;
		break;
	case 50: // 110010
		//TLT;
		break;
	case 51: // 110011
		//TLTU;
		break;
	case 52: // 110100
		//TEQ;
		break;
	case 54: // 110110
		//TNE;
		break;
	case 56: // 111000
		//DSLL;
		break;
	case 58: // 111010
		//DSRL;
		break;
	case 59: // 111011
		//DSRA;
		break;
	case 60: // 111100
		//DSLL32;
		break;
	case 62: // 111110
		//DSRL32;
		break;
	case 63: // 111111
		//DSRA32;
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_regimm(word i)
{
	switch(getRt(i)) {
	//TODO
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_cop0(word i)
{
	switch(getFmt(i)) {
	case 0: // 00000
		MFC0(getRt(i), getFs(i));
		break;
	case 4: // 00100
		MTC0(getRt(i), getFs(i));
		break;
	case 16: // 10000
		decode_tlb(i);
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_tlb(word i)
{
	switch(getFunc(i)) {
	case 1: // 000001
		TLBR();
		break;
	case 2: // 000010
		TLBWI();
		break;
	case 6: // 000110
		TLBWR();
		break;
	case 8: // 001000
		TLBP();
		break;
	case 24: // 011000
		ERET();
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_cop1(const word i)
{
	switch(getFmt(i)) {
	case 0: // 00000
		MFC1(getRt(i), getFs(i));
		break;
	case 1: // 00001
		DMFC1(getRt(i), getFs(i));
		break;
	case 2: // 00010
		CFC1(getRt(i), getFs(i));
		break;
	case 4: // 00100
		MTC1(getRt(i), getFs(i));
		break;
	case 5: // 00101
		DMTC1(getRt(i), getFs(i));
		break;
	case 6: // 00110
		CTC1(getRt(i), getFs(i));
		break;
	case 8: // 01000
		decode_bc1(i);
		break;
	case 16: // 10000
		decode_fpu_b(i);
		break;
	case 17: // 10001
		decode_fpu_h(i);
		break;
	case 20: // 10100
		decode_fpu_w(i);
		break;
	case 21: // 10101
		decode_fpu_d(i);
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_bc1(const word i)
{
	switch(getNdTf(i)) {
	case 0: // 00
		BC1F(getImmed(i));
		break;
	case 1: // 01
		BC1T(getImmed(i));
		break;
	case 2: // 10
		BC1FL(getImmed(i));
		break;
	case 3: // 11
		BC1TL(getImmed(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_fpu_b(const word i)
{
	switch(getFunc(i)) {
	// TODO
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_fpu_h(const word i)
{
	switch(getFunc(i)) {
	// TODO
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_fpu_w(const word i)
{
	switch(getFunc(i)) {
	// TODO
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_fpu_d(const word i)
{
	switch(getFunc(i)) {
	// TODO
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

void R4300i::LB(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LBU(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LDL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LDR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LH(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LHU(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LLD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LW(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LWL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LWR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LWU(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SB(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SC(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SCD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SDL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SDR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SH(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SW(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SWL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SWR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SYNC(void)
{
	// TODO
}

void R4300i::ADD(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::ADDI(int rt, int rs, int immed)
{
	if (DWORD_MAX - immed < r[rs])
	{
		//TODO: If overflow occurs, then trap.
		ehandler.trap();
	}
	else
	{
		r[rt] = r[rs] + immed;
	}
}

void R4300i::ADDIU(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::ADDU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::AND(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::ANDI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::DADD(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::DADDI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::DADDIU(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::DADDU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::DDIV(int rs, int rt)
{
	// TODO
}

void R4300i::DDIVU(int rs, int rt)
{
	// TODO
}

void R4300i::DIV(int rs, int rt)
{
	// TODO
}

void R4300i::DIVU(int rs, int rt)
{
	// TODO
}

void R4300i::DMULT(int rs, int rt)
{
	// TODO
}

void R4300i::DMULTU(int rs, int rt)
{
	// TODO
}

void R4300i::DSLL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSLL32(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSLLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::DSRA(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRA32(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRAV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::DSRL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRL32(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::DSUB(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::DSUBU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::LUI(int rt, int immed)
{
	// TODO
}

void R4300i::MFHI(int rd)
{
	// TODO
}

void R4300i::MFLO(int rd)
{
	// TODO
}

void R4300i::MTHI(int rd)
{
	// TODO
}

void R4300i::MTLO(int rd)
{
	// TODO
}

void R4300i::MULT(int rs, int rt)
{
	// TODO
}

void R4300i::MULTU(int rs, int rt)
{
	// TODO
}

void R4300i::NOR(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::OR(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::ORI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::SLL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::SLLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::SLT(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::SLTI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::SLTIU(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::SLTU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::SRA(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::SRAV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::SRL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::SRLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::SUB(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::SUBU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::XOR(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::XORI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::BEQ(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::BEQL(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::BGEZ(int immed, int rs)
{
	// TODO
}

void R4300i::BGEZAL(int immed, int rs)
{
	// TODO
}

void R4300i::BGEZALL(int immed, int rs)
{
	// TODO
}

void R4300i::BGEZL(int immed, int rs)
{
	// TODO
}

void R4300i::BGTZ(int immed, int rs)
{
	// TODO
}

void R4300i::BGTZL(int immed, int rs)
{
	// TODO
}

void R4300i::BLEZ(int immed, int rs)
{
	// TODO
}

void R4300i::BLEZL(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZ(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZAL(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZALL(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZL(int immed, int rs)
{
	// TODO
}

void R4300i::BNE(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::BNEL(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::J(int address)
{
	// TODO
}

void R4300i::JAL(int address)
{
	// TODO
}

void R4300i::JALR(int rs, int rd)
{
	// TODO
}

void R4300i::JR(int rs)
{
	// TODO
}

void R4300i::BREAK(int immed)
{
	// TODO
}

void R4300i::SYSCALL(int immed)
{
	// TODO
}

void R4300i::TEQ(int rs, int rt)
{
	// TODO
}

void R4300i::TEQI(int rs, int immed)
{
	// TODO
}

void R4300i::TGE(int rs, int rt)
{
	// TODO
}

void R4300i::TGEI(int rs, int immed)
{
	// TODO
}

void R4300i::TGEIU(int rs, int immed)
{
	// TODO
}

void R4300i::TGEU(int rs, int rt)
{
	// TODO
}

void R4300i::TLT(int rs, int rt)
{
	// TODO
}

void R4300i::TLTI(int rs, int immed)
{
	// TODO
}

void R4300i::TLTIU(int rs, int immed)
{
	// TODO
}

void R4300i::TLTU(int rs, int rt)
{
	// TODO
}

void R4300i::TNE(int rs, int rt)
{
	// TODO
}

void R4300i::TNEI(int rs, int immed)
{
	// TODO
}

void R4300i::CACHE(int op, int immed, int rs)
{
	// TODO
}

void R4300i::ERET(void)
{
	// TODO
}

void R4300i::MFC0(int rt, int fs)
{
	// TODO
}

void R4300i::MTC0(int rt, int fs)
{
	// TODO
}

void R4300i::TLBP(void)
{
	// TODO
}

void R4300i::TLBR(void)
{
	// TODO
}

void R4300i::TLBWI(void)
{
	// TODO
}

void R4300i::TLBWR(void)
{
	// TODO
}

void R4300i::ABS_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::ADD_fmt(int fd, int fs, int ft)
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

void R4300i::C_cond_fmt(int fs, int ft)
{
	// TODO
}

void R4300i::CEIL_L_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::CEIL_W_fmt(int fd, int fs)
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

void R4300i::CVT_D_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::CVT_L_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::CVT_S_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::CVT_W_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::DIV_fmt(int fd, int fs, int ft)
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

void R4300i::FLOOR_L_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::FLOOR_W_fmt(int fd, int fs)
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

void R4300i::MOV_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::MTC1(int rt, int fs)
{
	// TODO
}

void R4300i::MUL_fmt(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::NEG_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::ROUND_L_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::ROUND_W_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::SDC1(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::SQRT_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::SUB_fmt(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::SWC1(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::TRUNC_L_fmt(int fd, int fs)
{
	// TODO
}

void R4300i::TRUNC_W_fmt(int fd, int fs)
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
