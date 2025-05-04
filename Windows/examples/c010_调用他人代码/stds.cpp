
DWORD GetHashCode(const char* strings) {
	DWORD dRet = 0;
	DWORD seed = 1 - (DWORD)strings;
	while (*strings)
	{
		dRet = dRet + (seed + (DWORD)strings) * (*strings);
		dRet = -(dRet % 0x8000000B) * 0x11;
		strings++;
	}

	return dRet ^ 0x12345678;
}
