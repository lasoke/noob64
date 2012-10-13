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

	closeDLL_				= (CLOSEDLL) GetProcAddress(hDLL, "CloseDLL");
	dllAbout_				= (DLLABOUT) GetProcAddress(hDLL, "DllAbout");
	dllConfig_				= (DLLCONFIG) GetProcAddress(hDLL, "DllConfig");
	dllTest_				= (DLLTEST)	GetProcAddress(hDLL, "DllTest");
	getDllInfo_				= (GETDLLINFO) GetProcAddress(hDLL, "GetDllInfo");
	romClosed_				= (ROMCLOSED) GetProcAddress(hDLL, "RomClosed");

	plugin_info				= (PLUGIN_INFO*) malloc(sizeof(PLUGIN_INFO));
	getDllInfo_(plugin_info);
}


PLUGIN::~PLUGIN(void)
{
}

void PLUGIN::closeDLL()
{
	return closeDLL_();
}

void PLUGIN::dllAbout(HWND h)
{
	return dllAbout_(h);
}

void PLUGIN::dllConfig(HWND h)
{
	return dllConfig_(h);
}

void PLUGIN::dllTest(HWND h)
{
	return dllTest_(h);
}

void PLUGIN::romClosed()
{
	return romClosed_();
}

