#pragma once
#include "StdAfx.h"

class R4300i
{
public:
	R4300i(void);
	void decode(const word instr);
private:
	void decode_r(const word instr);

	//****************************************************************************
	//** Load and Store Instructions                                            **
	//****************************************************************************
	void LB           (int rt, int immed, int rs);	//  Load Byte
	void LBU          (int rt, int immed, int rs);	//  Load Byte Unsigned
	void LD           (int rt, int immed, int rs);	//  Load Doubleword
	void LDL          (int rt, int immed, int rs);	//  Load Doubleword Left
	void LDR          (int rt, int immed, int rs);	//  Load Doubleword Right
	void LH           (int rt, int immed, int rs);	//  Load Halfword
	void LHU          (int rt, int immed, int rs);	//  Load Halfword Unsigned
	void LL           (int rt, int immed, int rs);	//  Load Linked word
	void LLD          (int rt, int immed, int rs);	//  Load Linked Doubleword
	void LW           (int rt, int immed, int rs);	//  Load Word
	void LWL          (int rt, int immed, int rs);	//  Load Word Left
	void LWR          (int rt, int immed, int rs);	//  Load Word Right
	void LWU          (int rt, int immed, int rs);	//  Load Word Unsigned
	void SB           (int rt, int immed, int rs);	//  Store Byte
	void SC           (int rt, int immed, int rs);	//  Store Conditional word
	void SCD          (int rt, int immed, int rs);	//  Store Conditional Doubleword
	void SD           (int rt, int immed, int rs);	//  Store Doubleword
	void SDL          (int rt, int immed, int rs);	//  Store Doubleword Left
	void SDR          (int rt, int immed, int rs);	//  Store Doubleword Right
	void SH           (int rt, int immed, int rs);	//  Store Halfword
	void SW           (int rt, int immed, int rs);	//  Store Word
	void SWL          (int rt, int immed, int rs);	//  Store Word Left
	void SWR          (int rt, int immed, int rs);	//  Store Word Right
	void SYNC         (void);						//	SYNChronize shared memory
	//****************************************************************************
	//** Atithmetic Instructions                                                **
	//****************************************************************************
	void ADD          (int rd, int rs, int rt);		//	ADD word
	void ADDI         (int rt, int rs, int imm);		//	ADD Immediate word
	void ADDIU        (int rt, int rs, int imm);		//	Add Immediate Unsigned word
	void ADDU         (int rd, int rs, int rt);		//	Add Unsigned word
	void AND          (int rd, int rs, int rt);		//	AND
	void ANDI         (int rt, int rs, int imm);		//	AND Immediate
	void DADD         (int rd, int rs, int rt);		//	Doubleword ADD
	void DADDI        (int rt, int rs, int imm);		//	Doubleword ADD Immediate
	void DADDIU       (int rt, int rs, int imm);		//	Doubleword ADD Immediate Unsigned
	void DADDU        (int rd, int rs, int rt);		//	Doubleword ADD Unsigned
	void DDIV         (int rs, int rt);				//	Doubleword DIVide
	void DDIVU        (int rs, int rt);				//	Doubleword DIVide Unsigned
	void DIV          (int rs, int rt);				//	DIVide word
	void DIVU         (int rs, int rt);				//	DIVide Unsigned word
	void DMULT        (int rs, int rt);				//	Doubleword MULTiply
	void DMULTU       (int rs, int rt);				//	Doubleword MULTiply Unsigned
	void DSLL         (int rd, int rt, int sa);		//	Doubleword Shift Left Logical
	void DSLL32       (int rd, int rt, int sa);		//	Doubleword Shift Left Logical +32
	void DSLLV        (int rd, int rt, int rs);		//	Doubleword Shift Left Logical Variable
	void DSRA         (int rd, int rt, int sa);		//	Doubleword Shift Right Arithmetic
	void DSRA32       (int rd, int rt, int sa);		//	Doubleword Shift Right Arithmetic +32
	void DSRAV        (int rd, int rt, int rs);		//	Doubleword Shift Right Arithmetic Variable
	void DSRL         (int rd, int rt, int sa);		//	Doubleword Shift Right Logical
	void DSRL32       (int rd, int rt, int sa);		//	Doubleword Shift Right Logical +32
	void DSRLV        (int rd, int rt, int rs);		//	Doubleword Shift Right Logical Variable
	void DSUB         (int rd, int rs, int rt);		//	Doubleword SUBtract
	void DSUBU        (int rd, int rs, int rt);		//	Doubleword SUBtract Unsigned
	void LUI          (int rt, int imm);				//	Load Upper Immediate
	void MFHI         (int rd);						//	Move From HI register
	void MFLO         (int rd);						//	Move From LO register
	void MTHI         (int rd);						//	Move To HI register
	void MTLO         (int rd);						//	Move To LO register
	void MULT         (int rs, int rt);				//	MULTiply word
	void MULTU        (int rs, int rt);				//	MULTiply Unsigned word
	void NOR          (int rd, int rs, int rt);		//	Not OR
	void OR           (int rd, int rs, int rt);		//	OR
	void ORI          (int rt, int rs, int imm);		//	OR Immediate
	void SLL          (int rd, int rt, int sa);		//	Shift word Left Logical
	void SLLV         (int rd, int rt, int rs);		//	Shift word Left Logical Variable
	void SLT          (int rd, int rs, int rt);		//	Set on Less Than
	void SLTI         (int rt, int rs, int imm);		//	Set on Less Than Immediate
	void SLTIU        (int rt, int rs, int imm);		//	Set on Less Than Immediate Unsigned
	void SLTU         (int rd, int rs, int rt);		//	Set on Less Than Unsigned
	void SRA          (int rd, int rt, int sa);		//	Shift word Right Arithmetic
	void SRAV         (int rd, int rt, int rs);		//	Shift word Right Arithmetic Variable
	void SRL          (int rd, int rt, int sa);		//	Shift word Right Logical
	void SRLV         (int rd, int rt, int rs);		//	Shift word Right Logical Variable
	void SUB          (int rd, int rs, int rt);		//	SUBtract word
	void SUBU         (int rd, int rs, int rt);		//	SUBtract Unsigned word
	void XOR          (int rd, int rs, int rt);		//	eXclusive OR
	void XORI         (int rt, int rs, int imm);		//	eXclusive OR Immediate
	//****************************************************************************
	//** Jump and Branch Instructions                                           **
	//****************************************************************************
	void BEQ          (int rs, int rt, int immed);	//	Branch on =
	void BEQL         (int rs, int rt, int immed);	//	Branch on EQual Likely
	void BGEZ         (int immed, int rs);			//	Branch on >= Zero
	void BGEZAL       (int immed, int rs);			//	Branch on >= Zero And Link
	void BGEZALL      (int immed, int rs);			//	Branch on >= Zero And Link Likely
	void BGEZL        (int immed, int rs);			//	Branch on >= Equal to Zero Likely
	void BGTZ         (int immed, int rs);			//	Branch on > Zero
	void BGTZL        (int immed, int rs);			//	Branch on > Zero Likely
	void BLEZ         (int immed, int rs);			//	Branch on <= Equal to Zero
	void BLEZL        (int immed, int rs);			//	Branch on <= Zero Likely
	void BLTZ         (int immed, int rs);			//	Branch on < Zero
	void BLTZAL       (int immed, int rs);			//	Branch on < Zero And Link
	void BLTZALL      (int immed, int rs);			//	Branch on < Zero And Link Likely
	void BLTZL        (int immed, int rs);			//	Branch on < Zero Likely
	void BNE          (int rs, int rt, int immed);	//	Branch on <>
	void BNEL         (int rs, int rt, int immed);	//	Branch on <> Likely
	void J            (int address);					//	Jump
	void JAL          (int address);					//	Jump And Link
	void JALR         (int rs, int rd);				//	Jump And Link Register
	void JR           (int rs);						//	Jump Register
	//****************************************************************************
	//** Special Instructions                                                   **
	//****************************************************************************
	void BREAK        (int immed);					//	BREAKpoint
	void SYSCALL      (int immed);					//	SYStem CALL
	//****************************************************************************
	//** Exception Instructions                                                 **
	//****************************************************************************
	void TEQ          (int rs, int rt);				//	Trap if =
	void TEQI         (int rs, int imm);				//	Trap if = Immediate
	void TGE          (int rs, int rt);				//	Trap if >=
	void TGEI         (int rs, int imm);				//	Trap if >= Immediate
	void TGEIU        (int rs, int imm);				//	Trap if >= Immediate Unsigned
	void TGEU         (int rs, int rt);				//	Trap if >= Unsigned
	void TLT          (int rs, int rt);				//	Trap if <
	void TLTI         (int rs, int imm);				//	Trap if < Immediate
	void TLTIU        (int rs, int imm);				//	Trap if < Immediate Unsigned
	void TLTU         (int rs, int rt);				//	Trap if < Unsigned
	void TNE          (int rs, int rt);				//	Trap if <>
	void TNEI         (int rs, int imm);				//	Trap if <> Immediate
	//****************************************************************************
	//** System Control Processor (COP0); Instructions                           **
	//****************************************************************************
	void CACHE        (int op, int immed, int rs);	//	CACHE
	void ERET		  (void);						//	Return from Exception
	void MFC0         (int rt, int fs);				//	Move Word From CP0
	void MTC0         (int rt, int fs);				//	Move Word To CP0
	void TLBP		  (void);						//	Probe TLB for Matching Entry
	void TLBR		  (void);						//	Read Indexed TLB Entry
	void TLBWI		  (void);						//	Write Indexed TLB Entry
	void TLBWR		  (void);						//	Write Random TLB Entry
	//****************************************************************************
	//** Floating-point Unit, FPU (COP1); instructions                           **
	//****************************************************************************
	void ABS_fmt      (int fd, int fs);				//	floating-point ABSolute value
	void ADD_fmt      (int fd, int fs, int ft);		//	floating-point ADD
	void BC1F         (int immed);					//	Branch on FP False
	void BC1FL        (int immed);					//	Branch on FP False Likely
	void BC1T         (int immed);					//	Branch on FP True
	void BC1TL        (int immed);					//	Branch on FP True Likely
	void C_cond_fmt   (int fs, int ft);				//	floating-point floating point Compare
	void CEIL_L_fmt   (int fd, int fs);				//	floating-point CEILing convert to Long fixed-point
	void CEIL_W_fmt   (int fd, int fs);				//	floating-point CEILing convert to Word fixed-point
	void CFC1         (int rt, int fs);				//	Move control word From Floating-Point
	void CTC1         (int rt, int fs);				//	Move control word To Floating-Point
	void CVT_D_fmt    (int fd, int fs);				//	floating-point ConVerT to Double floating-point
	void CVT_L_fmt    (int fd, int fs);				//	floating-point ConVerT to Long fixed-point
	void CVT_S_fmt    (int fd, int fs);				//	floating-point ConVerT to Single floating-point
	void CVT_W_fmt    (int fd, int fs);				//	floating-point ConVerT to Word fixed-point
	void DIV_fmt      (int fd, int fs, int ft);		//	floating-point DIVide
	void DMFC1        (int rt, int fs);				//	Doubleword Move From Floating-Point
	void DMTC1        (int rt, int fs);				//	Doubleword Move To Floating-Point
	void FLOOR_L_fmt  (int fd, int fs);				//	floating-point FLOOR convert to Long fixed-point
	void FLOOR_W_fmt  (int fd, int fs);				//	floating-point FLOOR convert to Word fixed-point
	void LDC1         (int ft, int immed, int rs);	//	Load Doubleword to Floating-Point
	void LWC1         (int ft, int immed, int rs);	//	Load Word to Floating-Point
	void MFC1         (int rt, int fs);				//	Move Word From Floating-Point
	void MOV_fmt      (int fd, int fs);				//	floating-point MOVe
	void MTC1         (int rt, int fs);				//	Move Word To Floating-Point
	void MUL_fmt      (int fd, int fs, int ft);		//	floating-point MULtiply
	void NEG_fmt      (int fd, int fs);				//	floating-point NEGate
	void ROUND_L_fmt  (int fd, int fs);				//	floating-point ROUND to Long fixed-point
	void ROUND_W_fmt  (int fd, int fs);				//	floating-point ROUND to Word fixed-point
	void SDC1         (int ft, int immed, int rs);	//	Store Doubleword from Floating-Point
	void SQRT_fmt     (int fd, int fs);				//	floating-point SQuare RooT
	void SUB_fmt      (int fd, int fs, int ft);		//	floating-point SUBtract
	void SWC1         (int ft, int immed, int rs);	//	Store Word from Floating-Point
	void TRUNC_L_fmt  (int fd, int fs);				//	floating-point TRUNCate to Long fixed-point
	void TRUNC_W_fmt  (int fd, int fs);				//	floating-point TRUNCate to Word fixed-point
	//****************************************************************************
	//** Pseudo opcodes                                                         **
	//****************************************************************************
	void NOP          (void);						//	Assembles to SLL    r0, r0, 0
	void MOVE         (int rd, int rs);				//	Assembles to ADD    int rd, r0, rs
	void NEG          (int rd, int rt);				//	Assembles to SUB    int rd, r0, rt
	void NEGU         (int rd, int rs);				//	Assembles to SUBU   int rd, r0, rs
	void BNEZ         (int immed, int rs);			//	Assembles to BNE    (int rs, r0, immed
	void BNEZL        (int immed, int rs);			//	Assembles to BNEL   (int rs, r0, immed
	void BEQZ         (int immed, int rs);			//	Assembles to BEQ    (int rs, r0, immed
	void BEQZL        (int immed, int rs);			//	Assembles to BEQL   (int rs, r0, immed
	void B            (int immed);					//	Assembles to BEQ    r0, r0, immed
	void BAL          (int immed);					//	Assembles to BGEZAL r0, immed
	void LI           (int rt, int imm);				//	Assembles to ORI    rt, r0, imm (if imm is 16 bit);
	 												//						or ADDIU  rt, r0, imm
	 												//						or LUI    rt, high_16
													//						   ORI    rt, rt, low_16 (if imm is 32 bit);
	void S_S          (int ft, int immed, int rs);	//	Assembles to SWC1   ft, immed(rs);
	void L_S          (int ft, int immed, int rs);	//	Assembles to LWC1   ft, immed(rs);
};

