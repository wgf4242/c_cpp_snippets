.386
.model flat

.data
intArray SWORD 0,0,0,0,4,3,0,-34,-56,7,8
;intArray SWORD 0,0,0,0,0,0,0,0,0,0,0

.code
main	proc
		mov ebx,OFFSET intArray
		mov ecx,LENGTHOF intArray
		
L1:
		cmp WORD PTR[ebx],0        ;查找不为0的数
		jnz found
		add ebx,2
		loop L1
		jmp notFound

found:
		movsx eax,WORD  PTR[ebx]
		jmp quit

notFound:
		mov eax,999999  ; F423F

quit:
		ret

main	endp
end		main


