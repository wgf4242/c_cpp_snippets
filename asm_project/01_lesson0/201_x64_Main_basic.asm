; https://blog.csdn.net/qiuzen/article/details/125014584
.data
text db 'Hello World', 0
caption db 'Selph First x64 Application', 0
 
.code
start proc
sub rsp,28h ; ��������ǰ��ҪԤ��Ӱ�ӿռ䣬����rsp
xor r9d,r9d
lea r8, caption
lea rdx, text
xor rcx,rcx
add rsp,28h
start ENDP
END ; ���ֱ��end������ָ������