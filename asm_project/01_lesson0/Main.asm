.386
.model flat

; 添加 seg001 段，可以不写的
seg001 SEGMENT
    DB 22h, 72h, 53h, 52h, 23h, 02h, 0D1h, 15h, 55h, 70h, 0E5h, 70h, 50h, 00h, 06h, 54h, 04h, 55h, 05h, 57h, 53h, 02h, 0Bh, 1h
seg001 ENDS

.data
  ; title好像是保留字 不要用这个名
  msg db 'Hello, World!', 0
  
.code
start  PROC
       mov eax,213
       add eax,432
       
       push    offset msg

       ret
start  endp
end    start
