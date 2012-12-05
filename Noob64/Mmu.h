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
 * The Mmu files contains the functions, macro and structure to represente
 * and emulate the whole memory of the n64.
 *
 */

#pragma once

// Memory segments from 0x80000000 to 0xFFFFFFFF
#define KSEG0		0x80000000
#define KSEG1		0xA0000000
#define KSEG2		0xC0000000
#define KSEG3		0xE0000000

// The TLB entry structure
typedef struct {
   short			mask;	// Comparison MASK
   long				vpn2;	// Virtual Page Number / 2
   char				g;		// Global bit
   unsigned char	asid;	// Address Space Identifier
   long				pfn0;	// [EVEN] Physical Page Number (upper 20 bits of the physical address)
   char				c0;		// [EVEN] Cache Algorithm (011=cached; 010=uncached)
   char				d0;		// [EVEN] If set, page is writable
   char				v0;		// [EVEN] If set, entry is valid
   long				pfn1;	// [ODD] Physical Page Number (upper 20 bits of the physical address)
   char				c1;		// [ODD] Cache Algorithm (011=cached; 010=uncached)
   char				d1;		// [ODD] If set, page is writable
   char				v1;		// [ODD] If set, entry is valid

   char				r;		// Region used to match VAddr63..62
   unsigned long	start0;
   unsigned long	end0;
   unsigned long	phys0;
   unsigned long	start1;
   unsigned long	end1;
   unsigned long	phys1;
} tlb_entry;

//****************************************************************************
//** MEMORY MANAGEMENT UNIT					                                **
//****************************************************************************
class MMU
{
public:
	// Clears the MMU
	static void reset(void);

	// Returns a pointer to the physical location of the given virtual address
	static inline char* get(const word address);

	// Reads a Type at the given address and returns it
	template <typename Type> static inline Type read(word address);
	// Function read + Triggers read events if trigger_event is true
	template <typename Type> static inline Type read(word address, bool trigger_event);

	// Writes a data of the type Type at the given address
	template <typename Type> static inline void write(Type data, word address);
	// Function Write + Triggers write events if trigger_event is true
	template <typename Type> static inline void write(Type data, word address, bool trigger_event);

	// Returns true if the given address is valid
	static inline bool is_address_defined(word address);

	// TODO: Add getters and setters
	static tlb_entry	tlb[32]; // The TLB
	static word			tlb_lut_r[0x100000];
	static word			tlb_lut_w[0x100000];
	static char			invalid_code[0x100000];

private:
	static inline char* virtual_to_physical(word address);				// Returns a physical address given a virtual address
	static inline bool read_from_register(word *data, word address);	// Reads a register value with it's getter
	static inline bool write_in_register(word data, word address);		// Writes a value in a register with it's setter
};


