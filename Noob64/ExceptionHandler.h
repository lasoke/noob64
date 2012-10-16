#pragma once

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
