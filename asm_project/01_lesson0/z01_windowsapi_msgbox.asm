; title 关键字不能用
.386
.model flat, stdcall
include kernel32.inc
includelib kernel32.lib
include user32.inc
includelib user32.lib

.data
titlea db 'Win32', 0
msg db 'Hello World', 0

.code

Main:
push 0            ; uType = MB_OK
push offset titlea ; LPCSTR lpCaption
push offset msg   ; LPCSTR lpText
push 0            ; hWnd = HWND_DESKTOP
call MessageBoxA
push eax          ; uExitCode = MessageBox(...)
call ExitProcess

End Main