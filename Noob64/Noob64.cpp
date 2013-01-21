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

// Noob64.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Noob64.h"

#define MAX_LOADSTRING 100

#define PLUGIN_FAILED(ID)																		\
	{																							\
		DialogBox(hInst, MAKEINTRESOURCE(IDD_PLUGIN_FAILED_TO_LOAD), hWnd, About);				\
		EnableMenuItem(GetMenu(hWnd), ID, MF_BYCOMMAND | MF_GRAYED);							\
		EnableMenuItem(GetMenu(hWnd), ID_FILE_PLAY, MF_BYCOMMAND | MF_GRAYED);					\
	}																							\

#define PLUGIN_SUCCESS(ID)																		\
	{																							\
		EnableMenuItem(GetMenu(hWnd), ID, MF_BYCOMMAND);										\
		if (GFX::isLoaded() & RSP::isLoaded() & AUDIO::isLoaded() & CONTROLLER::isLoaded())		\
			EnableMenuItem(GetMenu(hWnd), ID_FILE_PLAY, MF_BYCOMMAND);							\
	}																							\

// Global Variables:
HINSTANCE	hInst;							// Current instance
HWND		hStatusBar;						// Status bar
TCHAR		szTitle[MAX_LOADSTRING];		// The title bar text
TCHAR		szWindowClass[MAX_LOADSTRING];	// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// Helper function to dispay a console
FILE *stream;
void inline enableConsole()
{
	AllocConsole();
	freopen_s(&stream, "conin$","r", stdin);
	freopen_s(&stream, "conout$","w", stdout);
	freopen_s(&stream, "conout$","w", stderr);
}

char main_directory[_MAX_PATH];


HANDLE emuThread;
HANDLE audioThread;

// This is the sound function that is start within
// a new thread (the audio thread).
DWORD WINAPI sound(LPVOID lpParameter)
{
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	for (;;) AUDIO::aiUpdate(TRUE);
	return 0;
}

// This is the boot function that is start within
// a new thread (the emulation thread).
DWORD WINAPI boot(LPVOID lpParameter)
{
	//enableConsole();						// Displays the console
	RCP::start();							// Initializes the CPU and boots the ROM
	return 0;
}

//
//  FUNCTION: load_rom(HWND hWnd)
//
//  PURPOSE: Open a file dialog to select the ROM to play.
//
//  COMMENTS:
//
//    If no file is selected, the function returns false and
//	  nothing happens.
//
bool load_rom(HWND hWnd)
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = "z64 files (*.z64)\0*.z64\0n64 files (*.n64)\0*.n64\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	if (GetOpenFileName(&ofn))
	{
		RCP::setROM(new ROM(szFileName)); // Sets up the RCP with the given ROM
		return true;
	}
	return false;
}

//
//  FUNCTION: load_default_plugins()
//
//  PURPOSE: Loads the default plugins, defined programmatically.
//
void load_default_plugins(HWND hWnd)
{
	char tmp_path[_MAX_PATH];

	strcpy(tmp_path, main_directory); strcat(tmp_path, "Plugin\\mupen64_rsp_hle.dll");
	if (!RSP::load(tmp_path, hWnd))					// We disable the Configure RSP button because the plugin failed to load
		PLUGIN_FAILED(ID_RSP_CONFIGURE)
	
	strcpy(tmp_path, main_directory); strcat(tmp_path, "Plugin\\Jabo_Direct3D8_1_0.dll");
	if (!GFX::load(tmp_path, hWnd, hStatusBar))		// We disable the Configure VIDEO button because the plugin failed to load
		PLUGIN_FAILED(ID_VIDEO_CONFIGURE)
	
	strcpy(tmp_path, main_directory); strcat(tmp_path, "Plugin\\AudioHLE.dll");
	if (!AUDIO::load(tmp_path, hWnd)) 			// We disable the Configure AUDIO button because the plugin failed to load
		PLUGIN_FAILED(ID_AUDIO_CONFIGURE)
	
	strcpy(tmp_path, main_directory); strcat(tmp_path, "Plugin\\NRage Input 2.2.2 Beta.dll");
	if (!CONTROLLER::load(tmp_path, hWnd))	// We disable the Configure CONTROLLER button because the plugin failed to load
		PLUGIN_FAILED(ID_CONTROLLER_CONFIGURE)
}

//
//  FUNCTION: select_plugin(HWND hWnd)
//
//  PURPOSE: Open a file dialog to select the plugin to use.
//
//  COMMENTS:
//
//    If no file is selected, the function returns false and
//	  nothing happens.
//
bool select_plugin(HWND hWnd, int plugin_type)
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = "DLL files (*.dll)\0*.dll\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	if (GetOpenFileName(&ofn))
	{
		switch (plugin_type)
		{
		case PLUGIN_TYPE_RSP:
			return RSP::load(szFileName, hWnd);
		case PLUGIN_TYPE_GFX:
			return GFX::load(szFileName, hWnd);
		case PLUGIN_TYPE_AUDIO:
			return AUDIO::load(szFileName, hWnd);
		case PLUGIN_TYPE_CONTROLLER:
			return CONTROLLER::load(szFileName, hWnd);
		default:
			return false;
		}
	}
	return false;
}

// Main
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// MAIN CODE HERE

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NOOB64, szWindowClass, MAX_LOADSTRING);
	Set_Noob64_Directory();
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NOOB64));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NOOB64));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NOOB64);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	hStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, "", hWnd, 0);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	load_default_plugins(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_PLAY:															// When we click on Play
			if (!load_rom(hWnd)) break;												// if load_rom returned false, we abort
			EnableMenuItem(GetMenu(hWnd), ID_FILE_PLAY, MF_BYCOMMAND | MF_GRAYED);	// We disable the Play button
			audioThread = CreateThread(0, 0, sound, 0, 0, 0);						// Creates the audio thread
			emuThread = CreateThread(0, 0, boot, 0, 0, 0);							// Creates the emulation thread
			break;

		case ID_VIDEO_CHANGEPLUGIN:
			if (select_plugin(hWnd, PLUGIN_TYPE_GFX)) PLUGIN_SUCCESS(ID_VIDEO_CONFIGURE)
			else PLUGIN_FAILED(ID_VIDEO_CONFIGURE)
			break;
		case ID_VIDEO_CONFIGURE:
			GFX::dllConfig();
			break;

		case ID_AUDIO_CHANGEPLUGIN:
			if (select_plugin(hWnd, PLUGIN_TYPE_AUDIO)) PLUGIN_SUCCESS(ID_AUDIO_CONFIGURE)
			else PLUGIN_FAILED(ID_AUDIO_CONFIGURE)
			break;
		case ID_AUDIO_CONFIGURE:
			AUDIO::dllConfig();
			break;

		case ID_CONTROLLER_CHANGEPLUGIN:
			if (select_plugin(hWnd, PLUGIN_TYPE_CONTROLLER)) PLUGIN_SUCCESS(ID_CONTROLLER_CONFIGURE)
			else PLUGIN_FAILED(ID_CONTROLLER_CONFIGURE)
			break;
		case ID_CONTROLLER_CONFIGURE:
			CONTROLLER::dllConfig();
			break;

		case ID_RSP_CHANGEPLUGIN:
			if (select_plugin(hWnd, PLUGIN_TYPE_RSP)) PLUGIN_SUCCESS(ID_RSP_CONFIGURE)
			else PLUGIN_FAILED(ID_RSP_CONFIGURE)
			break;
		case ID_RSP_CONFIGURE:
			RSP::dllConfig();
			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (GFX::isLoaded())	{ GFX::drawScreen(); }
		EndPaint(hWnd, &ps);
		break;
	case WM_MOVE:
		if (GFX::isLoaded())
		{
			int xPos = (int)(short) LOWORD(lParam);
			int yPos = (int)(short) HIWORD(lParam);
			GFX::moveScreen(xPos, yPos);
		}
		break;
	case WM_DESTROY:
		if (CONTROLLER::isLoaded())	{ CONTROLLER::closeDLL(); }
		if (AUDIO::isLoaded())		{ AUDIO::closeDLL(); }
		if (GFX::isLoaded())		{ GFX::closeDLL(); }
		if (RSP::isLoaded())		{ RSP::closeDLL(); }
		CloseHandle(emuThread);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void Set_Noob64_Directory()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	path_buffer[_MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR];
	char	fname[_MAX_FNAME], ext[_MAX_EXT];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GetModuleFileName(NULL, path_buffer, sizeof(path_buffer));
	_splitpath(path_buffer, drive, dir, fname, ext);

	/* Set the main noob64.exe directory */
	strcpy(main_directory, drive);
	strcat(main_directory, dir);
}
