.386
.model flat,c

    extern GlChar:byte
    extern GlShort:word
    extern GlInt:dword
    extern GlLongLong:qword

    .code

IntegerAddition proc
    push ebp
    mov ebp,esp

;Compute GlChar +=a
    mov al,[ebp+8]
    add [GlChar], al

;Compute GlShort +=b
    mov ax,[ebp+12]
    add [GlShort],ax

;Compute GlInt +=c
    mov eax,[ebp+16]
    add [GlInt],eax

;Compute GlLongLong +=d
    mov eax,[ebp+20]
    mov edx,[ebp+24]
    add dword ptr[GlLongLong],eax
    add dword ptr[GlLongLong+4],edx

    pop ebp
    ret
IntegerAddition endp
    end