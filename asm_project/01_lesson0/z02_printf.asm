.386
.model flat, stdcall
include kernel32.inc
includelib kernel32.lib
include D:\masm32\include\msvcrt.inc
includelib D:\masm32\lib\msvcrt.lib


.data
msg db 'Hello World', 0
format db '%s', 0

.code

Main:
push offset format ; const char *format
push offset msg    ; const char *str
call crt_printf

add esp, 8        ; «Â¿Ì∂—’ª

push 0            ; uExitCode = MessageBox(...)
call ExitProcess

End Main