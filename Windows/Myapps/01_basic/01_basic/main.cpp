#include "windows.h"
#include "tchar.h"

int _tmain(void) {
	MessageBox(NULL, L"Hello World!", L"Title", MB_OK);

	return 0;
}