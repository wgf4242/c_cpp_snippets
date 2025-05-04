.model flat,c
.code

SsePackedInt16_Add proc
    push ebp
    mov ebp,esp

    mov eax,[ebp+8]                    ; eax = pointer to a
    mov ecx,[ebp+12]                   ; ecx = pointer to b
    mov edx,[ebp+16]                   ; edx = pointer to c
                                       ; 
    movdqa xmm0,[eax]                  ; xmm0 = a
    movdqa xmm1,xmm0                   ; copy content of xmm0 into xmm1
    movdqa xmm2,[ecx]                  ; xmm2 = b
; Addition                             ; 
    paddw xmm0,xmm2                    ; packed add - wraparound
    paddsw xmm1,xmm2                   ; packed add - satureted
; Save result                          ; 
    movdqa [edx],xmm0                  ; save wraparound at c[0]
    movdqa [edx+16],xmm1               ; save saturated at c[1]

    pop ebp
    ret
SsePackedInt16_Add endp

SsePackedInt32_Sub proc
    push ebp
    mov ebp,esp
    
    mov eax,[ebp+8]                    ; eax = pointer to a
    mov ecx,[ebp+12]                   ; ecx = pointer to b
    mov edx,[ebp+16]                   ; edx = pointer to c

; Subtraction
    movdqa xmm0,[eax]                  ; xmm0 = a
    psubd  xmm0,[ecx]                  ; xmm0 = a - b
; Save
    movdqu [edx],xmm0                  ; dqu - unalign不用对齐, dqa要对齐
    pop ebp
    ret

SsePackedInt32_Sub endp

SsePackedInt32_Mul proc
    push ebp
    mov ebp,esp

    mov eax,[ebp+8]                    ; eax = pointer to a
    mov ecx,[ebp+12]                   ; ecx = pointer to b
    mov edx,[ebp+16]                   ; edx = pointer to c

    ; Load parameters
    movdqa xmm0,[eax]
    movdqa xmm1,[ecx]

    movdqa xmm2,xmm0
    pmulld xmm0,xmm1                   ; signed dword mul - low result
    pmuldq xmm2,xmm1                   ; signed dword mul - qword result

    movdqa [edx],xmm0                  ; c[0] = pmulld result
    movdqa [edx+16],xmm2               ; c[1] = pmulld result

    pop ebp
    ret
SsePackedInt32_Mul endp
    end