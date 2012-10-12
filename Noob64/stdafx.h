// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here

#define DEBUG true

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <typeinfo>
#include <vector>

using namespace std;

#include "Memory.h"
#include "RSP.h"
#include "Instruction.h"
#include "ExceptionHandler.h"
#include "Helper.h"
#include "Rom.h"
#include "tlb.h"
#include "R4300i.h"