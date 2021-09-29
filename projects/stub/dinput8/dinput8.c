//
// Created by alex on 28/09/2021.
//

#define _CRT_SECURE_NO_WARNINGS
#include "dinput8.h"

struct dinput8_dll dinput8;

bool dinput8_LoadOriginalLibrary() {
#define PROC_CHECK(x)          \
	if (!(x)) {                    \
		return false;               \
	}

	HMODULE lib;

	{
		wchar_t lib_path[MAX_PATH];

		if (!GetSystemDirectory(lib_path, sizeof(lib_path)))
			return false;

		wcscat(lib_path, L"//dinput8.dll");

		lib = LoadLibrary(lib_path);
		PROC_CHECK(lib)
		dinput8.lib = lib;
	}

	{
		dinput8.DirectInput8Create = NULL;

		dinput8.DllCanUnloadNow = NULL;
		dinput8.DllGetClassObject = NULL;

		dinput8.DllRegisterServer = NULL;
		dinput8.DllUnregisterServer = NULL;

		dinput8.GetdfDIJoystick = NULL;
	}

	FARPROC proc;

	{
		proc = GetProcAddress(lib, "DirectInput8Create");
		PROC_CHECK(proc)
		dinput8.DirectInput8Create = (fn_DirectInput8Create) proc;
	}

	{
		proc = GetProcAddress(lib, "DllCanUnloadNow");
		PROC_CHECK(proc)
		dinput8.DllCanUnloadNow = (fn_DllCanUnloadNow) proc;
	}

	{
		proc = GetProcAddress(lib, "DllGetClassObject");
		PROC_CHECK(proc)
		dinput8.DllGetClassObject = (fn_DllGetClassObject) proc;
	}

	{
		proc = GetProcAddress(lib, "DllRegisterServer");
		PROC_CHECK(proc)
		dinput8.DllRegisterServer = (fn_DllRegisterServer) proc;
	}

	{
		proc = GetProcAddress(lib, "DllUnregisterServer");
		PROC_CHECK(proc)
		dinput8.DllUnregisterServer = (fn_DllUnregisterServer) proc;
	}

	{
		proc = GetProcAddress(lib, "GetdfDIJoystick");
		PROC_CHECK(proc)
		dinput8.GetdfDIJoystick = (fn_GetdfDIJoystick) proc;
	}

#undef PROC_CHECK
	return true;
}

bool dinput8_FreeOriginalLibrary() {
	if (dinput8.lib) {
		FreeLibrary(dinput8.lib);
	}

	return true;
}

void *dinput8_FetchOriginalProc(enum e_DINPUT8_PROC proc) {
	switch (proc) {
		case DI_DirectInput8Create: {
			return (void*) dinput8.DirectInput8Create;
		}

		case DI_DllCanUnloadNow: {
			return (void*) dinput8.DllCanUnloadNow;
		}

		case DI_DllRegisterServer: {
			return (void*) dinput8.DllRegisterServer;
		}

		case DI_DllUnregisterServer: {
			return (void*) dinput8.DllUnregisterServer;
		}

		case DI_DllGetClassObject: {
			return (void*) dinput8.DllGetClassObject;
		}

		case DI_GetdfDIJoystick: {
			return (void*) dinput8.GetdfDIJoystick;
		}

		default: {
			return NULL;
		}
	}
}
