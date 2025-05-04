.model flat,c
.const

DegRoRad    real8   0.017453229252
RadToDeg    real8   57.2957795131

.code
; Rectangular to Polar notation converter
RectToPolar proc
        push ebp
        mov ebp,esp

        fld real8 ptr [ebp+16]       ; load y
        fld real8 ptr [ebp+8]        ; load x

        fpatan                       ; calc atan2 (y/x)
        fmul[RadToDeg]
        mov eax,[ebp+28]
        fstp real8 ptr [eax]


        fld real8 ptr [ebp+8]        ; load x
        fmul st(0),st(0)             ; x*x
        fld real8 ptr [ebp+16]
        fmul st(0),st(0)             ; y*y

        faddp                        ; x*x + y*y

        fsqrt                        ; sqrt(x*x + y*y)

        mov eax,[ebp+24]
        fstp real8 ptr[eax]

        pop ebp
        ret
RectToPolar endp

; Polar to Rectangular notation converter

PolarToRect proc
        push ebp
        mov ebp,esp

        fld real8 ptr [ebp+16]       ; load angle in degrees
        fmul [DegRoRad]              ; convet angle to radians

        fsincos                      ; calc sin(ST(0)) and cos(ST(0))
        fmul real8 ptr [ebp+8]       ; y = r * cos(a)
        mov eax,[ebp+24]
        fstp real8 ptr [eax]         ; save x

        fmul real8 ptr [ebp+8]       ; y = r * sin(a)
        mov eax,[ebp+28]
        fstp real8 ptr [eax]         ; save y

        pop ebp
        ret
PolarToRect endp
        end
