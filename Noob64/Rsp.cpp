#include "StdAfx.h"
#include "Rsp.h"


RSP::RSP(wstring filename) : PLUGIN(filename)
{
	DoRspCycles_			= (DORSPCYCLES) GetProcAddress(hDLL, "DoRspCycles");
	GetRspDebugInfo_		= (GETRSPDEBUGINFO) GetProcAddress(hDLL, "GetRspDebugInfo");
	InitiateRSP_			= (INITIATERSP) GetProcAddress(hDLL, "InitiateRSP");
	InitiateRSPDebugger_	= (INITIATERSPDEBUGGER) GetProcAddress(hDLL, "InitiateRSPDebugger");

	rsp_info				= (RSP_INFO*) malloc(sizeof(RSP_INFO));
	rspdebug_info			= (RSPDEBUG_INFO*) malloc(sizeof(RSPDEBUG_INFO));
	debug_info				= (DEBUG_INFO*) malloc(sizeof(DEBUG_INFO));
}

RSP::~RSP(void)
{
}

word RSP::DoRspCycles(word w)
{
	return DoRspCycles_(w);
}

void RSP::GetRspDebugInfo(RSPDEBUG_INFO* i)
{
	return GetRspDebugInfo_(i);
}

void RSP::InitiateRSP(RSP_INFO i, word* w)
{
	return InitiateRSP_(i, w);
}

void RSP::InitiateRSPDebugger(DEBUG_INFO i)
{
	return InitiateRSPDebugger_(i);
}

const RSP_INFO RSP::getRspInfo()
{
	return *rsp_info;
}

const RSPDEBUG_INFO RSP::getRspDebugInfo()
{
	return *rspdebug_info;
}

const DEBUG_INFO RSP::getDebugInfo()
{
	return *debug_info;
}

