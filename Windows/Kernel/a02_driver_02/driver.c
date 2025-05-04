#include<ntifs.h>

#define kprintf(format, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, format, ##__VA_ARGS__)

#define MY_COMPONENT_ID 0x1234
#define MY_DEBUG_LEVEL  0


void DriverUnload(PDRIVER_OBJECT pDriver) {
	UNREFERENCED_PARAMETER(pDriver); // 告诉编译器我们有意不使用此参数
	kprintf(("Line %d:xia0ji233: unload success\n"), __LINE__);
	DbgPrint("Driver01 Unload");
}

NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath
) {
	DriverObject->DriverUnload = DriverUnload;
	kprintf(("RegistryPath = %S\n"), RegistryPath->Buffer);
	DbgPrint("Driver01 Loaded");
	DbgPrintEx(MY_COMPONENT_ID, MY_DEBUG_LEVEL,         "MyDriverFunction was called0, Enable Verbose Kernel Output 时有我\n");
	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "MyDriverFunction was called1. All view 有我\n");
	kprintf(("Line %d:xia0ji233: work success\n"), __LINE__);
	return 0;
}
