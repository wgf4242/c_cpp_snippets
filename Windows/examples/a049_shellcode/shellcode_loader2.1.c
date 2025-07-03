#pragma comment(linker,"/section:.data,RWE")

unsigned char buf[] = "\xfc\xe8";


void main() {
	_asm {
		lea eax, buf
		call eax
		/// <summary>
			/// 取buf地址，放到exa寄存器
			/// 接着调用exa寄存器
			/// 
			/// buf是放在数据区的，buf的属性在p文件中是只读，不可以执行的
			/// 需要显示的它执行，所以有语句
			/// #pragma comment(linker,"/section:.data,RWE")
			/// </summary>
	}
}