#pragma once

class R4300i
{
public:
	R4300i(RDRAM &ram);
	void decode(const word instr);
private:
	RDRAM &ram;
	ExceptionHandler &ehandler;

	void decode_r(const word instr);
	void decode_i(const word instr);
	void decode_cop0(const word instr);
	void decode_tlb(const word instr);
	void decode_cop1(const word instr);
	void decode_bc1(const word instr);
	template<typename Type>
	void decode_fpu(const word instr);
	//****************************************************************************
	//** Rregisters					                                            **
	//****************************************************************************
	dword r[32];									// General Purpose Registers (GPRs)
	dword f[32];									// FP General Purpose Registers (FGRs)
	dword pc, hi, lo, ll, fcr0, fcr31;				// Special Registers
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
	void ADDI         (int rt, int rs, int immed);	//	ADD immediate word
	void ADDIU        (int rt, int rs, int immed);	//	Add immediate Unsigned word
	void ADDU         (int rd, int rs, int rt);		//	Add Unsigned word
	void AND          (int rd, int rs, int rt);		//	AND
	void ANDI         (int rt, int rs, int immed);	//	AND immediate
	void DADD         (int rd, int rs, int rt);		//	Doubleword ADD
	void DADDI        (int rt, int rs, int immed);	//	Doubleword ADD immediate
	void DADDIU       (int rt, int rs, int immed);	//	Doubleword ADD immediate Unsigned
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
	void LUI          (int rt, int immed);			//	Load Upper immediate
	void MFHI         (int rd);						//	Move From HI register
	void MFLO         (int rd);						//	Move From LO register
	void MTHI         (int rd);						//	Move To HI register
	void MTLO         (int rd);						//	Move To LO register
	void MULT         (int rs, int rt);				//	MULTiply word
	void MULTU        (int rs, int rt);				//	MULTiply Unsigned word
	void NOR          (int rd, int rs, int rt);		//	Not OR
	void OR           (int rd, int rs, int rt);		//	OR
	void ORI          (int rt, int rs, int immed);	//	OR immediate
	void SLL          (int rd, int rt, int sa);		//	Shift word Left Logical
	void SLLV         (int rd, int rt, int rs);		//	Shift word Left Logical Variable
	void SLT          (int rd, int rs, int rt);		//	Set on Less Than
	void SLTI         (int rt, int rs, int immed);	//	Set on Less Than immediate
	void SLTIU        (int rt, int rs, int immed);	//	Set on Less Than immediate Unsigned
	void SLTU         (int rd, int rs, int rt);		//	Set on Less Than Unsigned
	void SRA          (int rd, int rt, int sa);		//	Shift word Right Arithmetic
	void SRAV         (int rd, int rt, int rs);		//	Shift word Right Arithmetic Variable
	void SRL          (int rd, int rt, int sa);		//	Shift word Right Logical
	void SRLV         (int rd, int rt, int rs);		//	Shift word Right Logical Variable
	void SUB          (int rd, int rs, int rt);		//	SUBtract word
	void SUBU         (int rd, int rs, int rt);		//	SUBtract Unsigned word
	void XOR          (int rd, int rs, int rt);		//	eXclusive OR
	void XORI         (int rt, int rs, int immed);	//	eXclusive OR immediate
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
	void J            (int address);				//	Jump
	void JAL          (int address);				//	Jump And Link
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
	void TEQI         (int rs, int immed);			//	Trap if = immediate
	void TGE          (int rs, int rt);				//	Trap if >=
	void TGEI         (int rs, int immed);			//	Trap if >= immediate
	void TGEIU        (int rs, int immed);			//	Trap if >= immediate Unsigned
	void TGEU         (int rs, int rt);				//	Trap if >= Unsigned
	void TLT          (int rs, int rt);				//	Trap if <
	void TLTI         (int rs, int immed);			//	Trap if < immediate
	void TLTIU        (int rs, int immed);			//	Trap if < immediate Unsigned
	void TLTU         (int rs, int rt);				//	Trap if < Unsigned
	void TNE          (int rs, int rt);				//	Trap if <>
	void TNEI         (int rs, int immed);				//	Trap if <> immediate
	//****************************************************************************
	//** System Control Processor (COP0); Instructions                          **
	//****************************************************************************
	void CACHE        (int rt, int immed, int rs);	//	CACHE
	void ERET		  (void);						//	Return from Exception
	void MFC0         (int rt, int fs);				//	Move Word From CP0
	void MTC0         (int rt, int fs);				//	Move Word To CP0
	void TLBP		  (void);						//	Probe TLB for Matching Entry
	void TLBR		  (void);						//	Read Indexed TLB Entry
	void TLBWI		  (void);						//	Write Indexed TLB Entry
	void TLBWR		  (void);						//	Write Random TLB Entry
	//****************************************************************************
	//** Floating-point Unit, FPU (COP1); instructions                          **
	//****************************************************************************
	template<typename Type>
	void ABS		  (int fd, int fs);				//	floating-point ABSolute value
	template<typename Type>
	void ADD		  (int fd, int fs, int ft);		//	floating-point ADD
	void BC1F         (int immed);					//	Branch on FP False
	void BC1FL        (int immed);					//	Branch on FP False Likely
	void BC1T         (int immed);					//	Branch on FP True
	void BC1TL        (int immed);					//	Branch on FP True Likely
	template<typename Type>
	void C			  (int fs, int ft, int cond);	//	floating-point floating point Compare
	template<typename Type, typename toType>
	void CEIL		  (int fd, int fs);				//	floating-point CEILing convert to toType fixed-point
	void CFC1         (int rt, int fs);				//	Move control word From Floating-Point
	void CTC1         (int rt, int fs);				//	Move control word To Floating-Point
	template<typename Type, typename toType>
	void CVT		  (int fd, int fs);				//	floating-point ConVerT to toType floating/fixed-point
	template<typename Type>
	void DIV		  (int fd, int fs, int ft);		//	floating-point DIVide
	void DMFC1        (int rt, int fs);				//	Doubleword Move From Floating-Point
	void DMTC1        (int rt, int fs);				//	Doubleword Move To Floating-Point
	template<typename Type, typename toType>
	void FLOOR		  (int fd, int fs);				//	floating-point FLOOR convert to toType fixed-point
	void LDC1         (int ft, int immed, int rs);	//	Load Doubleword to Floating-Point
	void LWC1         (int ft, int immed, int rs);	//	Load Word to Floating-Point
	void MFC1         (int rt, int fs);				//	Move Word From Floating-Point
	template<typename Type>
	void MOV		  (int fd, int fs);				//	floating-point MOVe
	void MTC1         (int rt, int fs);				//	Move Word To Floating-Point
	template<typename Type>
	void MUL		  (int fd, int fs, int ft);		//	floating-point MULtiply
	template<typename Type>
	void NEG		  (int fd, int fs);				//	floating-point NEGate
	template<typename Type, typename toType>
	void ROUND		  (int fd, int fs);				//	floating-point ROUND to toType fixed-point
	void SDC1         (int ft, int immed, int rs);	//	Store Doubleword from Floating-Point
	template<typename Type>
	void SQRT		  (int fd, int fs);				//	floating-point SQuare RooT
	template<typename Type>
	void SUB		  (int fd, int fs, int ft);		//	floating-point SUBtract
	void SWC1         (int ft, int immed, int rs);	//	Store Word from Floating-Point
	template<typename Type, typename toType>
	void TRUNC		  (int fd, int fs);				//	floating-point TRUNCate to Long fixed-point
	//****************************************************************************
	//** Pseudo opcodes                                                         **
	//****************************************************************************
	// FIXME: cleanup, or try to figure out why there is no opcode for some of these:
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
	void LI           (int rt, int immed);			//	Assembles to ORI    rt, r0, immed (if immed is 16 bit);
	 												//						or ADDIU  rt, r0, immed
	 												//						or LUI    rt, high_16
													//						   ORI    rt, rt, low_16 (if immed is 32 bit);
	void S_S          (int ft, int immed, int rs);	//	Assembles to SWC1   ft, immed(rs);
	void L_S          (int ft, int immed, int rs);	//	Assembles to LWC1   ft, immed(rs);
	//****************************************************************************
	//** Conditions		                                                        **
	//****************************************************************************
	template<typename Type>
	bool F(Type a, Type b);		// False
	template<typename Type>
	bool UN(Type a, Type b);	// Unordered
	template<typename Type>
	bool EQ(Type a, Type b);	// Equal
	template<typename Type>
	bool UEQ(Type a, Type b);	// Unordered or Equal
	template<typename Type>
	bool OLT(Type a, Type b);	// Ordered or Less Than
	template<typename Type>
	bool ULT(Type a, Type b);	// Unordered or Less Than
	template<typename Type>
	bool OLE(Type a, Type b);	// Ordered or Less than or Equal
	template<typename Type>
	bool ULE(Type a, Type b);	// Unordered or Less than or Equal
	template<typename Type>
	bool SF(Type a, Type b);	// Signaling False
	template<typename Type>
	bool NGLE(Type a, Type b);	// Not Greater than or Less than or Equal
	template<typename Type>
	bool SEQ(Type a, Type b);	// Signaling Equal
	template<typename Type>
	bool NGL(Type a, Type b);	// Not Greater than or Less than
	template<typename Type>
	bool LT(Type a, Type b);	// Less Than
	template<typename Type>
	bool NGE(Type a, Type b);	// Not Greater than or Equal
	template<typename Type>
	bool LE(Type a, Type b);	// Less than or Equal
	template<typename Type>
	bool NGT(Type a, Type b);	// Not Greater Than
};

