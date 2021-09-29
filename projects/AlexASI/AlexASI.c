// AlexASI.cpp : Defines the entry point for the application.
//

#include "AlexASI.h"
#include <windows.h>

bool __declspec(dllexport) AlexASI_Init() {
	// DLL_PROCESS_ATTACH
	MessageBox(NULL, L"MessageBoxW", L"Nice", MB_OK | MB_ICONEXCLAMATION);
	return true;
}

bool __declspec(dllexport) AlexASI_Exit() {
	// DLL_PROCESS_DETACH
	MessageBox(NULL, L"MessageBoxW", L"Goodbye mens!", MB_OK | MB_ICONEXCLAMATION);
	return true;
}