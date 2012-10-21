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

#include "StdAfx.h"
#include "Exception.h"

#define UPDATE_REGS()															\
		EPC = (word) (delay_slot ? pc - 4 : pc);								\
		Cause = (word) (delay_slot ? Cause | CAUSE_BD : Cause & ~CAUSE_BD);		\
		Status |= STATUS_EXL;													\
		pc = 0x80000180;

#define PRINT_EXC(NAME)															\
		if (Status & STATUS_EXL)												\
			cerr << "EXL set in " << NAME << " Exception" << endl;				\
        if (Status & STATUS_ERL)												\
			cerr << "ERL set in " << NAME << " Exception" << endl;


void R4300i::check_interrupt(void)
{
	if (memory->mi_regs.getIntr() & memory->mi_regs.getIntrMask())	// An interrupt is detected.
		Cause |= CAUSE_IP2;											// Sets the IP2 bit (ExcCode mask should be clear at this point!).
	else
		Cause &= ~CAUSE_IP2;										// Clears the IP2 bit.
	if ((Cause & Status & STATUS_IM) == 0 || (Status & 7) != 1)		// Conditions to take an interrupt.
		return;
	interrupt_detected = true;										// We detected an interrupt, we now notify the handler
}

void R4300i::trigger_address_error(dword address, bool from_read)
{
	PRINT_EXC("AddressError");
	Cause = from_read ? ADDRESS_ERROR_INSTRUCTION_FETCH : ADDRESS_ERROR_DATA_ACCESS;
    BadVAddr = (word) address;
	UPDATE_REGS();
}

void R4300i::trigger_break_exception()
{
	PRINT_EXC("Break");
    Cause = BREAKPOINT;
	UPDATE_REGS();
}

void R4300i::trigger_copunusable_exception()
{
	PRINT_EXC("CopUnusable");
    Cause = COPROCESSOR_UNUSABLE;
    Cause |= current_coprocessor == 1 ? 0x10000000 : 0;
	UPDATE_REGS();
}

void R4300i::trigger_intr_exception()
{
	if ((Status & 7) != 1)
		return;
    //Cause = FAKE_Cause;
    Cause |= INTERRUPT;
    UPDATE_REGS();
}

void R4300i::trigger_tlb_miss(dword address)
{
    Cause = TLB_INVALID_INSTRUCTION_FETCH;
    BadVAddr = (word) address;
    Context &= 0xFF80000F;
    Context |= (address >> 9) & 0x007FFFF0;
    EntryHi = (address & 0xFFFFE000);

    if (!(Status & STATUS_EXL))
	{
		UPDATE_REGS();
		pc = is_address_defined(address) ? 0x80000180 : 0x80000000;
	}
	else
	{
		cerr << "EXL Set\nAddress Defined: " << (is_address_defined(address) ? "TRUE" : "FALSE") << endl;
		pc = 0x80000180;
	}
}

void R4300i::trigger_syscall_exception()
{
	PRINT_EXC("SysCall");
    Cause = SYSTEM_CALL;
	UPDATE_REGS();
}
