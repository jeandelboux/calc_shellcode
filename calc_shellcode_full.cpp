#include "stdafx.h"

int calc_shellcode_full()
{
	HMODULE hMod = LoadLibraryA("user32.dll");
	FARPROC addr = GetProcAddress(hMod, "keybd_event");

	/*
	There are 2 ways to open calc using keyboard input:
	keybd_event - supersed of SendInput (simpler way)
	SendInput - calling direclty the function that actually
	perform the actions of openning calc (when passing 0xb7)
	I prefered to use keybd_event so shellcode is smaller.
	This is the 32bits version.

	// Using SendInput
	INPUT input = { 0 };
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = 0xb7;
	SendInput(1, &input, 28);

	// Using keybd_event
	//keybd_event(0xb7, 0, 0, 0);
	*/
	DWORD x = __readfsdword(0x30);
	__asm {
		xor edx, edx					// edx = 0
			mov esi, dword ptr fs : [0x30]	// ESI = [TEB + 0x30] = PEB
			mov esi, [esi + 0x0c]			// ESI = [PEB + 0x0C] = PEB_LDR_DATA
			mov esi, [esi + 0x0c]			// ESI = [PEB_LDR_DATA + 0x0C] = LDR_MODULE InLoadOrder[0](process)
			lodsd							// EAX = InLoadOrder[1](ntdll)
			mov esi, [eax]					// ESI = InLoadOrder[2](kernel32)
			mov edi, [esi + 0x18]			// EDI = [InLoadOrder[2] + 0x18] = kernel32 DllBase

			mov eax, addr
			push edx
			push edx
			push edx
			push 0xb7
			call eax
	}

	return 0;
}
