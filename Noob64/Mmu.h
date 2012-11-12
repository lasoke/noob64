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

class MMU
{
public:
	MMU(R4300i&, RCP&);
	~MMU(void);

	void reset(void);

	char* operator[] (const word address);
	template <typename Type> inline Type read(word address);
	template <typename Type> inline void write(Type data, word address);

	inline bool is_address_defined(word address) const;

	// TODO: Add getters and setters
	tlb_entry	tlb[32];
	word		tlb_lut_r[0x100000];
	word		tlb_lut_w[0x100000];
	char		invalid_code[0x100000];

private:
	R4300i		&cpu;
	RCP			&rcp;

	inline char* virtual_to_physical(word address);
	inline bool read_from_register(word *data, word address);
	inline bool write_in_register(word data, word address);
};


