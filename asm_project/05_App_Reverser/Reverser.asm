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
            std                      ; EFLAGS �Ĵ����е� DF ��־��DF ��־����Ϊ 1 ʱ���ַ��������ݼ���ַ�Ĵ�����ESI ��/�� EDI����


@@:            
            lodsd
            mov [edi],eax
            add edi,4
            dec ecx
            jnz @B
            ; @B     ; ����ת�Ƶ������@@��
            ; @F     ; ����ת�Ƶ������@@��

            popfd    ; ��ջ������ EFLAGS
 
            mov eax,1

            pop edi
            pop esi
            pop ebp
            retn

Reverser    endp
end
