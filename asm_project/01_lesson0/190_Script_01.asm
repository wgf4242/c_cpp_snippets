; 2023工业信息安全技能大赛\钢铁行业锦标赛\05easy_vm
.386
.model flat,c

.data
    box db 'sundosnapxnsodkshgds', 0
    ;input db '00000000000000000000', 0
    input db 20 dup ('0')
    enc   db 0d9h, 0e1h, 0d5h, 0c9h, 0f8h, 0b8h, 0d5h, 0fdh, 0d3h, 0f2h, 0fdh, 0d0h, 0b6h, 0cfh, 0e4h, 0f6h, 8bh, 0ddh, 0d3h, 0f2h


.code
main proc

    mov ecx, 0
LP:
    lea eax, [box + ecx]
    lea eax, [eax + 5]
    not ax
    lea ebx, [input + ecx]
    lea ebx, [ebx - 8]
    xor eax, ebx
    mov byte ptr [enc + ecx], al
    lea ecx, [ecx + 1]
    mov eax, 20
    cmp eax, ecx
    jle LP

    xor eax, eax
    ret
main endp
end