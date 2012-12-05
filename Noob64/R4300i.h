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

/*
 * The R4300i files contains the functions which concerns the emulation
 * of the R4300i processor. like the instructions, and the main loop of
 * the n64 emulator.
 *
 */

#pragma once

// Cop0 Macros
// Each entry of the co-processor 0 have a signification
// So we can rename each entry to have a better understanding of the code
#define INDEX		0
#define RANDOM		1
#define ENTRYLO0	2
#define ENTRYLO1	3
#define CONTEXT		4
#define PAGEMASK	5
#define WIRED		6
#define BADVADDR	8
#define COUNT		9
#define ENTRYHI		10
#define COMPARE		11
#define STATUS		12
#define CAUSE		13
#define EPC			14
#define PREVID		15
#define CONFIG		16
#define LLADDR		17
#define WATCHLO		18
#define WATCHHI		19
#define XCONTEXT	20
#define PERR		26
#define CACHEERR	27
#define TAGLO		28
#define TAGHI		29
#define ERROREPC	30

#define Index		cop0[INDEX]
#define Random		cop0[RANDOM]
#define EntryLo0	cop0[ENTRYLO0]
#define EntryLo1	cop0[ENTRYLO1]
#define Context		cop0[CONTEXT]
#define PageMask	cop0[PAGEMASK]
#define Wired		cop0[WIRED]
#define BadVAddr	cop0[BADVADDR]
#define Count		cop0[COUNT]
#define EntryHi		cop0[ENTRYHI]
#define Compare		cop0[COMPARE]
#define Status		cop0[STATUS]
#define Cause		cop0[CAUSE]
#define Epc			cop0[EPC]
#define PRevID		cop0[PREVID]
#define Config		cop0[CONFIG]
#define LLAddr		cop0[LLADDR]
#define WatchLo		cop0[WATCHLO]
#define WatchHi		cop0[WATCHHI]
#define XContext	cop0[XCONTEXT]
#define PErr		cop0[PERR]
#define CacheErr	cop0[CACHEERR]
#define TagLo		cop0[TAGLO]
#define TagHi		cop0[TAGHI]
#define ErrorEpc	cop0[ERROREPC]

//****************************************************************************
//** N64's PROCESSOR														**
//****************************************************************************
class R4300i
{
public:
	static void start(void);						// Initializes the R4300i and enter in the main loop
	static void reset(void);						// Clears bits
	static void check_interrupt(void);				// Checks if an interrupt has been triggered
	static void timer_done(void);					// Uses to see if a timer is done
	/* GETTERS */
	static inline word getCop0(int);
	/* SETTERS */
	static inline void setCop0(int, word);

private:
	void static pif_init(void); // Workaround to pass the CRC check which prevents a fake game from loading
	//****************************************************************************
	//** EXCEPTION PROCESSING UNIT												**
	//****************************************************************************
	bool static interrupt_detected;									// Notifies whether an interrupt has been detected or not
	void static trigger_address_error(word address, bool from_read);// Triggers an address error exception
	void static trigger_break_exception();							// Triggers a break exception
	void static trigger_copunusable_exception(int cop);				// Triggers a COP unusable exception
	void static trigger_intr_exception();							// Triggers an interruption exception
	void static trigger_tlb_miss(word address);						// Triggers a TLB missed exception
	void static trigger_syscall_exception();						// Triggers a syscall exception
	//****************************************************************************
	//** DECODER																**
	//****************************************************************************
	static inline void decode(const word instr);					// Decodes the given instruction
	static inline void decode_r(const word instr);					// Decodes the given R-typed instruction
	static inline void decode_i(const word instr);					// Decodes the given I-typed instruction
	static inline void decode_cop0(const word instr);				// Decodes the given COP0-typed instruction
	static inline void decode_tlb(const word instr);				// Decodes the given TLB-typed instruction
	static inline void decode_cop1(const word instr);				// Decodes the given COP1-typed instruction
	static inline void decode_bc1(const word instr);				// Decodes the given BC1-typed instruction
	template<typename Type>
	static inline void decode_fpu(const word instr);				// Decodes the given FPU-typed instruction
	static inline int probe_nop(word address);						// Checks whether the next instruction is a nop or not
	//****************************************************************************
	//** REGISTERS					                                            **
	//****************************************************************************
	// TODO: r[0] is always 0
	static dword	r[32];											// General Purpose Registers (GPRs)
	static dword	f[32];											// FP General Purpose Registers (FGRs)
	static double*	reg_cop1_double[32];
	static float*	reg_cop1_simple[32];
	static word		cop0[32];										// Cop0 registers
	static dword	pc;												// Program Counter
	static dword	hi, lo;											// Multiply/Divide result
	static word		fcr0, fcr31;									// Floating Point Control Registers
	static int		rounding_mode, trunc_mode, round_mode, ceil_mode, floor_mode;
	static bool		ll;												// Load/Link Register
	//****************************************************************************
	//** MISC																	**
	//****************************************************************************
	static bool	delay_slot;											// for branch instructions
	static bool	running;											// Status of the CPU
	static dword cic_chip;											// To hack the security check of the n64
	//****************************************************************************
	//** LOAD AND STORE INSTRUCTIONS                                            **
	//****************************************************************************
	static inline void LB			(int rt, int immed, int rs);	//  Load Byte
	static inline void LBU			(int rt, int immed, int rs);	//  Load Byte Unsigned
	static inline void LD			(int rt, int immed, int rs);	//  Load Doubleword
	static inline void LDL			(int rt, int immed, int rs);	//  Load Doubleword Left
	static inline void LDR			(int rt, int immed, int rs);	//  Load Doubleword Right
	static inline void LH			(int rt, int immed, int rs);	//  Load Halfword
	static inline void LHU			(int rt, int immed, int rs);	//  Load Halfword Unsigned
	static inline void LL			(int rt, int immed, int rs);	//  Load Linked word
	static inline void LLD			(int rt, int immed, int rs);	//  Load Linked Doubleword
	static inline void LW			(int rt, int immed, int rs);	//  Load Word
	static inline void LWL			(int rt, int immed, int rs);	//  Load Word Left
	static inline void LWR			(int rt, int immed, int rs);	//  Load Word Right
	static inline void LWU			(int rt, int immed, int rs);	//  Load Word Unsigned
	static inline void SB			(int rt, int immed, int rs);	//  Store Byte
	static inline void SC			(int rt, int immed, int rs);	//  Store Conditional word
	static inline void SCD			(int rt, int immed, int rs);	//  Store Conditional Doubleword
	static inline void SD			(int rt, int immed, int rs);	//  Store Doubleword
	static inline void SDL			(int rt, int immed, int rs);	//  Store Doubleword Left
	static inline void SDR			(int rt, int immed, int rs);	//  Store Doubleword Right
	static inline void SH			(int rt, int immed, int rs);	//  Store Halfword
	static inline void SW			(int rt, int immed, int rs);	//  Store Word
	static inline void SWL			(int rt, int immed, int rs);	//  Store Word Left
	static inline void SWR			(int rt, int immed, int rs);	//  Store Word Right
	static inline void SYNC			(void);							//	SYNChronize shared memory
	//****************************************************************************
	//** ATITHMETIC INSTRUCTIONS                                                **
	//****************************************************************************
	static inline void ADD			(int rd, int rs, int rt);		//	ADD word
	static inline void ADDI			(int rt, int rs, int immed);	//	ADD immediate word
	static inline void ADDIU		(int rt, int rs, int immed);	//	Add immediate Unsigned word
	static inline void ADDU			(int rd, int rs, int rt);		//	Add Unsigned word
	static inline void AND			(int rd, int rs, int rt);		//	AND
	static inline void ANDI			(int rt, int rs, int immed);	//	AND immediate
	static inline void DADD			(int rd, int rs, int rt);		//	Doubleword ADD
	static inline void DADDI		(int rt, int rs, int immed);	//	Doubleword ADD immediate
	static inline void DADDIU		(int rt, int rs, int immed);	//	Doubleword ADD immediate Unsigned
	static inline void DADDU		(int rd, int rs, int rt);		//	Doubleword ADD Unsigned
	static inline void DDIV			(int rs, int rt);				//	Doubleword DIVide
	static inline void DDIVU		(int rs, int rt);				//	Doubleword DIVide Unsigned
	static inline void DIV			(int rs, int rt);				//	DIVide word
	static inline void DIVU			(int rs, int rt);				//	DIVide Unsigned word
	static inline void DMULT		(int rs, int rt);				//	Doubleword MULTiply
	static inline void DMULTU		(int rs, int rt);				//	Doubleword MULTiply Unsigned
	static inline void DSLL			(int rd, int rt, int sa);		//	Doubleword Shift Left Logical
	static inline void DSLL32		(int rd, int rt, int sa);		//	Doubleword Shift Left Logical +32
	static inline void DSLLV		(int rd, int rt, int rs);		//	Doubleword Shift Left Logical Variable
	static inline void DSRA			(int rd, int rt, int sa);		//	Doubleword Shift Right Arithmetic
	static inline void DSRA32		(int rd, int rt, int sa);		//	Doubleword Shift Right Arithmetic +32
	static inline void DSRAV		(int rd, int rt, int rs);		//	Doubleword Shift Right Arithmetic Variable
	static inline void DSRL			(int rd, int rt, int sa);		//	Doubleword Shift Right Logical
	static inline void DSRL32		(int rd, int rt, int sa);		//	Doubleword Shift Right Logical +32
	static inline void DSRLV		(int rd, int rt, int rs);		//	Doubleword Shift Right Logical Variable
	static inline void DSUB			(int rd, int rs, int rt);		//	Doubleword SUBtract
	static inline void DSUBU		(int rd, int rs, int rt);		//	Doubleword SUBtract Unsigned
	static inline void LUI			(int rt, int immed);			//	Load Upper immediate
	static inline void MFHI			(int rd);						//	Move From HI register
	static inline void MFLO			(int rd);						//	Move From LO register
	static inline void MTHI			(int rs);						//	Move To HI register
	static inline void MTLO			(int rs);						//	Move To LO register
	static inline void MULT			(int rs, int rt);				//	MULTiply word
	static inline void MULTU		(int rs, int rt);				//	MULTiply Unsigned word
	static inline void NOR			(int rd, int rs, int rt);		//	Not OR
	static inline void OR			(int rd, int rs, int rt);		//	OR
	static inline void ORI			(int rt, int rs, int immed);	//	OR immediate
	static inline void SLL			(int rd, int rt, int sa);		//	Shift word Left Logical
	static inline void SLLV			(int rd, int rt, int rs);		//	Shift word Left Logical Variable
	static inline void SLT			(int rd, int rs, int rt);		//	Set on Less Than
	static inline void SLTI			(int rt, int rs, int immed);	//	Set on Less Than immediate
	static inline void SLTIU		(int rt, int rs, int immed);	//	Set on Less Than immediate Unsigned
	static inline void SLTU			(int rd, int rs, int rt);		//	Set on Less Than Unsigned
	static inline void SRA			(int rd, int rt, int sa);		//	Shift word Right Arithmetic
	static inline void SRAV			(int rd, int rt, int rs);		//	Shift word Right Arithmetic Variable
	static inline void SRL			(int rd, int rt, int sa);		//	Shift word Right Logical
	static inline void SRLV			(int rd, int rt, int rs);		//	Shift word Right Logical Variable
	static inline void SUB			(int rd, int rs, int rt);		//	SUBtract word
	static inline void SUBU			(int rd, int rs, int rt);		//	SUBtract Unsigned word
	static inline void XOR			(int rd, int rs, int rt);		//	eXclusive OR
	static inline void XORI			(int rt, int rs, int immed);	//	eXclusive OR immediate
	//****************************************************************************
	//** JUMP AND BRANCH INSTRUCTIONS                                           **
	//****************************************************************************
	static inline void BEQ			(int rs, int rt, int immed);	//	Branch on =
	static inline void BEQL			(int rs, int rt, int immed);	//	Branch on EQual Likely
	static inline void BGEZ			(int immed, int rs);			//	Branch on >= Zero
	static inline void BGEZAL		(int immed, int rs);			//	Branch on >= Zero And Link
	static inline void BGEZALL		(int immed, int rs);			//	Branch on >= Zero And Link Likely
	static inline void BGEZL		(int immed, int rs);			//	Branch on >= Equal to Zero Likely
	static inline void BGTZ			(int immed, int rs);			//	Branch on > Zero
	static inline void BGTZL		(int immed, int rs);			//	Branch on > Zero Likely
	static inline void BLEZ			(int immed, int rs);			//	Branch on <= Equal to Zero
	static inline void BLEZL		(int immed, int rs);			//	Branch on <= Zero Likely
	static inline void BLTZ			(int immed, int rs);			//	Branch on < Zero
	static inline void BLTZAL		(int immed, int rs);			//	Branch on < Zero And Link
	static inline void BLTZALL		(int immed, int rs);			//	Branch on < Zero And Link Likely
	static inline void BLTZL		(int immed, int rs);			//	Branch on < Zero Likely
	static inline void BNE			(int rs, int rt, int immed);	//	Branch on <>
	static inline void BNEL			(int rs, int rt, int immed);	//	Branch on <> Likely
	static inline void J			(int address);					//	Jump
	static inline void JAL			(int address);					//	Jump And Link
	static inline void JALR			(int rs, int rd);				//	Jump And Link Register
	static inline void JR			(int rs);						//	Jump Register
	//****************************************************************************
	//** SPECIAL INSTRUCTIONS                                                   **
	//****************************************************************************
	static inline void BREAK		(int immed);					//	BREAKpoint
	static inline void SYSCALL		(int immed);					//	SYStem CALL
	//****************************************************************************
	//** EXCEPTION INSTRUCTIONS                                                 **
	//****************************************************************************
	static inline void TEQ			(int rs, int rt);				//	Trap if =
	static inline void TEQI			(int rs, int immed);			//	Trap if = immediate
	static inline void TGE			(int rs, int rt);				//	Trap if >=
	static inline void TGEI			(int rs, int immed);			//	Trap if >= immediate
	static inline void TGEIU		(int rs, int immed);			//	Trap if >= immediate Unsigned
	static inline void TGEU			(int rs, int rt);				//	Trap if >= Unsigned
	static inline void TLT			(int rs, int rt);				//	Trap if <
	static inline void TLTI			(int rs, int immed);			//	Trap if < immediate
	static inline void TLTIU		(int rs, int immed);			//	Trap if < immediate Unsigned
	static inline void TLTU			(int rs, int rt);				//	Trap if < Unsigned
	static inline void TNE			(int rs, int rt);				//	Trap if <>
	static inline void TNEI			(int rs, int immed);				//	Trap if <> immediate
	//****************************************************************************
	//** SYSTEM CONTROL PROCESSOR (COP0) INSTRUCTIONS                          **
	//****************************************************************************
	static inline void CACHE		(int rt, int immed, int rs);	//	CACHE
	static inline void ERET			(void);							//	Return from Exception
	static inline void MFC0			(int rt, int fs);				//	Move Word From CP0
	static inline void MTC0			(int rt, int fs);				//	Move Word To CP0
	static inline void TLBP			(void);							//	Probe TLB for Matching Entry
	static inline void TLBR			(void);							//	Read Indexed TLB Entry
	static inline void TLBWI		(void);							//	Write Indexed TLB Entry
	static inline void TLBWR		(void);							//	Write Random TLB Entry
	//****************************************************************************
	//** FLOATING-POINT UNIT, FPU (COP1) INSTRUCTIONS                           **
	//****************************************************************************
	template<typename Type>
	static inline void ABS			(int fd, int fs);				//	floating-point ABSolute value
	template<typename Type>
	static inline void ADD			(int fd, int fs, int ft);		//	floating-point ADD
	static inline void BC1F			(int immed);					//	Branch on FP False
	static inline void BC1FL		(int immed);					//	Branch on FP False Likely
	static inline void BC1T			(int immed);					//	Branch on FP True
	static inline void BC1TL		(int immed);					//	Branch on FP True Likely
	template<typename Type>
	static inline void C			(int fs, int ft, int cond);		//	floating-point floating point Compare
	template<typename Type, typename toType>
	static inline void CEIL			(int fd, int fs);				//	floating-point CEILing convert to toType fixed-point
	static inline void CFC1			(int rt, int fs);				//	Move control word From Floating-Point
	static inline void CTC1			(int rt, int fs);				//	Move control word To Floating-Point
	template<typename Type, typename toType>
	static inline void CVT			(int fd, int fs);				//	floating-point ConVerT to toType floating/fixed-point
	template<typename Type>
	static inline void DIV			(int fd, int fs, int ft);		//	floating-point DIVide
	static inline void DMFC1		(int rt, int fs);				//	Doubleword Move From Floating-Point
	static inline void DMTC1		(int rt, int fs);				//	Doubleword Move To Floating-Point
	template<typename Type, typename toType>
	static inline void FLOOR		(int fd, int fs);				//	floating-point FLOOR convert to toType fixed-point
	static inline void LDC1			(int ft, int immed, int rs);	//	Load Doubleword to Floating-Point
	static inline void LWC1			(int ft, int immed, int rs);	//	Load Word to Floating-Point
	static inline void MFC1			(int rt, int fs);				//	Move Word From Floating-Point
	template<typename Type>
	static inline void MOV			(int fd, int fs);				//	floating-point MOVe
	static inline void MTC1			(int rt, int fs);				//	Move Word To Floating-Point
	template<typename Type>
	static inline void MUL			(int fd, int fs, int ft);		//	floating-point MULtiply
	template<typename Type>
	static inline void NEG			(int fd, int fs);				//	floating-point NEGate
	template<typename Type, typename toType>
	static inline void ROUND		(int fd, int fs);				//	floating-point ROUND to toType fixed-point
	static inline void SDC1			(int ft, int immed, int rs);	//	Store Doubleword from Floating-Point
	template<typename Type>
	static inline void SQRT			(int fd, int fs);				//	floating-point SQuare RooT
	template<typename Type>
	static inline void SUB			(int fd, int fs, int ft);		//	floating-point SUBtract
	static inline void SWC1			(int ft, int immed, int rs);	//	Store Word from Floating-Point
	template<typename Type, typename toType>
	static inline void TRUNC		(int fd, int fs);				//	floating-point TRUNCate to Long fixed-point
	//****************************************************************************
	//** CONDITIONS		                                                        **
	//****************************************************************************
	template<typename Type>	static inline void F(int fs, int ft);		// False
	template<typename Type>	static inline void UN(int fs, int ft);		// Unordered
	template<typename Type>	static inline void EQ(int fs, int ft);		// Equal
	template<typename Type>	static inline void UEQ(int fs, int ft);	// Unordered or Equal
	template<typename Type>	static inline void OLT(int fs, int ft);	// Ordered or Less Than
	template<typename Type>	static inline void ULT(int fs, int ft);	// Unordered or Less Than
	template<typename Type>	static inline void OLE(int fs, int ft);	// Ordered or Less than or Equal
	template<typename Type>	static inline void ULE(int fs, int ft);	// Unordered or Less than or Equal
	template<typename Type>	static inline void SF(int fs, int ft);		// Signaling False
	template<typename Type>	static inline void NGLE(int fs, int ft);	// Not Greater than or Less than or Equal
	template<typename Type>	static inline void SEQ(int fs, int ft);	// Signaling Equal
	template<typename Type>	static inline void NGL(int fs, int ft);	// Not Greater than or Less than
	template<typename Type>	static inline void LT(int fs, int ft);		// Less Than
	template<typename Type>	static inline void NGE(int fs, int ft);	// Not Greater than or Equal
	template<typename Type>	static inline void LE(int fs, int ft);		// Less than or Equal
	template<typename Type>	static inline void NGT(int fs, int ft);	// Not Greater Than
};

