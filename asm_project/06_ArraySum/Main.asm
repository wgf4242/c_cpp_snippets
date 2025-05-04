.386
.model flat

.data
intArray DWORD 10000h,20000h,30000h,40000h;

.code
start	proc
		mov edi, OFFSET intArray    ; intArrayµØÖ·¸ø edi
		mov ecx, LENGTHOF intArray
		mov eax, 0

LP:
		add eax, [edi]
		add edi, TYPE intArray
		loop LP
		ret

start endp
end start
