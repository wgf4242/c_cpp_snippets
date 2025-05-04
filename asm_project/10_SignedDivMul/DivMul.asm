.386
.model flat,c
.code

;Return	: 0 Error (Division by zero)
;		: 1 Success
;Cmputation *prod = a*b
;			*quo = a/b
;			*rem = a % b

IntegerMulDiv	proc
				
				push ebp
				mov ebp, esp
				push ebx

				xor eax,eax

				mov ecx,[ebp+8]		;ecx = 'a'
				mov edx,[ebp+12]	;edx = 'b'
				
				or edx,edx
				jz InvalidDivisor

				imul edx,ecx		;edx = 'a' * 'b'
				
				mov ebx,[ebp+16]	;ebx = 'prod'
				mov [ebx],edx

				mov eax,ecx			;eax = 'a'
				cdq					;edx:eax contains dividend

				idiv dword ptr[ebp+12]
				
				mov ebx,[ebp+20]	;quo
				mov [ebx],eax			;*quo = quotient
				mov ebx,[ebp+24]	;rem
				mov [ebx],edx			;*rem = remainder
				mov eax,1					;rv
	
	InvalidDivisor:
				pop ebx
				pop ebp
				ret

IntegerMulDiv	endp
				end




					