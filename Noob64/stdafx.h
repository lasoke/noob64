// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

#define DEBUG true

#include <stdlib.h>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// TODO: reference additional headers your program requires here
#include "Memory.h"
#include "Instruction.h"
#include "ExceptionHandler.h"
#include "Helper.h"
#include "Rom.h"
#include "tlb.h"
#include "R4300i.h"
#include "Form1.h"

// byteswap
#include <intrin.h>

