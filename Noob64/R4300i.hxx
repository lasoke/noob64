/*
* Noob64 - A Nintendo 64 emulator.
*
* (c) Copyright 2012 Quentin Metzler and 
* Romain Richard.
*
* Permission to use, copy, modify and distribute Noob64 in both binary and
* source form, for non-commercial purposes, is hereby granted without fee,
* providing that this license information and copyright notice appear with
* all copies and any derived work.
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event shall the authors be held liable for any damages
* arising from the use of this software.
*
* Noob64 is freeware for PERSONAL USE only. Commercial users should
* seek permission of the copyright holders first. Commercial use includes
* charging money for Noob64 or software derived from Noob64.
*
* The copyright holders request that bug fixes and improvements to the code
* should be forwarded to them so if they want them.
*
*/

#pragma once

#include "R4300i.h"

//****************************************************************************
//** MACROS																	**
//****************************************************************************

// Prints the current instruction on cout if
// DEBUG has been defined
#if defined DEBUG
#	define PRINT_PC(instr) cout << print_addr((word) pc) << instr
#	define PRINT(instr) cout << instr
#else
#	define PRINT_PC(instr)
#	define PRINT(instr)
#endif

// Checks if the current timer has reached 0
#define CHECK_TIMER()						\
	if (TimerHandler::getTimer() < 0)		\
		TimerHandler::timer_done()			\

// Checks if an interrupt has been detected
// and launches the interrupt handler if so
#define CHECK_INTERRUPT()					\
	if (interrupt_detected)					\
	{										\
		interrupt_detected = false;			\
		trigger_intr_exception();			\
	}										\

// Update the count register and the timer handler
#define UPDATE_TIME()						\
	Count += TIME_UNIT;						\
	TimerHandler::decTimer()				\

// Checks if a copunusable exception has been
// detected and launches the copunusable exception
// handler if so
#define TEST_COP1_USABLE_EXCEPTION()		\
	if (!(Status & STATUS_CU1))				\
	{										\
		trigger_copunusable_exception(1);	\
		return;								\
	}										\

//****************************************************************************
//** GETTERS																**
//****************************************************************************

inline word R4300i::getCop0(int i)					{ return cop0[i]; }

//****************************************************************************
//** SETTERS																**
//****************************************************************************

inline void R4300i::setCop0(int i, word w)					{ cop0[i] = w; }

//****************************************************************************
//** DECODE METHODS															**
//****************************************************************************

inline void R4300i::decode(const word i)
{
	UPDATE_TIME();

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
		trigger_address_error(i, true);
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
		trigger_address_error(i, true);
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
		trigger_address_error(i, true);
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
		trigger_address_error(i, true);
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
		trigger_address_error(i, true);
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
		trigger_address_error(i, true);
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
		trigger_address_error(i, true);
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
		trigger_address_error(i, true);
	}
}

//****************************************************************************
//** INSTRUCTIONS															**
//****************************************************************************

inline void R4300i::LB(int rt, int immed, int rs)
{
	PRINT_PC("LB " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_byte(MMU::read<sbyte>((word) (r[rs] + extend_sign_halfword(immed))));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LBU(int rt, int immed, int rs)
{
	PRINT_PC("LBU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = MMU::read<byte>((word) (r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LD(int rt, int immed, int rs)
{
	PRINT_PC("LD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = MMU::read<dword>((word) (r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LDL(int rt, int immed, int rs)
{
	PRINT_PC("LDL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	dword tmp = MMU::read<dword>((word) (r[rs] + extend_sign_halfword(immed)));
	r[rt] |= (tmp << ((r[rs] + extend_sign_halfword(immed)) & 7) * 8);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LDR(int rt, int immed, int rs)
{
	PRINT_PC("LDR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	dword tmp = MMU::read<dword>((word) (r[rs] + extend_sign_halfword(immed)));
	r[rt] |= (tmp >> (( 7 - (r[rs] + extend_sign_halfword(immed)) & 7)) * 8);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LH(int rt, int immed, int rs)
{
	PRINT_PC("LH " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_halfword(MMU::read<shword>((word) (r[rs] + extend_sign_halfword(immed))));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LHU(int rt, int immed, int rs)
{
	PRINT_PC("LHU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = MMU::read<hword>((word) (r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LL(int rt, int immed, int rs)
{
	PRINT_PC("LL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(MMU::read<sword>((word) (r[rs] + extend_sign_halfword(immed))));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	ll = 1;
	pc += 4;
}

inline void R4300i::LLD(int rt, int immed, int rs)
{
	PRINT_PC("LLD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = MMU::read<sdword>((word) (r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	ll = 1;
	pc += 4;
}

inline void R4300i::LW(int rt, int immed, int rs)
{
	PRINT_PC("LW " << dec << "r" << rt << " 0x" << hex << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(MMU::read<word>((word) (r[rs] + extend_sign_halfword(immed))));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LWL(int rt, int immed, int rs)
{
	PRINT_PC("LWL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	word address = (word) (r[rs] + extend_sign_halfword(immed));
	switch (address & 3)
	{
	case 0:
		r[rt] = extend_sign_word(MMU::read<word>(address));
		break;
	case 1:
		r[rt] = extend_sign_word((r[rt] & 0xFF) | (MMU::read<word>(address & ~3) << 8));
		break;
	case 2:
		r[rt] = extend_sign_word((r[rt] & 0xFFFF) | (MMU::read<word>(address & ~3) << 16));
		break;
	case 3:
		r[rt] = extend_sign_word((r[rt] & 0xFFFFFF) | (MMU::read<word>(address & ~3) << 24));
		break;
	}
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LWR(int rt, int immed, int rs)
{
	PRINT_PC("LWR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
   	word address = (word) (r[rs] + extend_sign_halfword(immed));
	switch (address & 3)
	{
	case 0:
		r[rt] = extend_sign_word((r[rt] & 0xFFFFFF00) | ((MMU::read<word>(address & ~3) >> 24) & 0xFF));
		break;
	case 1:
		r[rt] = extend_sign_word((r[rt] & 0xFFFF0000) | ((MMU::read<word>(address & ~3) >> 16) & 0xFFFF));
		break;
	case 2:
		r[rt] = extend_sign_word((r[rt] & 0xFF000000) + ((MMU::read<word>(address & ~3) >> 8) & 0xFFFFFF));
		break;
	case 3:
		r[rt] = extend_sign_word((r[rt] & 0) + ((MMU::read<word>(address & ~3) >> 0) & 0xFFFFFFFF));
		break;
	}
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::LWU(int rt, int immed, int rs)
{
	PRINT_PC("LWU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = MMU::read<word>((word) (r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::SB(int rt, int immed, int rs)
{
	PRINT_PC("SB " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	MMU::write<byte>(r[rt] & 0xFF, (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

inline void R4300i::SC(int rt, int immed, int rs)
{
	if (ll)
	{
		PRINT_PC("SC " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
		MMU::write<word>(r[rt] & 0xFFFFFFFF, (word) (r[rs] + extend_sign_halfword(immed)));
		//maybe something to do here...
		ll = 0;
	}
	else
		PRINT_PC("SC " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]  no ll was done before");
	pc += 4;
}

inline void R4300i::SCD(int rt, int immed, int rs)
{
	if (ll)
	{
		PRINT_PC("SCD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
		MMU::write<dword>(r[rt], (word) (r[rs] + extend_sign_halfword(immed)));
		//maybe something to do here...
		ll = 0;
	}
	else
	{
		PRINT_PC("SCD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]  no ll was done before");
	}
	pc += 4;
}

inline void R4300i::SD(int rt, int immed, int rs)
{
	PRINT_PC("SD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	MMU::write<dword>(r[rt], (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

inline void R4300i::SDL(int rt, int immed, int rs)
{
	dword old_word = 0;
	PRINT_PC("SDL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	old_word = MMU::read<dword>((word) (r[rs] + extend_sign_halfword(immed)));
	old_word = (r[rt] >> (8 * (r[rs] + extend_sign_halfword(immed)) & 7)) | old_word;
	MMU::write<dword>(old_word, (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

inline void R4300i::SDR(int rt, int immed, int rs)
{
	dword old_word = 0;
	PRINT_PC("SDR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	old_word = MMU::read<dword>((word) (r[rs] + extend_sign_halfword(immed)));
	old_word = (r[rt] << (8 * (7 - (r[rs] + extend_sign_halfword(immed)) & 7))) | old_word;
	MMU::write<dword>(old_word, (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

inline void R4300i::SH(int rt, int immed, int rs)
{
	PRINT_PC("SH " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	MMU::write<hword>(r[rt] & 0xFFFF, (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

inline void R4300i::SW(int rt, int immed, int rs)
{
	PRINT_PC("SW " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	MMU::write<word>(r[rt] & 0xFFFFFFFF, (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

inline void R4300i::SWL(int rt, int immed, int rs)
{
	PRINT_PC("SWL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	word address = (word) (r[rs] + extend_sign_halfword(immed));
	switch (address & 3)
	{
	case 0:
		MMU::write<word>(r[rt] & 0xFFFFFFFF, address);
		break;
	case 1:
		address &= ~3;
		MMU::write<word>((MMU::read<word>(address) & 0xFF000000) | ((r[rt] & 0xFFFFFF00) >> 8), address);
		break;
	case 2:
		address &= ~3;
		MMU::write<word>((MMU::read<word>(address) & 0xFFFF0000) | ((r[rt] & 0xFFFF0000) >> 16), address);
		break;
	case 3:
		address &= ~3;
		MMU::write<word>((MMU::read<word>(address) & 0xFFFFFF00) | ((r[rt] & 0xFF000000) >> 24), address);
		break;
	}
	pc += 4;
}

inline void R4300i::SWR(int rt, int immed, int rs)
{
	PRINT_PC("SWR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	word address = (word) (r[rs] + extend_sign_halfword(immed));
	switch (address & 3)
	{
	case 0:
		MMU::write<word>((MMU::read<word>(address) & 0x00FFFFFF) | ((r[rt] & 0x000000FF) << 24), address);
		break;
	case 1:
		address &= ~3;
		MMU::write<word>((MMU::read<word>(address) & 0x0000FFFF) | ((r[rt] & 0x0000FFFF) << 16), address);
		break;
	case 2:
		address &= ~3;
		MMU::write<word>((MMU::read<word>(address) & 0x000000FF) | ((r[rt] & 0x00FFFFFF) << 8), address);
		break;
	case 3:
		address &= ~3;
		MMU::write<word>(r[rt] & 0xFFFFFFFF, address);
		break;
	}
	pc += 4;
}

inline void R4300i::SYNC(void)
{
	PRINT_PC("SYNC?");
	pc += 4;
}

inline void R4300i::ADD(int rd, int rs, int rt)
{
#	if defined DEBUG
	if (!rt) { PRINT_PC("MOVE " << dec << "r" << rd << ", " << dec << "r" << rs); }
	else PRINT_PC("ADD " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
#	endif
	r[rd] = extend_sign_word(r[rs] + r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::ADDI(int rt, int rs, int immed)
{
	PRINT_PC("ADDI " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::ADDIU(int rt, int rs, int immed)
{
	PRINT_PC("ADDIU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << dec << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::ADDU(int rd, int rs, int rt)
{
	PRINT_PC("ADDU " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = extend_sign_word(r[rs] + r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::AND(int rd, int rs, int rt)
{
	PRINT_PC("AND " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] & r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::ANDI(int rt, int rs, int immed)
{
	PRINT_PC("ANDI " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = r[rs] & immed;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::DADD(int rd, int rs, int rt)
{
	PRINT_PC("DADD " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] + r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DADDI(int rt, int rs, int immed)
{
	PRINT_PC("DADDI " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = r[rs] + extend_sign_halfword(immed);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::DADDIU(int rt, int rs, int immed)
{
	PRINT_PC("DADDIU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = r[rs] + extend_sign_halfword(immed);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::DADDU(int rd, int rs, int rt)
{
	PRINT_PC("DADDU " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] + r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DDIV(int rs, int rt)
{
	PRINT_PC("DDIV " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = (sdword) r[rs] / (sdword) r[rt];
	hi = (sdword) r[rs] % (sdword) r[rt];
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::DDIVU(int rs, int rt)
{
	PRINT_PC("DDIVU " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = r[rs] / r[rt];
	hi = r[rs] % r[rt];
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::DIV(int rs, int rt)
{
	PRINT_PC("DIV " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = extend_sign_word(r[rs] / r[rt]);
	hi = extend_sign_word(r[rs] % r[rt]);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::DIVU(int rs, int rt)
{
	PRINT_PC("DIVU " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = extend_sign_word(r[rs] / r[rt]);
	hi = extend_sign_word(r[rs] % r[rt]);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::DMULT(int rs, int rt)
{
	PRINT_PC("DMULT " << dec << "r" << rs << ", " << dec << "r" << rt);
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
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::DMULTU(int rs, int rt)
{
	PRINT_PC("DMULTU " << dec << "r" << rs << ", " << dec << "r" << rt);
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
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::DSLL(int rd, int rt, int sa)
{
	PRINT_PC("DSLL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] << sa;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSLL32(int rd, int rt, int sa)
{
	PRINT_PC("DSLL32 " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] << (sa + 32);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSLLV(int rd, int rt, int rs)
{
	PRINT_PC("DSLLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = r[rt] << r[rs];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSRA(int rd, int rt, int sa)
{
	PRINT_PC("DSRA " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = extend_sign_word(r[rt] >> sa);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSRA32(int rd, int rt, int sa)
{
	PRINT_PC("DSRA32 " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = extend_sign_word(r[rt] >> (sa + 32));
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSRAV(int rd, int rt, int rs)
{
	PRINT_PC("DSRAV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = extend_sign_word(r[rt] >> r[rs]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSRL(int rd, int rt, int sa)
{
	PRINT_PC("DSRL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] >> sa;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSRL32(int rd, int rt, int sa)
{
	PRINT_PC("DSRL32 " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] >> (sa + 32);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSRLV(int rd, int rt, int rs)
{
	PRINT_PC("DSRLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = r[rt] >> r[rs];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSUB(int rd, int rs, int rt)
{
	PRINT_PC("DSUB " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = (sdword) r[rs] - (sdword) r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::DSUBU(int rd, int rs, int rt)
{
	PRINT_PC("DSUBU " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] - r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::LUI(int rt, int immed)
{
	PRINT_PC("LUI " << dec << "r" << rt << " 0x" << hex << extend_sign_halfword(immed));
	r[rt] = extend_sign_word(extend_sign_halfword(immed) << 16);
	PRINT(" r" << dec << rt << "=0x" << hex << r[rt]);
	pc += 4;
}

inline void R4300i::MFHI(int rd)
{
	PRINT_PC("MFHI " << dec << "r" << rd);
	r[rd] = hi;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::MFLO(int rd)
{
	PRINT_PC("MFLO " << dec << "r" << rd);
	r[rd] = lo;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::MTHI(int rs)
{
	PRINT_PC("MTHI " << dec << "r" << rs);
	hi = r[rs];
	PRINT_PC(" hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::MTLO(int rs)
{
	PRINT_PC("MTLO " << dec << "r" << rs);
	lo = r[rs];
	PRINT_PC(" lo" << hex << "=0x" << lo);
	pc += 4;
}

inline void R4300i::MULT(int rs, int rt)
{
	PRINT_PC("MULT " << dec << "r" << rs << ", " << dec << "r" << rt);
	sdword temp = r[rs] * r[rt];
	hi = extend_sign_word(temp >> 32);
	lo = extend_sign_word(temp);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::MULTU(int rs, int rt)
{
	PRINT_PC("DMULTU " << dec << "r" << rs << ", " << dec << "r" << rt);
	dword temp = r[rs] * r[rt];
	hi = extend_sign_word(temp >> 32);
	lo = extend_sign_word(temp);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

inline void R4300i::NOR(int rd, int rs, int rt)
{
	PRINT_PC("NOR " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = ~(r[rs] | r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::OR(int rd, int rs, int rt)
{
	PRINT_PC("OR " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] | r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::ORI(int rt, int rs, int immed)
{
	PRINT_PC("ORI " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	r[rt] = r[rs] | immed;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::SLL(int rd, int rt, int sa)
{
#	if defined DEBUG
	if (!rd && !rt && !sa) { PRINT_PC("NOP"); }
	else PRINT_PC("SLL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
#	endif
	r[rd] = extend_sign_word((word) r[rt] << sa);

#	if defined DEBUG
	if (!rd && !rt && !sa) { }
	else PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
#	endif
	pc += 4;
}

inline void R4300i::SLLV(int rd, int rt, int rs)
{
	PRINT_PC("SLLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = extend_sign_word((word) r[rt] << (r[rs]&0x1F));
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SLT(int rd, int rs, int rt)
{
	PRINT_PC("SLT " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	if ((sword) r[rs] < (sword) r[rt])
		r[rd] = 1;
	else
		r[rd] = 0;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SLTI(int rt, int rs, int immed)
{
	PRINT_PC("SLTI " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	if ((sword) r[rs] < extend_sign_halfword(immed))
		r[rt] = 1;
	else
		r[rt] = 0;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::SLTIU(int rt, int rs, int immed)
{
	PRINT_PC("SLTIU " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	if (r[rs] < extend_sign_halfword(immed))
		r[rt] = 1;
	else
		r[rt] = 0;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::SLTU(int rd, int rs, int rt)
{
	PRINT_PC("SLTU " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	if (r[rs] < r[rt])
		r[rd] = 1;
	else
		r[rd] = 0;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SRA(int rd, int rt, int sa)
{
	PRINT_PC("SRA " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = extend_sign_word((sword) r[rt] >> sa);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SRAV(int rd, int rt, int rs)
{
	PRINT_PC("SRAV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = extend_sign_word((sword) r[rt] >> (r[rs]&0x1F));
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SRL(int rd, int rt, int sa)
{
	PRINT_PC("SRL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = extend_sign_word((word) r[rt] >> sa);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SRLV(int rd, int rt, int rs)
{
	PRINT_PC("SRLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = extend_sign_word((word) r[rt] >> (r[rs]&0x1F));
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SUB(int rd, int rs, int rt)
{
#	if defined DEBUG
	if (!rs) { PRINT_PC("NEG " << dec << "r" << rd << " " << dec << "r" << rt); }
	else PRINT_PC("SUB " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
#	endif
	r[rd] = extend_sign_word(r[rs] - r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::SUBU(int rd, int rs, int rt)
{
#	if defined DEBUG
	if (!rs) { PRINT_PC("NEGU " << dec << "r" << rd << " " << dec << "r" << rt); }
	else PRINT_PC("SUBU " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
#	endif

	r[rd] = extend_sign_word(r[rs] - r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);

	pc += 4;
}

inline void R4300i::XOR(int rd, int rs, int rt)
{
	PRINT_PC("XOR " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] ^ r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

inline void R4300i::XORI(int rt, int rs, int immed)
{
	PRINT_PC("XORI " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	r[rt] = r[rs] ^ immed;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::BEQ(int rs, int rt, int immed)
{
#	if defined DEBUG
	if (!rt && !rs) { PRINT_PC("B"); }
	else if (!rt) { PRINT_PC("BEQZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed)); }
	else PRINT_PC("BEQ " << dec << "r" << rs << " " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif
	sdword local_rs = r[rs];
	sdword local_rt = r[rt];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	if (local_rs == local_rt)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BEQL(int rs, int rt, int immed)
{
#	if defined DEBUG
	if (!rt) { PRINT_PC("BEQLZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed)); }
	else PRINT_PC("BEQL " << dec << "r" << rs << " " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif

	sdword local_rs = r[rs];
	sdword local_rt = r[rt];
	if (local_rs == local_rt)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BGEZ(int immed, int rs)
{
	PRINT_PC("BGEZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	if (local_rs >= 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BGEZAL(int immed, int rs)
{
#	if defined DEBUG
	if (!rs) { PRINT_PC("BAL"); }
	else PRINT_PC("BGEZAL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	r[31] = pc;
	if (local_rs >= 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BGEZALL(int immed, int rs)
{
	PRINT_PC("BGEZALL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs >= 0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		r[31] = pc;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BGEZL(int immed, int rs)
{
	PRINT_PC("BGEZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs >= 0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BGTZ(int rs, int immed)
{
	PRINT_PC("BGTZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	if (local_rs > 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BGTZL(int immed, int rs)
{
	PRINT_PC("BGTZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs > 0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BLEZ(int rs, int immed)
{
	PRINT_PC("BLEZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	if (local_rs <= 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BLEZL(int immed, int rs)
{
	PRINT_PC("BLEZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs <= 0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BLTZ(int immed, int rs)
{
	PRINT_PC("BLTZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	if (local_rs < 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BLTZAL(int immed, int rs)
{
	PRINT_PC("BLTZAL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	r[31] = pc;
	if (local_rs < 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BLTZALL(int immed, int rs)
{
	PRINT_PC("BLTZALL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs < 0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		r[31] = pc;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BLTZL(int immed, int rs)
{
	PRINT_PC("BLTZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs < 0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BNE(int rs, int rt, int immed)
{
#	if defined DEBUG
	if (!rt) { PRINT_PC("BNEZ " << dec << "r" << rs << " 0x" << hex << extend_sign_halfword(immed)); }
	else PRINT_PC("BNE " << dec << "r" << rs << " " << dec << "r" << rt << " 0x" << hex << extend_sign_halfword(immed));
#	endif

	dword local_rs = r[rs];
	dword local_rt = r[rt];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	if (local_rs != local_rt)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BNEL(int rs, int rt, int immed)
{
#	if defined DEBUG
	if (!rt) { PRINT_PC("BNELZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed)); }
	else PRINT_PC("BNEL " << dec << "r" << rs << " " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif

	dword local_rs = r[rs];
	dword local_rt = r[rt];
	if (local_rs != local_rt)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::J(int address)
{
	PRINT_PC("J " << address);

	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	pc = (pc & 0xF0000000) | ((address & 0x03FFFFFF) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::JAL(int address)
{
	PRINT_PC("JAL " << address);
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	r[31] = extend_sign_word(pc);
	pc = (pc & 0xF0000000) | ((address & 0x03FFFFFF) << 2);
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::JALR(int rs, int rd)
{
	PRINT_PC("JALR " << dec << "r" << rs << " " << dec << "r" << rd);

	dword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	r[rd] = extend_sign_word(pc);
	pc = local_rs;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::JR(int rs)
{
	PRINT_PC("JR " << dec << "r" << rs);

	dword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(MMU::read<word>((word) pc));
	delay_slot = false;
	pc = local_rs;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BREAK(int immed)
{
	PRINT_PC("SYSCALL " << extend_sign_halfword(immed));
	trigger_break_exception();
}

inline void R4300i::SYSCALL(int immed)
{
	PRINT_PC("SYSCALL " << hex << "0x" << extend_sign_halfword(immed));
	trigger_syscall_exception();
}

inline void R4300i::TEQ(int rs, int rt)
{
	PRINT_PC("TEQ " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

inline void R4300i::TEQI(int rs, int immed)
{
	PRINT_PC("TEQI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

inline void R4300i::TGE(int rs, int rt)
{
	PRINT_PC("TGE " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

inline void R4300i::TGEI(int rs, int immed)
{
	PRINT_PC("TGEI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

inline void R4300i::TGEIU(int rs, int immed)
{
	PRINT_PC("TGEIU " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

inline void R4300i::TGEU(int rs, int rt)
{
	PRINT_PC("TGEU " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

inline void R4300i::TLT(int rs, int rt)
{
	PRINT_PC("TLT " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

inline void R4300i::TLTI(int rs, int immed)
{
	PRINT_PC("TLTI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

inline void R4300i::TLTIU(int rs, int immed)
{
	PRINT_PC("TLTIU " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

inline void R4300i::TLTU(int rs, int rt)
{
	PRINT_PC("TLTU " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

inline void R4300i::TNE(int rs, int rt)
{
	PRINT_PC("TNE " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

inline void R4300i::TNEI(int rs, int immed)
{
	PRINT_PC("TNEI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

inline void R4300i::CACHE(int rt, int immed, int rs)
{
	PRINT_PC("CACHE " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	pc += 4;
}

static bool first_eret = true;

inline void R4300i::ERET(void)
{
	PRINT_PC("ERET");
	Status &= (Status & STATUS_ERL) ? ~STATUS_ERL : 0xFFFFFFFD;
	// Workaround to clear the ExCode after we triggered an exception
	Cause &= ~CAUSE_ExcCode;
	//
	pc = (Status & STATUS_ERL) ? ErrorEpc : Epc;
	ll = 0;
	check_interrupt();

	// Workaround to trigger the PI timer that what supposed to occure
	// when we copied the first 0x1000 bytes of the ROM to the RAM
	if (first_eret)
	{
		first_eret = false;
		TimerHandler::force_pi_timer_done();
	}

	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::MFC0(int rt, int fs)
{
	PRINT_PC("MFC0 " << dec << "r" << rt << " " << dec << "cop0" << fs);
	r[rt] = extend_sign_word(cop0[fs]);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::MTC0(int rt, int fs)
{
	PRINT_PC("MTC0 " << dec << "r" << rt << " " << dec << "cop0" << fs);

	switch(fs)
	{
	case 0:    // Index
		Index = r[rt] & 0x8000003F;
		if ((Index & 0x3F) > 31) 
			cout << print_addr((word) pc) << " il y a plus de 32 TLB";
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
		Wired = r[rt] & 0xFFFFFFFF;
		Random = 31;
		break;
	case 8:    // BadVAddr
		break;
	case 9:    // Count
		UPDATE_TIME();
		Count = r[rt] & 0xFFFFFFFF;
		TimerHandler::change_compare_timer();
		break;
	case 10:   // EntryHi
		EntryHi = r[rt] & 0xFFFFE0FF;
		break;
	case 11:   // Compare
		Compare = r[rt] & 0xFFFFFFFF;
		Cause = Cause & 0xFFFFFFFFFFFF7FFF; //Timer interupt is clear
		TimerHandler::change_compare_timer();
		break;
	case 12:   // Status
		Status = r[rt] & 0xFFFFFFFF;
		UPDATE_TIME();
		//		check_interupt();
		break;
	case 13:   // Cause
		Cause = r[rt] & 0xFFFFFFFF;
		break;
	case 14:   // Epc
		Epc = r[rt] & 0xFFFFFFFF;
		break;
	case 15:  // PRevID
		break;
	case 16:  // Config
		Config = r[rt] & 0xFFFFFFFF;
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
		TagHi = 0;
		break;
	default:
		cout << endl << "Unknown mtc0 MMU::write";
	}
	pc += 4;
}

inline void R4300i::TLBP(void)
{
	PRINT_PC("TLBP");
	//	int i;
	Index = 0x80000000;
	/*  for (i = 0; i < 32; i++)
	{
	if (((MMU::tlb[i].vpn2 & (~MMU::tlb[i].mask)) ==
	(((EntryHi & 0xFFFFE000) >> 13) & (~MMU::tlb[i].mask))) &&
	((MMU::tlb[i].g) ||
	(MMU::tlb[i].asid == (EntryHi & 0xFF))))
	{
	cout << hex << "vpn2 " << MMU::tlb[i].vpn2 << " ~mask " << (~MMU::tlb[i].mask) << " EntryHi " << ((EntryHi & 0xFFFFE000) >> 13) << " g " << (MMU::tlb[i].g) << " asid " << MMU::tlb[i].asid << endl;
	Index = i;
	break;
	}
	}*/
	pc += 4;
}

inline void R4300i::TLBR(void)
{  
	PRINT_PC("TLBR");
	int index;
	index = Index & 0x1F;
	PageMask = MMU::tlb[index].mask << 13;
	EntryHi = ((MMU::tlb[index].vpn2 << 13) | MMU::tlb[index].asid);
	EntryLo0 = (MMU::tlb[index].pfn0 << 6) | (MMU::tlb[index].c0 << 3)
		| (MMU::tlb[index].d0 << 2) | (MMU::tlb[index].v0 << 1)
		| MMU::tlb[index].g;
	EntryLo1 = (MMU::tlb[index].pfn1 << 6) | (MMU::tlb[index].c1 << 3)
		| (MMU::tlb[index].d1 << 2) | (MMU::tlb[index].v1 << 1)
		| MMU::tlb[index].g;
	pc += 4;
}

inline void R4300i::TLBWI(void)
{
	PRINT_PC("TLBWI");
	unsigned int i;
	if (MMU::tlb[Index&0x3F].v0)
	{
		for (i=MMU::tlb[Index&0x3F].start0; i<MMU::tlb[Index&0x3F].end0; i++)
		{
			MMU::tlb_lut_r[i>>12] = 0;
			MMU::invalid_code[i>>12] = 1;
		}
		if (MMU::tlb[Index&0x3F].d0)
			for (i=MMU::tlb[Index&0x3F].start0; i<MMU::tlb[Index&0x3F].end0; i++)
				MMU::tlb_lut_w[i>>12] = 0;
	}
	if (MMU::tlb[Index&0x3F].v1)
	{
		for (i=MMU::tlb[Index&0x3F].start1; i<MMU::tlb[Index&0x3F].end1; i++)
		{
			MMU::tlb_lut_r[i>>12] = 0;
			MMU::invalid_code[i>>12] = 1;
		}
		if (MMU::tlb[Index&0x3F].d1)
			for (i=MMU::tlb[Index&0x3F].start1; i<MMU::tlb[Index&0x3F].end1; i++)
				MMU::tlb_lut_w[i>>12] = 0;
	}
	MMU::tlb[Index&0x3F].g = (EntryLo0 & EntryLo1 & 1);
	MMU::tlb[Index&0x3F].pfn0 = (EntryLo0 & 0x3FFFFFC0) >> 6;
	MMU::tlb[Index&0x3F].pfn1 = (EntryLo1 & 0x3FFFFFC0) >> 6;
	MMU::tlb[Index&0x3F].c0 = (EntryLo0 & 0x38) >> 3;
	MMU::tlb[Index&0x3F].c1 = (EntryLo1 & 0x38) >> 3;
	MMU::tlb[Index&0x3F].d0 = (EntryLo0 & 0x4) >> 2;
	MMU::tlb[Index&0x3F].d1 = (EntryLo1 & 0x4) >> 2;
	MMU::tlb[Index&0x3F].v0 = (EntryLo0 & 0x2) >> 1;
	MMU::tlb[Index&0x3F].v1 = (EntryLo1 & 0x2) >> 1;
	MMU::tlb[Index&0x3F].asid = (EntryHi & 0xFF);
	MMU::tlb[Index&0x3F].vpn2 = (EntryHi & 0xFFFFE000) >> 13;
	MMU::tlb[Index&0x3F].r = (EntryHi & 0xC000000000000000LL) >> 62;
	MMU::tlb[Index&0x3F].mask = (PageMask & 0x1FFE000) >> 13;

	MMU::tlb[Index&0x3F].start0 = MMU::tlb[Index&0x3F].vpn2 << 13;
	MMU::tlb[Index&0x3F].end0 = MMU::tlb[Index&0x3F].start0+
		(MMU::tlb[Index&0x3F].mask << 12) + 0xFFF;
	MMU::tlb[Index&0x3F].phys0 = MMU::tlb[Index&0x3F].pfn0 << 12;

	if (MMU::tlb[Index&0x3F].v0)
	{
		if (MMU::tlb[Index&0x3F].start0 < MMU::tlb[Index&0x3F].end0 &&
			!(MMU::tlb[Index&0x3F].start0 >= 0x80000000 &&
			MMU::tlb[Index&0x3F].end0 < 0xC0000000) &&
			MMU::tlb[Index&0x3F].phys0 < 0x20000000)
		{
			for (i=MMU::tlb[Index&0x3F].start0;i<MMU::tlb[Index&0x3F].end0;i++)
				MMU::tlb_lut_r[i>>12] = 0x80000000 | 
				(MMU::tlb[Index&0x3F].phys0 + (i - MMU::tlb[Index&0x3F].start0));
			if (MMU::tlb[Index&0x3F].d0)
				for (i=MMU::tlb[Index&0x3F].start0;i<MMU::tlb[Index&0x3F].end0;i++)
					MMU::tlb_lut_w[i>>12] = 0x80000000 | 
					(MMU::tlb[Index&0x3F].phys0 + (i - MMU::tlb[Index&0x3F].start0));
		}
	}
	MMU::tlb[Index&0x3F].start1 = MMU::tlb[Index&0x3F].end0+1;
	MMU::tlb[Index&0x3F].end1 = MMU::tlb[Index&0x3F].start1+
		(MMU::tlb[Index&0x3F].mask << 12) + 0xFFF;
	MMU::tlb[Index&0x3F].phys1 = MMU::tlb[Index&0x3F].pfn1 << 12;

	if (MMU::tlb[Index&0x3F].v1)
	{
		if (MMU::tlb[Index&0x3F].start1 < MMU::tlb[Index&0x3F].end1 &&
			!(MMU::tlb[Index&0x3F].start1 >= 0x80000000 &&
			MMU::tlb[Index&0x3F].end1 < 0xC0000000) &&
			MMU::tlb[Index&0x3F].phys1 < 0x20000000)
		{
			for (i=MMU::tlb[Index&0x3F].start1;i<MMU::tlb[Index&0x3F].end1;i++)
				MMU::tlb_lut_r[i>>12] = 0x80000000 | 
				(MMU::tlb[Index&0x3F].phys1 + (i - MMU::tlb[Index&0x3F].start1));
			if (MMU::tlb[Index&0x3F].d1)
				for (i=MMU::tlb[Index&0x3F].start1;i<MMU::tlb[Index&0x3F].end1;i++)
					MMU::tlb_lut_w[i>>12] = 0x80000000 | 
					(MMU::tlb[Index&0x3F].phys1 + (i - MMU::tlb[Index&0x3F].start1));
		}
	}
	pc += 4;
}

inline void R4300i::TLBWR(void)
{
	PRINT_PC("TLBWR");
	unsigned int i;
	UPDATE_TIME();
	Random = (Count/2 % (32 - Wired)) + Wired;
	if (MMU::tlb[Random].v0)
	{
		for (i=MMU::tlb[Random].start0; i<MMU::tlb[Random].end0; i++)
		{
			MMU::tlb_lut_r[i>>12] = 0;
			MMU::invalid_code[i>>12] = 1;
		}
		if (MMU::tlb[Random].d0)
			for (i=MMU::tlb[Random].start0; i<MMU::tlb[Random].end0; i++)
				MMU::tlb_lut_w[i>>12] = 0;
	}
	if (MMU::tlb[Random].v1)
	{
		for (i=MMU::tlb[Random].start1; i<MMU::tlb[Random].end1; i++)
		{
			MMU::tlb_lut_r[i>>12] = 0;
			MMU::invalid_code[i>>12] = 1;
		}
		if (MMU::tlb[Random].d1)
			for (i=MMU::tlb[Random].start1; i<MMU::tlb[Random].end1; i++)
				MMU::tlb_lut_w[i>>12] = 0;
	}
	MMU::tlb[Random].g = (EntryLo0 & EntryLo1 & 1);
	MMU::tlb[Random].pfn0 = (EntryLo0 & 0x3FFFFFC0) >> 6;
	MMU::tlb[Random].pfn1 = (EntryLo1 & 0x3FFFFFC0) >> 6;
	MMU::tlb[Random].c0 = (EntryLo0 & 0x38) >> 3;
	MMU::tlb[Random].c1 = (EntryLo1 & 0x38) >> 3;
	MMU::tlb[Random].d0 = (EntryLo0 & 0x4) >> 2;
	MMU::tlb[Random].d1 = (EntryLo1 & 0x4) >> 2;
	MMU::tlb[Random].v0 = (EntryLo0 & 0x2) >> 1;
	MMU::tlb[Random].v1 = (EntryLo1 & 0x2) >> 1;
	MMU::tlb[Random].asid = (EntryHi & 0xFF);
	MMU::tlb[Random].vpn2 = (EntryHi & 0xFFFFE000) >> 13;
	MMU::tlb[Random].r = (EntryHi & 0xC000000000000000LL) >> 62;
	MMU::tlb[Random].mask = (PageMask & 0x1FFE000) >> 13;

	MMU::tlb[Random].start0 = MMU::tlb[Random].vpn2 << 13;
	MMU::tlb[Random].end0 = MMU::tlb[Random].start0+
		(MMU::tlb[Random].mask << 12) + 0xFFF;
	MMU::tlb[Random].phys0 = MMU::tlb[Random].pfn0 << 12;

	if (MMU::tlb[Random].v0)
	{
		if (MMU::tlb[Random].start0 < MMU::tlb[Random].end0 &&
			!(MMU::tlb[Random].start0 >= 0x80000000 &&
			MMU::tlb[Random].end0 < 0xC0000000) &&
			MMU::tlb[Random].phys0 < 0x20000000)
		{
			for (i=MMU::tlb[Random].start0;i<MMU::tlb[Random].end0;i++)
				MMU::tlb_lut_r[i>>12] = 0x80000000 | 
				(MMU::tlb[Random].phys0 + (i - MMU::tlb[Random].start0));
			if (MMU::tlb[Random].d0)
				for (i=MMU::tlb[Random].start0;i<MMU::tlb[Random].end0;i++)
					MMU::tlb_lut_w[i>>12] = 0x80000000 | 
					(MMU::tlb[Random].phys0 + (i - MMU::tlb[Random].start0));
		}
	}
	MMU::tlb[Random].start1 = MMU::tlb[Random].end0+1;
	MMU::tlb[Random].end1 = MMU::tlb[Random].start1+
		(MMU::tlb[Random].mask << 12) + 0xFFF;
	MMU::tlb[Random].phys1 = MMU::tlb[Random].pfn1 << 12;

	if (MMU::tlb[Random].v1)
	{
		if (MMU::tlb[Random].start1 < MMU::tlb[Random].end1 &&
			!(MMU::tlb[Random].start1 >= 0x80000000 &&
			MMU::tlb[Random].end1 < 0xC0000000) &&
			MMU::tlb[Random].phys1 < 0x20000000)
		{
			for (i=MMU::tlb[Random].start1;i<MMU::tlb[Random].end1;i++)
				MMU::tlb_lut_r[i>>12] = 0x80000000 | 
				(MMU::tlb[Random].phys1 + (i - MMU::tlb[Random].start1));
			if (MMU::tlb[Random].d1)
				for (i=MMU::tlb[Random].start1;i<MMU::tlb[Random].end1;i++)
					MMU::tlb_lut_w[i>>12] = 0x80000000 | 
					(MMU::tlb[Random].phys1 + (i - MMU::tlb[Random].start1));
		}
	}
	pc += 4;
}

template<>
inline void R4300i::ABS <s> (int fd, int fs)
{
	PRINT_PC("ABS " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION()
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = fabs(*reg_cop1_simple[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::ABS <d> (int fd, int fs)
{
	PRINT_PC("ABS " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = fabs(*reg_cop1_double[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::ABS(int fd, int fs)
{
	PRINT_PC("ABS " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "ABS type not handle";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::ADD <s> (int fd, int fs, int ft)
{
	PRINT_PC("ADD " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = *reg_cop1_simple[fs] + *reg_cop1_simple[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::ADD <d> (int fd, int fs, int ft)
{
	PRINT_PC("ADD " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = *reg_cop1_double[fs] + *reg_cop1_double[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::ADD(int fd, int fs, int ft)
{
	PRINT_PC("ADD " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	cerr << "ADD type not handle";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

inline void R4300i::BC1F(int immed)
{
	PRINT_PC("BC1F " << hex << "0x" << extend_sign_halfword(immed));
	TEST_COP1_USABLE_EXCEPTION();
	dword pc_tmp = pc + extend_sign_halfword(immed);
	pc += 4;
	delay_slot = 1;
	decode(MMU::read<word>((word) pc));
	UPDATE_TIME();
	delay_slot = 0;
	if ((fcr31 & 0x800000)==0)
		pc = pc_tmp;
	else
		pc += 4;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BC1FL(int immed)
{
	PRINT_PC("BC1FL " << hex << "0x" << extend_sign_halfword(immed));
	TEST_COP1_USABLE_EXCEPTION();
	dword pc_tmp = pc + extend_sign_halfword(immed);
	if ((fcr31 & 0x800000)==0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		UPDATE_TIME();
		delay_slot = false;
		pc = pc_tmp;
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();	
}

inline void R4300i::BC1T(int immed)
{
	PRINT_PC("BC1T " << hex << "0x" << extend_sign_halfword(immed));
	TEST_COP1_USABLE_EXCEPTION();
	dword pc_tmp = pc + extend_sign_halfword(immed);
	pc += 4;
	delay_slot = 1;
	decode(MMU::read<word>((word) pc));
	UPDATE_TIME();
	delay_slot = 0;
	if ((fcr31 & 0x800000)!=0)
		pc = pc_tmp;
	else
		pc += 4;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

inline void R4300i::BC1TL(int immed)
{
	PRINT_PC("BC1TL " << hex << "0x" << extend_sign_halfword(immed));
	TEST_COP1_USABLE_EXCEPTION();
	dword pc_tmp = pc + extend_sign_halfword(immed);
	if ((fcr31 & 0x800000) != 0)
	{
		pc += 4;
		delay_slot = true;
		decode(MMU::read<word>((word) pc));
		UPDATE_TIME();
		delay_slot = false;
		pc = pc_tmp;
	}
	else
		pc += 8;
	CHECK_TIMER();
	CHECK_INTERRUPT();
}

template<typename Type>
inline void R4300i::C(int fs, int ft, int cond)
{
	PRINT_PC("C " << dec << "f" << fs << " " << dec << "f" << ft << " " << dec << "cond " << cond);
	TEST_COP1_USABLE_EXCEPTION();
	switch (cond) {
	case 0:
		F<Type>(fs, ft);
		break;
	case 1:
		UN<Type>(fs, ft);
		break;
	case 2:
		EQ<Type>(fs, ft);
		break;
	case 3:
		UEQ<Type>(fs, ft);
		break;
	case 4:
		OLT<Type>(fs, ft);
		break;
	case 5:
		ULT<Type>(fs, ft);
		break;
	case 6:
		OLE<Type>(fs, ft);
		break;
	case 7:
		ULE<Type>(fs, ft);
		break;
	case 8:
		SF<Type>(fs, ft);
		break;
	case 9:
		NGLE<Type>(fs, ft);
		break;
	case 10:
		SEQ<Type>(fs, ft);
		break;
	case 11:
		NGL<Type>(fs, ft);
		break;
	case 12:
		LT<Type>(fs, ft);
		break;
	case 13:
		NGE<Type>(fs, ft);
		break;
	case 14:
		LE<Type>(fs, ft);
		break;
	case 15:
		NGT<Type>(fs, ft);
		break;
	default:
		cout << endl << "Unknown Condition";
		break;
	}
	pc += 4;
}

template<>
inline void R4300i::CEIL<s, l> (int fd, int fs)
{
	PRINT_PC("CEIL " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(ceil_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CEIL<d, l> (int fd, int fs)
{
	PRINT_PC("CEIL " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(ceil_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CEIL<s, w> (int fd, int fs)
{
	PRINT_PC("CEIL " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(ceil_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CEIL<d, w> (int fd, int fs)
{
	PRINT_PC("CEIL " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(ceil_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type, typename toType>
inline void R4300i::CEIL(int fd, int fs)
{
	PRINT_PC("CEIL " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "CEIL type not handle"
		PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

inline void R4300i::CFC1(int rt, int fs)
{
	PRINT_PC("CFC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	if (fs == 0)
		r[rt] = extend_sign_word(fcr0);
	else
		r[rt] = extend_sign_word(fcr31);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::CTC1(int rt, int fs)
{
	PRINT_PC("CTC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	if (fs = 31)
		fcr31 = r[rt] & 0xFFFFFFFF;
	switch((fcr31 & 3))
	{
	case 0:
		rounding_mode = 0x33F;
		break;
	case 1:
		rounding_mode = 0xF3F;
		break;
	case 2:
		rounding_mode = 0xB3F;
		break;
	case 3:
		rounding_mode = 0x73F;
		break;
	}
	PRINT_PC(" f" << dec << fs << hex << "=0x" << f[fs]);
	pc += 4;
}

template<>
inline void R4300i::CVT<s, d> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<s, w> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*((long *)reg_cop1_simple[fd]) = (long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<s, l> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*((long long *)reg_cop1_double[fd]) = (long long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<d, s> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = (float) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<d, w> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*((long *)reg_cop1_simple[fd]) = (long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<d, l> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*((long long *)reg_cop1_double[fd]) = (long long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<w, s> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = (float) *((long *)reg_cop1_simple[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<w, d> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = *((long *)reg_cop1_simple[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<w, l> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*((long long *)reg_cop1_double[fd]) = *((long *)reg_cop1_double[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<l, s> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = (float) *((long long *)reg_cop1_double[fd]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<l, d> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = (double) *((long long *)reg_cop1_double[fd]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::CVT<l, w> (int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*((long *)reg_cop1_simple[fd]) = (long) *((long long *)reg_cop1_double[fd]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type, typename toType>
inline void R4300i::CVT(int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	cerr << "CVT not define for this combinaison of type";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::DIV<s> (int fd, int fs, int ft)
{
	PRINT_PC("DIV " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	TEST_COP1_USABLE_EXCEPTION();
	*reg_cop1_simple[fd] = *reg_cop1_simple[fs] / *reg_cop1_simple[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::DIV <d> (int fd, int fs, int ft)
{
	PRINT_PC("DIV " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	TEST_COP1_USABLE_EXCEPTION();
	*reg_cop1_double[fd] = *reg_cop1_double[fs] / *reg_cop1_double[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::DIV(int fd, int fs, int ft)
{
	PRINT_PC("DIV " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	cerr << "DIV type undefine";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

inline void R4300i::DMFC1(int rt, int fs)
{
	PRINT_PC("DMFC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	r[rt] = *((long long*)(reg_cop1_double[fs]));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

inline void R4300i::DMTC1(int rt, int fs)
{
	PRINT_PC("DMTC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	*((long long*)reg_cop1_double[fs]) = r[rt];
	PRINT_PC(" f" << dec << fs << hex << "=0x" << f[fs]);
	pc += 4;
}

template<>
inline void R4300i::FLOOR<s, l> (int fd, int fs)
{
	PRINT_PC("FLOOR " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(floor_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::FLOOR<d, l> (int fd, int fs)
{
	PRINT_PC("FLOOR " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(floor_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::FLOOR<s, w> (int fd, int fs)
{
	PRINT_PC("FLOOR " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(floor_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::FLOOR<d, w> (int fd, int fs)
{
	PRINT_PC("FLOOR " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(floor_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type, typename toType>
inline void R4300i::FLOOR(int fd, int fs)
{
	PRINT_PC("FLOOR " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "FLOOR type not define";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

inline void R4300i::LDC1(int ft, int immed, int rs)
{
	PRINT_PC("LDC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	TEST_COP1_USABLE_EXCEPTION();
	*((long long*)reg_cop1_double[ft]) = MMU::read<dword>((word) (r[rs] + extend_sign_halfword(immed)));
	PRINT_PC(" f" << dec << ft << hex << "=0x" << f[ft]);
	pc += 4;
}

inline void R4300i::LWC1(int ft, int immed, int rs)
{
	PRINT_PC("LWC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	TEST_COP1_USABLE_EXCEPTION();
	*((long*)reg_cop1_simple[ft]) = MMU::read<word>((word) (r[rs] + extend_sign_halfword(immed)));
	PRINT_PC(" f" << dec << ft << hex << "=0x" << f[ft]);
	pc += 4;
}

inline void R4300i::MFC1(int rt, int fs)
{
	PRINT_PC("MFC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	r[rt] = extend_sign_word(*((long*)reg_cop1_simple[fs]));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

template<>
inline void R4300i::MOV<s> (int fd, int fs)
{
	PRINT_PC("MOV " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	reg_cop1_simple[fd] = reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::MOV<d> (int fd, int fs)
{
	PRINT_PC("MOV " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	reg_cop1_double[fd] = reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::MOV(int fd, int fs)
{
	PRINT_PC("MOV " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "MOV type not handle";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

inline void R4300i::MTC1(int rt, int fs)
{
	PRINT_PC("MTC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	*((long*)reg_cop1_simple[fs]) = r[rt] & 0xFFFFFFFF;
	PRINT_PC(" f" << dec << fs << hex << "=0x" << f[fs]);
	pc += 4;
}

template<>
inline void R4300i::MUL<s> (int fd, int fs, int ft)
{
	PRINT_PC("MUL " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = *reg_cop1_simple[fs] * *reg_cop1_simple[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::MUL<d> (int fd, int fs, int ft)
{
	PRINT_PC("MUL " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = *reg_cop1_double[fs] * *reg_cop1_double[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::MUL(int fd, int fs, int ft)
{
	PRINT_PC("MUL " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	cerr << "MUL type not handle";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::NEG<s> (int fd, int fs)
{
	PRINT_PC("NEG " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = -(*reg_cop1_simple[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::NEG<d> (int fd, int fs)
{
	PRINT_PC("NEG " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = -(*reg_cop1_double[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::NEG(int fd, int fs)
{
	PRINT_PC("NEG " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "NEG type not handle";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::ROUND<s, l> (int fd, int fs)
{
	PRINT_PC("ROUND " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(round_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::ROUND<d, l> (int fd, int fs)
{
	PRINT_PC("ROUND " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(round_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::ROUND<s, w> (int fd, int fs)
{
	PRINT_PC("ROUND " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(round_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::ROUND<d, w> (int fd, int fs)
{
	PRINT_PC("ROUND " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(round_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type, typename toType>
inline void R4300i::ROUND(int fd, int fs)
{
	PRINT_PC("ROUND " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "ROUND type not handle";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

inline void R4300i::SDC1(int ft, int immed, int rs)
{
	PRINT_PC("SDC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	TEST_COP1_USABLE_EXCEPTION();
	MMU::write<dword>(*((unsigned long long*)reg_cop1_double[ft]), (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

template<>
inline void R4300i::SQRT<s> (int fd, int fs)
{
	PRINT_PC("SQRT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = sqrt(*reg_cop1_simple[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::SQRT<d>(int fd, int fs)
{
	PRINT_PC("SQRT " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	*reg_cop1_double[fd] = sqrt(*reg_cop1_double[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::SQRT(int fd, int fs)
{
	PRINT_PC("SQRT " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "SQRT type not define";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::SUB<s> (int fd, int fs, int ft)
{
	PRINT_PC("SUB " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_simple[fd] = *reg_cop1_simple[fs] - *reg_cop1_simple[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::SUB<d> (int fd, int fs, int ft)
{
	PRINT_PC("SUB " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	_controlfp(rounding_mode, _MCW_RC);
	*reg_cop1_double[fd] = *reg_cop1_double[fs] - *reg_cop1_double[ft];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::SUB(int fd, int fs, int ft)
{
	PRINT_PC("SUB " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	cerr << "SUB type not define";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

inline void R4300i::SWC1(int ft, int immed, int rs)
{
	PRINT_PC("SWC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	TEST_COP1_USABLE_EXCEPTION();
	MMU::write<word>(*((long*)reg_cop1_simple[ft]), (word) (r[rs] + extend_sign_halfword(immed)));
	pc += 4;
}

template<>
inline void R4300i::TRUNC<s, l>(int fd, int fs)
{
	PRINT_PC("TRUNC " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(trunc_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::TRUNC<d, l>(int fd, int fs)
{
	PRINT_PC("TRUNC " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(trunc_mode, _MCW_RC);
	*((long long*)(reg_cop1_double[fd])) = (long long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::TRUNC<s, w>(int fd, int fs)
{
	PRINT_PC("TRUNC " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(trunc_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_simple[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
inline void R4300i::TRUNC<d, w>(int fd, int fs)
{
	PRINT_PC("TRUNC " << dec << "f" << fd << " " << dec << "f" << fs);
	TEST_COP1_USABLE_EXCEPTION();
	_controlfp(trunc_mode, _MCW_RC);
	*((long *)(reg_cop1_simple[fd])) = (long) *reg_cop1_double[fs];
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type, typename toType>
inline void R4300i::TRUNC(int fd, int fs)
{
	PRINT_PC("TRUNC " << dec << "f" << fd << " " << dec << "f" << fs);
	cerr << "TRUNC type not handle";
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
inline void R4300i::F(int fs, int ft)
{
	fcr31 &= ~0x800000;
}

template<>
inline void R4300i::UN<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::UN<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::UN(int fs, int ft)
{
	cerr << "C UN type not define";
}

template<>
inline void R4300i::EQ<s> (int fs, int ft)
{
	if (!_isnan(*reg_cop1_simple[fs]) && !_isnan(*reg_cop1_simple[ft]) && *reg_cop1_simple[fs] == *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::EQ<d> (int fs, int ft)
{
	if (!_isnan(*reg_cop1_double[fs]) && !_isnan(*reg_cop1_double[ft]) && *reg_cop1_double[fs] == *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::EQ(int fs, int ft)
{
	cerr << "C EQ type not handle";
}

template<>
inline void R4300i::UEQ<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]) || *reg_cop1_simple[fs] == *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::UEQ<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]) || *reg_cop1_double[fs] == *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::UEQ(int fs, int ft)
{
	cerr << "C UEQ type not handle";
}

template<>
inline void R4300i::OLT<s> (int fs, int ft)
{
	if (!_isnan(*reg_cop1_simple[fs]) && !_isnan(*reg_cop1_simple[ft]) && *reg_cop1_simple[fs] < *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::OLT <d>(int fs, int ft)
{
	if (!_isnan(*reg_cop1_double[fs]) && !_isnan(*reg_cop1_double[ft]) && *reg_cop1_double[fs] < *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::OLT(int fs, int ft)
{
	cerr << "C OLT type not handle";
}

template<>
inline void R4300i::ULT<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]) || *reg_cop1_simple[fs] < *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::ULT<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]) || *reg_cop1_double[fs] < *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::ULT(int fs, int ft)
{
	cerr << "C ULT type not handle";
}

template<>
inline void R4300i::OLE<s> (int fs, int ft)
{
	if (!_isnan(*reg_cop1_simple[fs]) && !_isnan(*reg_cop1_simple[ft]) && *reg_cop1_simple[fs] <= *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::OLE<d> (int fs, int ft)
{
	if (!_isnan(*reg_cop1_double[fs]) && !_isnan(*reg_cop1_double[ft]) && *reg_cop1_double[fs] <= *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::OLE(int fs, int ft)
{
	cerr << "C OLE type not handle";
}

template<>
inline void R4300i::ULE<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]) || *reg_cop1_simple[fs] <= *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::ULE<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]) || *reg_cop1_double[fs] <= *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::ULE(int fs, int ft)
{
	PRINT_PC("C ULE type not handle");
}

template<>
inline void R4300i::SF<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	fcr31 &= ~0x800000;
}

template<>
inline void R4300i::SF<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::SF(int fs, int ft)
{
	PRINT_PC("C SF type not handle");
}

template<>
inline void R4300i::NGLE<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	fcr31 &= ~0x800000;
}

template<>
inline void R4300i::NGLE<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::NGLE(int fs, int ft)
{
	PRINT_PC("C NGLE type noy handle");
}

template<>
inline void R4300i::SEQ<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	if (*reg_cop1_simple[fs] == *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::SEQ<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	if (*reg_cop1_double[fs] == *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::SEQ(int fs, int ft)
{
	PRINT_PC("C SEQ type not handle");
}

template<>
inline void R4300i::NGL<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	if (*reg_cop1_simple[fs] == *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::NGL<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	if (*reg_cop1_double[fs] == *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::NGL(int fs, int ft)
{
	PRINT_PC("C NGL type not handle");
}

template<>
inline void R4300i::LT<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC("Invalid operation exception in C opcode");
	if (*reg_cop1_simple[fs] < *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::LT<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	if (*reg_cop1_double[fs] < *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::LT(int fs, int ft)
{
	PRINT_PC("C LT type not handle");
}

template<>
inline void R4300i::NGE<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC(" Invalid operation exception in C opcode");
	if (*reg_cop1_simple[fs] < *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::NGE<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC("Invalid operation exception in C opcode");
	if (*reg_cop1_double[fs] < *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::NGE(int fs, int ft)
{
	PRINT_PC("C NGE type not handle");
}

template<>
inline void R4300i::LE<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC("Invalid operation exception in C opcode");
	if (*reg_cop1_simple[fs] <= *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::LE<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC("Invalid operation exception in C opcode");
	if (*reg_cop1_double[fs] <= *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::LE(int fs, int ft)
{
	PRINT_PC("C LE type not handle");
}

template<>
inline void R4300i::NGT<s> (int fs, int ft)
{
	if (_isnan(*reg_cop1_simple[fs]) || _isnan(*reg_cop1_simple[ft]))
		PRINT_PC("Invalid operation exception in C opcode");
	if (*reg_cop1_simple[fs] <= *reg_cop1_simple[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<>
inline void R4300i::NGT<d> (int fs, int ft)
{
	if (_isnan(*reg_cop1_double[fs]) || _isnan(*reg_cop1_double[ft]))
		PRINT_PC("Invalid operation exception in C opcode");
	if (*reg_cop1_double[fs] <= *reg_cop1_double[ft])
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
inline void R4300i::NGT(int fs, int ft)
{
	PRINT_PC("C NGT type not handle");
}

inline int R4300i::probe_nop(word address)
{
	word a;
	address = (word) address;
	if (address < 0x80000000 || address > 0xc0000000)
	{
		if (MMU::tlb_lut_r[address >> 12])
			a = (MMU::tlb_lut_r[address >> 12] & 0xFFFFF000) | (address & 0xFFF);
		else
			return 0;
	}
	else
		a = (word) address;

	if ((a >= 0xa4000000 && a < 0xa4001000) || (a >= 0x80000000 && a < 0x80800000))
	{
		if (!MMU::read<word>(a)) return 1;
		else return 0;
	}
	else return 0;
}