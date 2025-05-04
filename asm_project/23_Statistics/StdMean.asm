.model flat,c
.code

CalcMeanStdevASM proc

    push ebp
    mov ebp,esp
    sub esp,4

    xor eax,eax
    mov ecx,[ebp+12]    ; ecx = 'n'
    cmp ecx,1
    jle Done
    dec ecx

    mov [ebp-4],ecx     ; save n-1

    inc ecx

    mov edx,[ebp+8]     ; edx = 'a'
    fldz                ; sum = 0.0

@@: fadd real8 ptr[edx] ; sum += *a
    add edx,8           ; a++
    dec ecx
    jnz @B
    fidiv dword ptr[ebp+12] ; mean = sum/n

    mov edx,[ebp+8]         ; edx = 'a'
    mov ecx,[ebp+12]        ; n
    fldz                    ; sum = 0.0, ST(1)=mean

@@: fld real8 ptr[edx]      ; ST(0) = *a
    fsub st(0),st(2)        ; ST(0) = *a - mean
    fmul st(0),st(0)        ; ST(0) = (*a - mean)^2
    faddp                   ; update sum
    add edx,8
    dec ecx
    jnz @B

    fidiv dword ptr [ebp-4] ; var sum/(n-1)
    fsqrt

    mov eax,[ebp+20]
    fstp real8 ptr [eax]
    mov eax,[ebp+16]
    fstp real8  ptr [eax]
    mov eax,1

Done: mov esp,ebp
    pop ebp
    ret

CalcMeanStdevASM endp
    end