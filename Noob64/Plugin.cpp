#include "StdAfx.h"
#include "Plugin.h"


PLUGIN::PLUGIN(wstring filename)
{
	hDLL = LoadLibrary(filename.c_str());

	if (hDLL == NULL)
	{
		// TODO: throw an exception so that new RSP() returns NULL
		return;
	}

	CloseDLL_				= (CLOSEDLL) GetProcAddress(hDLL, "CloseDLL");
	DllAbout_				= (DLLABOUT) GetProcAddress(hDLL, "DllAbout");
	DllConfig_				= (DLLCONFIG) GetProcAddress(hDLL, "DllConfig");
	DllTest_				= (DLLTEST)	GetProcAddress(hDLL, "DllTest");
	GetDllInfo_				= (GETDLLINFO) GetProcAddress(hDLL, "GetDllInfo");
	RomClosed_				= (ROMCLOSED) GetProcAddress(hDLL, "RomClosed");

	plugin_info				= (PLUGIN_INFO*) malloc(sizeof(PLUGIN_INFO));
}


PLUGIN::~PLUGIN(void)
{
}

void PLUGIN::CloseDLL()
{
	return CloseDLL_();
}

void PLUGIN::DllAbout(HWND h)
{
	return DllAbout_(h);
}

void PLUGIN::DllConfig(HWND h)
{
	return DllConfig_(h);
}

void PLUGIN::DllTest(HWND h)
{
	return DllTest_(h);
}

void PLUGIN::GetDllInfo()
{
	return GetDllInfo_(plugin_info);
}

void PLUGIN::RomClosed()
{
	return RomClosed_();
}

const PLUGIN_INFO PLUGIN::getPluginInfo()
{
	return *plugin_info;
}

