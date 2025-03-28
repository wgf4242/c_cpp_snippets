#include <iostream>
#include <windows.h>


// Define the function signature
typedef void (*HelloFunc)();

int main()
{
	HINSTANCE hGetProcIDDLL = LoadLibrary(L"example.dll");

	if (!hGetProcIDDLL) {
		std::cerr << "Could not load the dynamic library" << std::endl;
		return EXIT_FAILURE;
	}

	HelloFunc hello = (HelloFunc)GetProcAddress(hGetProcIDDLL, "hello");

	if (!hello) {
		std::cerr << "Could not locate the function" << std::endl;
		return EXIT_FAILURE;
	}

	hello();

	//FreeLibrary(hGetProcIDDLL);
	return 0;
}
