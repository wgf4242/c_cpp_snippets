.386
.model flat

; 添加 seg001 段，可以不写的,
; 16进制如果是字母开头 要 0a0h, 不要写a0h
seg001 SEGMENT
    DB 22h, 72h, 53h, 52h, 23h, 02h, 0D1h, 15h, 55h, 70h, 0E5h, 70h, 50h, 00h, 06h, 54h, 04h, 55h, 05h, 57h, 53h, 02h, 0Bh, 1h
seg001 ENDS

.data
  ; title好像是保留字 不要用这个名
  msg db 'Hello, World!', 0
  num1    dword    11111111h
  num2    dword    10101010h
  enc     db a0h,34h,56h,78h
  input db 20 dup ('0')  ; 重复指令初始化
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
