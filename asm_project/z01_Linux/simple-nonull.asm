; hello world in 64-bit assembly for Linux

; nasm -f elf64 simple-nonull.asm -o simple-nonull.o
; ld simple-nonull.o -o simple-nonull
; ./simple-nonull
; Hello, Reverser!
; ./sc.sh simple-nonull
; \x48\x31\xc0\xb0\x01\x48\x31\xff\x48\xff\xc7\xeb\x12\x5e\x48\x31\xd2\xb2\x11\x0f\x05\x48\x31\xc0\xb0\x3c\x48\x31\xff\x0f\x05\xe8\xe9\xff\xff\xff\x48\x65\x6c\x6c\x6f\x2c\x20\x52\x65\x76\x65\x72\x73\x65\x72\x21\x0a

    global _start
    section .text
_start:
    ; write is system call 1
    xor     rax, rax                ; zero out rax
    mov     al, 1                   ; system call 1 is write
    xor     rdi, rdi                ; zero out rdi
    inc     rdi                     ; file handle 1 is stdout
    ;mov     rsi, message           ; address of string to output
    jmp short call_shellcode        ; get that address
return_shellcode:
    pop     rsi
    xor     rdx, rdx                ; zero out rdx
    mov     dl, 17                  ; number of bytes
    syscall                         ; invoke syscall

    ; exit(0)
    xor     rax, rax                ; zero out rax
    mov     al, 60                  ; system call 60 is exit
    xor     rdi, rdi                ; exit code 0
    syscall                         ; invoke operating system to exit

call_shellcode:
    call return_shellcode
    db      "Hello, Reverser!", 10  ; 10 is a newline