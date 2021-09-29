//
// Created by alex on 28/09/2021.
//

#ifndef ALEXASI_DINPUT8_H
#define ALEXASI_DINPUT8_H

#include <windows.h>
#include <stdbool.h>

typedef struct _DIOBJECTDATAFORMAT {
	const GUID *pguid;
	DWORD   dwOfs;
	DWORD   dwType;
	DWORD   dwFlags;
} DIOBJECTDATAFORMAT, *LPDIOBJECTDATAFORMAT;
typedef const DIOBJECTDATAFORMAT *LPCDIOBJECTDATAFORMAT;

typedef struct _DIDATAFORMAT {
	DWORD   dwSize;
	DWORD   dwObjSize;
	DWORD   dwFlags;
	DWORD   dwDataSize;
	DWORD   dwNumObjs;
	LPDIOBJECTDATAFORMAT rgodf;
} DIDATAFORMAT, *LPDIDATAFORMAT;
typedef const DIDATAFORMAT *LPCDIDATAFORMAT;

typedef HRESULT (*fn_DirectInput8Create)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);

typedef HRESULT (__stdcall *fn_DllCanUnloadNow)();
typedef HRESULT (__stdcall *fn_DllGetClassObject)(REFCLSID, REFIID, LPVOID*);

typedef HRESULT (__stdcall *fn_DllRegisterServer)();
typedef void    (__stdcall *fn_DllUnregisterServer)();

typedef LPCDIDATAFORMAT (__stdcall *fn_GetdfDIJoystick)();

struct dinput8_dll {
	HMODULE lib;

	fn_DirectInput8Create DirectInput8Create;

	fn_DllCanUnloadNow DllCanUnloadNow;
	fn_DllGetClassObject DllGetClassObject;

	fn_DllRegisterServer DllRegisterServer;
	fn_DllUnregisterServer DllUnregisterServer;
	fn_GetdfDIJoystick GetdfDIJoystick;
};

enum e_DINPUT8_PROC {
	DI_DirectInput8Create,
	DI_DllCanUnloadNow,

	DI_DllGetClassObject,
	DI_GetdfDIJoystick,

	DI_DllRegisterServer,
	DI_DllUnregisterServer,
};

bool dinput8_LoadOriginalLibrary();
bool dinput8_FreeOriginalLibrary();
void* dinput8_FetchOriginalProc(enum e_DINPUT8_PROC proc);

#endif //ALEXASI_DINPUT8_H
