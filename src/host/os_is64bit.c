/**
 * \file   os_is64bit.c
 * \brief  Native code-side checking for a 64-bit architecture.
 * \author Copyright (c) 2011 Jason Perkins and the Premake project
 */

#include "premake.h"

#if PLATFORM_WINDOWS
typedef BOOL(WINAPI* WowFuncSig)(HANDLE, PBOOL);
#endif

int os_is64bit(lua_State* L)
{
#if PLATFORM_WINDOWS
	HMODULE hKrnl32 = GetModuleHandle(TEXT("kernel32"));
#endif
	if (sizeof(void*) == 8) // our premake build is 64-bit, so the runtime environment must be also (at least) 64-bit ...
	{
		lua_pushboolean(L, 1);
		return 1;
	}
	// If this code returns true, then the platform is 64-bit. If it
	// returns false, the platform might still be 64-bit, but more 
	// checking will need to be done on the Lua side of things.
#if PLATFORM_WINDOWS
	if (hKrnl32)
	{
		WowFuncSig func = (WowFuncSig)GetProcAddress(hKrnl32, "IsWow64Process");
		if (func)
		{
			BOOL isWow = FALSE;
			if (func(GetCurrentProcess(), &isWow))
			{
				lua_pushboolean(L, isWow);
				return 1;
			}
		}
	}
#endif

	lua_pushboolean(L, 0);
	return 1;
}
