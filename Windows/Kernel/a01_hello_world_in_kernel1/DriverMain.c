#include <ntddk.h>


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver,
	PUNICODE_STRING pReg)
{
	DbgPrint("Hello World\n");
	DbgPrint("RegPath: %wZ\n", *pReg);
}