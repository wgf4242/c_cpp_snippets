.model flat,c
.code

MmxShifter proc
            push ebp
            mov ebp,esp

            xor eax,eax
            mov edx,[ebp+16]
            cmp edx,ShiftOpTableCount
            jae BadShiftOp

            mov eax,1                          ; set success return code
            movq mm0,[ebp+8]                   ; load 'a'
            movd mm1,dword ptr [ebp+20]        ; load 'count' into low dword
            jmp [ShiftOpTable+edx*4]

MmxPsllw:   psllw mm0, mm1                      ; shift left logical word
            jmp SaveResult

MmxPsrlw:   psrlw mm0, mm1                      ; shift right logical word
            jmp SaveResult

MmxPsraw:   psraw mm0, mm1                      ; shift right arithmetic word
            jmp SaveResult

MmxPslld:   pslld mm0, mm1                      ; shift left logical dword
            jmp SaveResult

MmxPsrld:   psrld mm0, mm1                      ; shift right logical dword
            jmp SaveResult

MmxPsrad:   psrad mm0, mm1                      ; shift right arithmetic dword
            jmp SaveResult

BadShiftOp: pxor mm0,mm0


SaveResult: mov edx,[ebp+24]
            movq [edx],mm0
            emms
            pop ebp

            ret

            align 4

ShiftOpTable:
            dword MmxPsllw, MmxPsrlw, MmxPsraw
            dword MmxPslld, MmxPsrld, MmxPsraw


ShiftOpTableCount   equ ($- ShiftOpTable)/size dword

MmxShifter  endp
        end