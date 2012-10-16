#pragma once

#define STATUS_IE		0x00000000
#define STATUS_EXL		0x00000002
#define STATUS_ERL		0x00000004
#define STATUS_KSU		0x00000018
#define STATUS_UX		0x00000020
#define STATUS_SX		0x00000040
#define STATUS_KX		0x00000080
#define STATUS_IM		0x0000FF00
#define STATUS_DE		0x00010000
#define STATUS_CE		0x00020000
#define STATUS_CH		0x00040000
#define STATUS_SR		0x00100000
#define STATUS_TS		0x00200000
#define STATUS_BEV		0x00400000
#define STATUS_rsvd		0x00800000
#define STATUS_ITS		0x01000000
#define STATUS_RE		0x02000000
#define STATUS_FR		0x04000000
#define STATUS_RP		0x08000000
#define STATUS_CU		0xF0000000

#define CAUSE_ExcCode	0x0000007C
#define CAUSE_IP		0x0000FF0C
#define CAUSE_CE		0x30000000
#define CAUSE_BD		0x10000000

enum ExceptionType
{
	RESET_NMI,
	TLB_REFILL,
	XTLB_REFILL,
	OTHER
};

enum Exception // Order matters: Reset has the highest priority while Interrupt has the lowest
{
	RESET,
	SOFT_RESET,
	NMI,
	ADDRESS_ERROR_INSTRUCTION_FETCH,
	TLB_REFILL_INSTRUCTION_FETCH,
	TLB_INVALID_INSTRUCTION_FETCH,
	BUS_ERROR_INSTRUCTION_FETCH,
	SYSTEM_CALL,
	BREAKPOINT,
	COPROCESSOR_UNUSABLE,
	RESERVED_INSTRUCTION,
	TRAP_INSTRUCTION,
	INTEGER_OVERﬂOW,
	FLOATING_POINT_EXCEPTION,
	ADDRESS_ERROR_DATA_ACCESS,
	TLB_REFILL_DATA_ACCESS,
	TLB_INVALID_DATA_ACCESS,
	TLB_MODIﬁED_DATA_WRITE,
	WATCH,
	BUS_ERROR_DATA_ACCESS,
	INTERRUPT
};

class ExceptionVector
{
public:
	ExceptionVector(int off, dword vec) : offset(off), bev(0), vector(vec)  {};
	inline void		setBev(bool b)	{ bev = b; };
	inline dword	getVector()		{ return bev ? vector + 0x200 : vector; };
private:
	int				offset;		// Vector Offset
	bool			bev;		// Boot Exception Vector
	dword			vector;		// Exception Vector
};

// When following instructions are aborted, exceptions
// associated with those instructions are also aborted.
// Therefore, exceptions are not taken in the order
// detected, but rather in instruction fetch order.
