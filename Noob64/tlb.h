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