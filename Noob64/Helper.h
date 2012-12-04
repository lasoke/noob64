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
 * The Helper files contains the functions, use by the emulator but not related
 * to any component in particular
 *
 */

#pragma once

// Formats the string "s" representing a number:
// adds a character "c" every "frequency" character
string format_number(string s, char c, int frequency);

// Prints an address in the standard representation:
// e.g. FFFFFFFF will print "FFFF FFFF : "
string print_addr(word address);

// Returns the word contained at the address pointed by ptr
byte getByte(char **ptr);

// Converts a byte array to its "type" representation
template <typename Type> inline Type binary_to_type(Type toSwap);

// Converts a "type" to its binary representation
template <typename Type> inline Type type_to_binary(Type data);

// Temporary dummy function
void dummyCheckInterrupts();
void dummyProcessDList();
void dummyProcessAList();
void dummyProcessRdpList();
void dummyShowCFB();