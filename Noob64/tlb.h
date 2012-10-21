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
   short			mask;
   long				vpn2;
   char				g;
   unsigned char	asid;
   long				pfn_even;
   char				c_even;
   char				d_even;
   char				v_even;
   long				pfn_odd;
   char				c_odd;
   char				d_odd;
   char				v_odd;
   char				r;
   //long check_parity_mask;
   unsigned long	start_even;
   unsigned long	end_even;
   unsigned long	phys_even;
   unsigned long	start_odd;
   unsigned long	end_odd;
   unsigned long	phys_odd;
} TLB;