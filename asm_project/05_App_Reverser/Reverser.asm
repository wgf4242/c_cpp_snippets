.386
.model flat,c
.code

Reverser    proc
            push ebp
            mov ebp,esp
            push esi
            push edi


            xor eax,eax
            mov edi,[ebp+8]          ; y
            mov esi,[ebp+12]         ; x
            mov ecx,[ebp+16]         ; n
            test ecx,ecx

            lea esi,[esi+ecx*4-4]
            pushfd
            std                      ; EFLAGS 寄存器中的 DF 标志。DF 标志设置为 1 时，字符串操作递减变址寄存器（ESI 与/或 EDI）。


@@:            
            lodsd
            mov [edi],eax
            add edi,4
            dec ecx
            jnz @B
            ; @B     ; 向上转移到最近的@@处
            ; @F     ; 向下转移到最近的@@处

            popfd    ; 将栈顶弹入 EFLAGS
 
            mov eax,1

            pop edi
            pop esi
            pop ebp
            retn

Reverser    endp
end
