.386
.model flat

; ��� seg001 �Σ����Բ�д��,
; 16�����������ĸ��ͷ Ҫ 0a0h, ��Ҫдa0h
seg001 SEGMENT
    DB 22h, 72h, 53h, 52h, 23h, 02h, 0D1h, 15h, 55h, 70h, 0E5h, 70h, 50h, 00h, 06h, 54h, 04h, 55h, 05h, 57h, 53h, 02h, 0Bh, 1h
seg001 ENDS

.data
  ; title�����Ǳ����� ��Ҫ�������
  msg db 'Hello, World!', 0
  num1    dword    11111111h
  num2    dword    10101010h
  enc     db a0h,34h,56h,78h
  input db 20 dup ('0')  ; �ظ�ָ���ʼ��
  bytesWritten DWORD ?

.code
start  PROC
       mov eax,213
       add eax,432

LP:       
       push    offset msg
       
       loop LP
       ; jle LP
       xor eax,eax
       ret
start  endp
end    start
