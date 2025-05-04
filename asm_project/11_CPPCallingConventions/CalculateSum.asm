.386
.model flat,c
.code

CalculateSum proc

;Function prolog
	push ebp
	mov ebp,esp
	sub esp,12	; allocate local storage space  3¸ö(Temp s1,s2,s3)¼õ12
	push ebx
	push esi
	push edi

;Load arguments
	mov eax,[ebp+8]		; eax = 'a'
	mov ebx,[ebp+12]	; ebx = 'b'
	mov ecx,[ebp+16]	; ecx = 'c'
	mov edx,[ebp+20]	; ebx = 's1'
	mov esi,[ebp+24]	; ebx = 's2'
	mov edi,[ebp+28]	; ebx = 's3'

;Compute s1 = a + b + c
	mov [ebp-12],eax
	add [ebp-12],ebx
	add [ebp-12],ecx

;Compute s2 = a*a + b*b + c*c
	imul eax,eax
	imul ebx,ebx
	imul ecx,ecx
	mov [ebp-8], eax
	add [ebp-8], ebx
	add [ebp-8], ecx

;Compute s3 = a*a*a + b*b*b + c*c*c
	imul eax,[ebp+8]
	imul ebx,[ebp+12]
	imul ecx,[ebp+16]
	mov [ebp-4],eax
	add [ebp-4],ebx
	add [ebp-4],ecx

;Save s1, s2, s3
	mov eax,[ebp-12]
	mov [edx],eax
	mov eax,[ebp-8]
	mov [esi],eax
	mov eax,[ebp-4]
	mov [edi],eax

;Epilog
	pop edi
	pop esi
	pop ebx
	mov esp,ebp
	pop ebp

	ret

CalculateSum endp
			 end
