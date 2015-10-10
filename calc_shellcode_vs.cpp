#include "stdafx.h"

int calc_shellcode_vs()
{
	HMODULE hMod = LoadLibraryA("user32.dll");
	FARPROC addr = GetProcAddress(hMod, "keybd_event");

	__asm {
		push ecx
		xor ecx, ecx
		push ecx
		push ecx
		push ecx
		push 0xb7
		mov eax, dword ptr [addr]
		call eax
		pop ecx
	}

	return 0;
}
