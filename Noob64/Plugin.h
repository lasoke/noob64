#pragma once

#define PLUGIN_TYPE_RSP				1
#define PLUGIN_TYPE_GFX				2
#define PLUGIN_TYPE_AUDIO			3
#define PLUGIN_TYPE_CONTROLLER		4

typedef struct {
	hword Version;        /* Should be set to 0x0101 */
	hword Type;           /* Set to PLUGIN_TYPE_RSP */
	char Name[100];      /* Name of the DLL */

	/* If DLL supports memory these memory options then set them to TRUE or FALSE
	   if it does not support it */
	bool NormalMemory;   /* a normal byte array */ 
	bool MemoryBswaped;  /* a normal byte array where the memory has been pre
	                          bswap on a dword (32 bits) boundry */
} PLUGIN_INFO;

typedef void (_cdecl* CLOSEDLL)(void);
typedef void (_cdecl* DLLABOUT)(HWND);
typedef void (_cdecl* DLLCONFIG)(HWND);
typedef void (_cdecl* DLLTEST)(HWND);
typedef void (_cdecl* GETDLLINFO)(PLUGIN_INFO*);
typedef void (_cdecl* ROMCLOSED)(void);

class PLUGIN
{
public:
	PLUGIN(wstring filename);
	~PLUGIN();

	void closeDLL();
	void dllAbout(HWND);
	void dllConfig(HWND);
	void dllTest(HWND);
	void romClosed();

protected:
	HINSTANCE				hDLL;

	CLOSEDLL				closeDLL_;
	DLLABOUT				dllAbout_;
	DLLCONFIG				dllConfig_;
	DLLTEST					dllTest_;
	GETDLLINFO				getDllInfo_;
	ROMCLOSED				romClosed_;

	PLUGIN_INFO				*plugin_info;
};

