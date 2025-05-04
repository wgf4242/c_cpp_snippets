.386
.model flat,c
.code

AdderASM proc
		push ebp
		mov ebp,esp
		
		mov eax,[ebp+8]		;eax = 'a'
		mov ecx,[ebp+12]	;ecx = 'b'
		mov edx,[ebp+16]	;edx = 'c'
		
		add eax,ecx			;eax = 'a' + 'b'
		add eax,edx			;eax = 'a' + 'b' + 'c'
		
		pop ebp

		ret
AdderASM endp
		 end