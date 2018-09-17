# calc shellcode

Shellcode that opens calc.exe (tested sucessfully on Windows 7)

This shellcode uses the value in HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\AppKey\18 to launch APP_KEY_2 application. Normally this is configured to be calc.exe (on Windows 8 this is NOT configured by default).

There are 3 files:

1) calc_shellcode_vs.cpp - use VS API to facilitate assembly;

2) calc_shellcode_full.cpp - this is the complete Assembly for x86 architecturem null byte free and no hardcode address;

3) calc_shellcode_bin.cpp - this is the real shellcode.


Jean D'Elboux
