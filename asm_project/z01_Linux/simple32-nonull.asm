; hello world in 32-bit assembly for Linux

; nasm -f elf32 simple32-nonull.asm -o simple32-nonull.o
; ld -m elf_i386 simple32-nonull.o -o simple32-nonull
; ./sc.sh simple32-nonull
; \x31\xc0\xb0\x04\x31\xdb\xb3\x01\xeb\x0f\x59\x31\xd2\xb2\x11\xcd\x80\x31\xc0\xb0\x01\x31\xdb\xcd\x80\xe8\xec\xff\xff\xff\x48\x65\x6c\x6c\x6f\x2c\x20\x52\x65\x76\x65\x72\x73\x65\x72\x21\x0aphil@i3touch:~/InfiniteSkills/Reversing$

    global _start
    section .text
_start:
    ; write is system call 4
    xor     eax, eax                ; zero out eax
    mov     al, 4                   ; system call 4 is write
    xor     ebx, ebx                ; zero out ebx
    mov     bl, 1                   ; file handle 1 is stdout
    ;mov     ecx, message           ; address of string to output
    jmp short call_shellcode
return_shellcode:
    pop     ecx
    xor     edx, edx                ; zero out edx
    mov     dl, 17                  ; number of bytes
    int     0x80                    ; invoke syscall

    ; exit(0)
    xor     eax, eax                ; zero out eax
    mov     al, 1                   ; system call 1 is exit
    xor     ebx, ebx                ; exit code 0
    int     0x80                    ; invoke operating system to exit

call_shellcode:
    call return_shellcode
    db      "Hello, Reverser!", 10  ; 10 is a newline