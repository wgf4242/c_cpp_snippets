.CODE

myAdd PROC
    add rcx,rdx
    mov rax,rcx
    ret
myAdd ENDP

EXTERN myAddOne:PROC     ;引用外部函数

myAdd1 PROC
    add rcx,rdx
    call myAddOne
    mov rax,rcx
    ret
myAdd1 ENDP

END