#pragma once
#include <Windows.h>
typedef DWORD(*GetHashCodePtr)(const char* strings);
DWORD GetHashCode(const char* strings);
