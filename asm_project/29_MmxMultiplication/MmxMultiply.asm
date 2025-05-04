.model flat,c
.code

MmxMultiply proc
    push ebp
    mov ebp,esp

    movq mm0,[ebp+8]         ; mm0 = 'a'
    movq mm1,[ebp+16]        ; mm1 = 'b'
                             
    movq mm2,mm0             ; mm2 = 'a'
    pmullw mm0,mm1           ; mm0 = product low result
    pmulhw mm1,mm2           ; mm1 = product high result

    movq mm2,mm0             ; mm2 = product low result
    punpcklwd mm0,mm1        ; mm0 = low dword result
    punpckhwd mm2,mm1        ; mm2 = high dword results

    mov eax,[ebp+24]         ; eax = pointer to 'prod_lo
    mov edx,[ebp+28]         ; edx = pointer to 'prod_hi
    movq [eax],mm0           ; save low dword product
    movq [edx],mm2           ; save high dword product

    pop ebp
    ret
MmxMultiply endp
    end
