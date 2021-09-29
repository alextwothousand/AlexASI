//
// Created by alex on 28/09/2021.
//

#include <windows.h>
#include "dinput8/dinput8.h"

typedef bool (*fn_AlexASI_Init)();
typedef bool (*fn_AlexASI_Exit)();

HMODULE asi_lib;
fn_AlexASI_Init fn_asi_init;
fn_AlexASI_Exit fn_asi_exit;

BOOL WINAPI DllMain(HMODULE hModule, DWORD fdwReason, void* lpReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH: {
			if (!dinput8_LoadOriginalLibrary()) {
				return FALSE;
			}

			asi_lib = LoadLibrary(L"AlexASI.dll");
			if (!asi_lib) {
				return FALSE;
			}

			{
				FARPROC proc = GetProcAddress(asi_lib, "AlexASI_Init");
				if (!proc) {
					return FALSE;
				}

				fn_asi_init = (fn_AlexASI_Init) proc;
			}

			{
				FARPROC proc = GetProcAddress(asi_lib, "AlexASI_Exit");
				if (!proc) {
					return FALSE;
				}

				fn_asi_exit = (fn_AlexASI_Exit) proc;
			}

			return fn_asi_init();
		}

		case DLL_PROCESS_DETACH: {
			dinput8_FreeOriginalLibrary();
			fn_asi_exit();
			FreeLibrary(asi_lib);

			return TRUE;
		}

		default: {
			return TRUE;
		}
	}
}

HRESULT __stdcall stub_DirectInput8Create(HINSTANCE hInst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter) {
	fn_DirectInput8Create fn = (fn_DirectInput8Create) dinput8_FetchOriginalProc(DI_DirectInput8Create);

	HRESULT result = fn(hInst, dwVersion, riidltf, ppvOut, punkOuter);

	return result;
}

HRESULT __stdcall stub_DllCanUnloadNow() {
	fn_DllCanUnloadNow fn = (fn_DllCanUnloadNow) dinput8_FetchOriginalProc(DI_DllCanUnloadNow);

	HRESULT result = fn();

	return result;
}

HRESULT __stdcall stub_DllGetClassObject(REFCLSID x, REFIID y, LPVOID* z) {
	fn_DllGetClassObject fn = (fn_DllGetClassObject) dinput8_FetchOriginalProc(DI_DllGetClassObject);

	HRESULT result = fn(x, y, z);

	return result;
}

HRESULT __stdcall stub_DllRegisterServer() {
	fn_DllRegisterServer fn = (fn_DllRegisterServer) dinput8_FetchOriginalProc(DI_DllRegisterServer);

	HRESULT result = fn();

	return result;
}

void __stdcall stub_DllUnregisterServer() {
	fn_DllUnregisterServer fn = (fn_DllUnregisterServer) dinput8_FetchOriginalProc(DI_DllUnregisterServer);
	fn();
}

LPCDIDATAFORMAT __stdcall stub_GetdfDIJoystick() {
	fn_GetdfDIJoystick fn = (fn_GetdfDIJoystick) dinput8_FetchOriginalProc(DI_GetdfDIJoystick);

	LPCDIDATAFORMAT result = fn();

	return result;
}