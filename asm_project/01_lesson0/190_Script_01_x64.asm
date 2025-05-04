.data
    box db 'sundosnapxnsodkshgds', 0
    ;input db '00000000000000000000', 0
    input db 20 dup ('0')
    enc   db 0d9h, 0e1h, 0d5h, 0c9h, 0f8h, 0b8h, 0d5h, 0fdh, 0d3h, 0f2h, 0fdh, 0d0h, 0b6h, 0cfh, 0e4h, 0f6h, 8bh, 0ddh, 0d3h, 0f2h


.code
main proc

    mov cl, 0
LP:
    lea rax, [box + rcx]
    lea rax, [rax+5]
    not ax
    lea  rbx, [input + rcx]
    lea rbx, [rbx-8]
    xor rax,rbx
    mov byte ptr [enc + rcx], al
    lea rcx, [rcx+1]
    mov rax, 20
    cmp rax,rcx
    jge LP

    xor rax, rax
    ret
main endp
end