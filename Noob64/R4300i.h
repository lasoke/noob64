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
	R4300i(RCP*);

	void start(void);				// Initializes the R4300i and enter in the main loop
	void reset(void);				// Clears bits
	void check_interrupt(void);		// Checks if an interrupt has been triggered
	void timer_done(void);			// Uses to see if a timer is done

	/* GETTERS */
	inline MMU& getMMU(void) const;
	inline TimerHandler& getTimerHandler(void) const;
	inline word getCop0(int) const;
	
	/* SETTERS */
	inline void setCop0(int, word);

private:
	RCP				&rcp;										// A pointer to the RCP
	MMU				&mmu;										// A pointer to the MMU
	TimerHandler	&timer_handler;								// A pointer to the timer handler

	void pif_init(void); // Workaround to pass the CRC check which prevents a fake game from loading

	//****************************************************************************
	//** EXCEPTION PROCESSING UNIT												**
	//****************************************************************************
	bool interrupt_detected;									// Notifies whether an interrupt has been detected or not
	void trigger_address_error(word address, bool from_read);	// Triggers an address error exception
	void trigger_break_exception();								// Triggers a break exception
	void trigger_copunusable_exception(int cop);				// Triggers a COP unusable exception
	void trigger_intr_exception();								// Triggers an interruption exception
	void trigger_tlb_miss(word address);						// Triggers a TLB missed exception
	void trigger_syscall_exception();							// Triggers a syscall exception
	//****************************************************************************
	//** DECODER																**
	//****************************************************************************
	inline void	decode(const word instr);						// Decodes the given instruction
	inline void decode_r(const word instr);						// Decodes the given R-typed instruction
	inline void decode_i(const word instr);						// Decodes the given I-typed instruction
	inline void decode_cop0(const word instr);					// Decodes the given COP0-typed instruction
	inline void decode_tlb(const word instr);					// Decodes the given TLB-typed instruction
	inline void decode_cop1(const word instr);					// Decodes the given COP1-typed instruction
	inline void decode_bc1(const word instr);					// Decodes the given BC1-typed instruction
	template<typename Type>
	inline void decode_fpu(const word instr);					// Decodes the given FPU-typed instruction
	inline int	probe_nop(word address);						// Checks whether the next instruction is a nop or not
	//****************************************************************************
	//** REGISTERS					                                            **
	//****************************************************************************
	// TODO: r[0] is always 0
	dword	r[32];												// General Purpose Registers (GPRs)
	dword	f[32];												// FP General Purpose Registers (FGRs)
	word	cop0[32];											// Cop0 registers
	dword	pc;													// Program Counter
	dword	hi, lo;												// Multiply/Divide result
	word	fcr0, fcr31;										// Floating Point Control Registers
	bool	ll;													// Load/Link Register
	//****************************************************************************
	//** MISC																	**
	//****************************************************************************
	bool	delay_slot;											// for branch instructions
	bool	running;											// Status of the CPU
	dword	cic_chip;											// To hack the security check of the n64
	//****************************************************************************
	//** LOAD AND STORE INSTRUCTIONS                                            **
	//****************************************************************************
	inline void LB				(int rt, int immed, int rs);	//  Load Byte
	inline void LBU				(int rt, int immed, int rs);	//  Load Byte Unsigned
	inline void LD				(int rt, int immed, int rs);	//  Load Doubleword
	inline void LDL				(int rt, int immed, int rs);	//  Load Doubleword Left
	inline void LDR				(int rt, int immed, int rs);	//  Load Doubleword Right
	inline void LH				(int rt, int immed, int rs);	//  Load Halfword
	inline void LHU				(int rt, int immed, int rs);	//  Load Halfword Unsigned
	inline void LL				(int rt, int immed, int rs);	//  Load Linked word
	inline void LLD				(int rt, int immed, int rs);	//  Load Linked Doubleword
	inline void LW				(int rt, int immed, int rs);	//  Load Word
	inline void LWL				(int rt, int immed, int rs);	//  Load Word Left
	inline void LWR				(int rt, int immed, int rs);	//  Load Word Right
	inline void LWU				(int rt, int immed, int rs);	//  Load Word Unsigned
	inline void SB				(int rt, int immed, int rs);	//  Store Byte
	inline void SC				(int rt, int immed, int rs);	//  Store Conditional word
	inline void SCD				(int rt, int immed, int rs);	//  Store Conditional Doubleword
	inline void SD				(int rt, int immed, int rs);	//  Store Doubleword
	inline void SDL				(int rt, int immed, int rs);	//  Store Doubleword Left
	inline void SDR				(int rt, int immed, int rs);	//  Store Doubleword Right
	inline void SH				(int rt, int immed, int rs);	//  Store Halfword
	inline void SW				(int rt, int immed, int rs);	//  Store Word
	inline void SWL				(int rt, int immed, int rs);	//  Store Word Left
	inline void SWR				(int rt, int immed, int rs);	//  Store Word Right
	inline void SYNC			(void);							//	SYNChronize shared memory
	//****************************************************************************
	//** ATITHMETIC INSTRUCTIONS                                                **
	//****************************************************************************
	inline void ADD				(int rd, int rs, int rt);		//	ADD word
	inline void ADDI			(int rt, int rs, int immed);	//	ADD immediate word
	inline void ADDIU			(int rt, int rs, int immed);	//	Add immediate Unsigned word
	inline void ADDU			(int rd, int rs, int rt);		//	Add Unsigned word
	inline void AND				(int rd, int rs, int rt);		//	AND
	inline void ANDI			(int rt, int rs, int immed);	//	AND immediate
	inline void DADD			(int rd, int rs, int rt);		//	Doubleword ADD
	inline void DADDI			(int rt, int rs, int immed);	//	Doubleword ADD immediate
	inline void DADDIU			(int rt, int rs, int immed);	//	Doubleword ADD immediate Unsigned
	inline void DADDU			(int rd, int rs, int rt);		//	Doubleword ADD Unsigned
	inline void DDIV			(int rs, int rt);				//	Doubleword DIVide
	inline void DDIVU			(int rs, int rt);				//	Doubleword DIVide Unsigned
	inline void DIV				(int rs, int rt);				//	DIVide word
	inline void DIVU			(int rs, int rt);				//	DIVide Unsigned word
	inline void DMULT			(int rs, int rt);				//	Doubleword MULTiply
	inline void DMULTU			(int rs, int rt);				//	Doubleword MULTiply Unsigned
	inline void DSLL			(int rd, int rt, int sa);		//	Doubleword Shift Left Logical
	inline void DSLL32			(int rd, int rt, int sa);		//	Doubleword Shift Left Logical +32
	inline void DSLLV			(int rd, int rt, int rs);		//	Doubleword Shift Left Logical Variable
	inline void DSRA			(int rd, int rt, int sa);		//	Doubleword Shift Right Arithmetic
	inline void DSRA32			(int rd, int rt, int sa);		//	Doubleword Shift Right Arithmetic +32
	inline void DSRAV			(int rd, int rt, int rs);		//	Doubleword Shift Right Arithmetic Variable
	inline void DSRL			(int rd, int rt, int sa);		//	Doubleword Shift Right Logical
	inline void DSRL32			(int rd, int rt, int sa);		//	Doubleword Shift Right Logical +32
	inline void DSRLV			(int rd, int rt, int rs);		//	Doubleword Shift Right Logical Variable
	inline void DSUB			(int rd, int rs, int rt);		//	Doubleword SUBtract
	inline void DSUBU			(int rd, int rs, int rt);		//	Doubleword SUBtract Unsigned
	inline void LUI				(int rt, int immed);			//	Load Upper immediate
	inline void MFHI			(int rd);						//	Move From HI register
	inline void MFLO			(int rd);						//	Move From LO register
	inline void MTHI			(int rs);						//	Move To HI register
	inline void MTLO			(int rs);						//	Move To LO register
	inline void MULT			(int rs, int rt);				//	MULTiply word
	inline void MULTU			(int rs, int rt);				//	MULTiply Unsigned word
	inline void NOR				(int rd, int rs, int rt);		//	Not OR
	inline void OR				(int rd, int rs, int rt);		//	OR
	inline void ORI				(int rt, int rs, int immed);	//	OR immediate
	inline void SLL				(int rd, int rt, int sa);		//	Shift word Left Logical
	inline void SLLV			(int rd, int rt, int rs);		//	Shift word Left Logical Variable
	inline void SLT				(int rd, int rs, int rt);		//	Set on Less Than
	inline void SLTI			(int rt, int rs, int immed);	//	Set on Less Than immediate
	inline void SLTIU			(int rt, int rs, int immed);	//	Set on Less Than immediate Unsigned
	inline void SLTU			(int rd, int rs, int rt);		//	Set on Less Than Unsigned
	inline void SRA				(int rd, int rt, int sa);		//	Shift word Right Arithmetic
	inline void SRAV			(int rd, int rt, int rs);		//	Shift word Right Arithmetic Variable
	inline void SRL				(int rd, int rt, int sa);		//	Shift word Right Logical
	inline void SRLV			(int rd, int rt, int rs);		//	Shift word Right Logical Variable
	inline void SUB				(int rd, int rs, int rt);		//	SUBtract word
	inline void SUBU			(int rd, int rs, int rt);		//	SUBtract Unsigned word
	inline void XOR				(int rd, int rs, int rt);		//	eXclusive OR
	inline void XORI			(int rt, int rs, int immed);	//	eXclusive OR immediate
	//****************************************************************************
	//** JUMP AND BRANCH INSTRUCTIONS                                           **
	//****************************************************************************
	inline void BEQ				(int rs, int rt, int immed);	//	Branch on =
	inline void BEQL			(int rs, int rt, int immed);	//	Branch on EQual Likely
	inline void BGEZ			(int immed, int rs);			//	Branch on >= Zero
	inline void BGEZAL			(int immed, int rs);			//	Branch on >= Zero And Link
	inline void BGEZALL			(int immed, int rs);			//	Branch on >= Zero And Link Likely
	inline void BGEZL			(int immed, int rs);			//	Branch on >= Equal to Zero Likely
	inline void BGTZ			(int immed, int rs);			//	Branch on > Zero
	inline void BGTZL			(int immed, int rs);			//	Branch on > Zero Likely
	inline void BLEZ			(int immed, int rs);			//	Branch on <= Equal to Zero
	inline void BLEZL			(int immed, int rs);			//	Branch on <= Zero Likely
	inline void BLTZ			(int immed, int rs);			//	Branch on < Zero
	inline void BLTZAL			(int immed, int rs);			//	Branch on < Zero And Link
	inline void BLTZALL			(int immed, int rs);			//	Branch on < Zero And Link Likely
	inline void BLTZL			(int immed, int rs);			//	Branch on < Zero Likely
	inline void BNE				(int rs, int rt, int immed);	//	Branch on <>
	inline void BNEL			(int rs, int rt, int immed);	//	Branch on <> Likely
	inline void J				(int address);					//	Jump
	inline void JAL				(int address);					//	Jump And Link
	inline void JALR			(int rs, int rd);				//	Jump And Link Register
	inline void JR				(int rs);						//	Jump Register
	//****************************************************************************
	//** SPECIAL INSTRUCTIONS                                                   **
	//****************************************************************************
	inline void BREAK			(int immed);					//	BREAKpoint
	inline void SYSCALL			(int immed);					//	SYStem CALL
	//****************************************************************************
	//** EXCEPTION INSTRUCTIONS                                                 **
	//****************************************************************************
	inline void TEQ				(int rs, int rt);				//	Trap if =
	inline void TEQI			(int rs, int immed);			//	Trap if = immediate
	inline void TGE				(int rs, int rt);				//	Trap if >=
	inline void TGEI			(int rs, int immed);			//	Trap if >= immediate
	inline void TGEIU			(int rs, int immed);			//	Trap if >= immediate Unsigned
	inline void TGEU			(int rs, int rt);				//	Trap if >= Unsigned
	inline void TLT				(int rs, int rt);				//	Trap if <
	inline void TLTI			(int rs, int immed);			//	Trap if < immediate
	inline void TLTIU			(int rs, int immed);			//	Trap if < immediate Unsigned
	inline void TLTU			(int rs, int rt);				//	Trap if < Unsigned
	inline void TNE				(int rs, int rt);				//	Trap if <>
	inline void TNEI			(int rs, int immed);				//	Trap if <> immediate
	//****************************************************************************
	//** SYSTEM CONTROL PROCESSOR (COP0) INSTRUCTIONS                          **
	//****************************************************************************
	inline void CACHE			(int rt, int immed, int rs);	//	CACHE
	inline void ERET			(void);							//	Return from Exception
	inline void MFC0			(int rt, int fs);				//	Move Word From CP0
	inline void MTC0			(int rt, int fs);				//	Move Word To CP0
	inline void TLBP			(void);							//	Probe TLB for Matching Entry
	inline void TLBR			(void);							//	Read Indexed TLB Entry
	inline void TLBWI			(void);							//	Write Indexed TLB Entry
	inline void TLBWR			(void);							//	Write Random TLB Entry
	//****************************************************************************
	//** FLOATING-POINT UNIT, FPU (COP1) INSTRUCTIONS                          **
	//****************************************************************************
	template<typename Type>
	inline void ABS				(int fd, int fs);				//	floating-point ABSolute value
	template<typename Type>
	inline void ADD				(int fd, int fs, int ft);		//	floating-point ADD
	inline void BC1F			(int immed);					//	Branch on FP False
	inline void BC1FL			(int immed);					//	Branch on FP False Likely
	inline void BC1T			(int immed);					//	Branch on FP True
	inline void BC1TL			(int immed);					//	Branch on FP True Likely
	template<typename Type>
	inline void C				(int fs, int ft, int cond);		//	floating-point floating point Compare
	template<typename Type, typename toType>
	inline void CEIL			(int fd, int fs);				//	floating-point CEILing convert to toType fixed-point
	inline void CFC1			(int rt, int fs);				//	Move control word From Floating-Point
	inline void CTC1			(int rt, int fs);				//	Move control word To Floating-Point
	template<typename Type, typename toType>
	inline void CVT				(int fd, int fs);				//	floating-point ConVerT to toType floating/fixed-point
	template<typename Type>
	inline void DIV				(int fd, int fs, int ft);		//	floating-point DIVide
	inline void DMFC1			(int rt, int fs);				//	Doubleword Move From Floating-Point
	inline void DMTC1			(int rt, int fs);				//	Doubleword Move To Floating-Point
	template<typename Type, typename toType>
	inline void FLOOR			(int fd, int fs);				//	floating-point FLOOR convert to toType fixed-point
	inline void LDC1			(int ft, int immed, int rs);	//	Load Doubleword to Floating-Point
	inline void LWC1			(int ft, int immed, int rs);	//	Load Word to Floating-Point
	inline void MFC1			(int rt, int fs);				//	Move Word From Floating-Point
	template<typename Type>
	inline void MOV				(int fd, int fs);				//	floating-point MOVe
	inline void MTC1			(int rt, int fs);				//	Move Word To Floating-Point
	template<typename Type>
	inline void MUL				(int fd, int fs, int ft);		//	floating-point MULtiply
	template<typename Type>
	inline void NEG				(int fd, int fs);				//	floating-point NEGate
	template<typename Type, typename toType>
	inline void ROUND			(int fd, int fs);				//	floating-point ROUND to toType fixed-point
	inline void SDC1			(int ft, int immed, int rs);	//	Store Doubleword from Floating-Point
	template<typename Type>
	inline void SQRT			(int fd, int fs);				//	floating-point SQuare RooT
	template<typename Type>
	inline void SUB				(int fd, int fs, int ft);		//	floating-point SUBtract
	inline void SWC1			(int ft, int immed, int rs);	//	Store Word from Floating-Point
	template<typename Type, typename toType>
	inline void TRUNC			(int fd, int fs);				//	floating-point TRUNCate to Long fixed-point
	//****************************************************************************
	//** CONDITIONS		                                                        **
	//****************************************************************************
	template<typename Type>
	inline void F(Type a, Type b);		// False
	template<typename Type>
	inline void UN(Type a, Type b);		// Unordered
	template<typename Type>
	inline void EQ(Type a, Type b);		// Equal
	template<typename Type>
	inline void UEQ(Type a, Type b);	// Unordered or Equal
	template<typename Type>
	inline void OLT(Type a, Type b);	// Ordered or Less Than
	template<typename Type>
	inline void ULT(Type a, Type b);	// Unordered or Less Than
	template<typename Type>
	inline void OLE(Type a, Type b);	// Ordered or Less than or Equal
	template<typename Type>
	inline void ULE(Type a, Type b);	// Unordered or Less than or Equal
	template<typename Type>
	inline void SF(Type a, Type b);		// Signaling False
	template<typename Type>
	inline void NGLE(Type a, Type b);	// Not Greater than or Less than or Equal
	template<typename Type>
	inline void SEQ(Type a, Type b);	// Signaling Equal
	template<typename Type>
	inline void NGL(Type a, Type b);	// Not Greater than or Less than
	template<typename Type>
	inline void LT(Type a, Type b);		// Less Than
	template<typename Type>
	inline void NGE(Type a, Type b);	// Not Greater than or Equal
	template<typename Type>
	inline void LE(Type a, Type b);		// Less than or Equal
	template<typename Type>
	inline void NGT(Type a, Type b);	// Not Greater Than
};

