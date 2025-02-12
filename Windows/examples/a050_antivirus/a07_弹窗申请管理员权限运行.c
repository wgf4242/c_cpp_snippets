#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wincrypt.h>
#pragma comment(lib, "crypt32.lib")

BOOL IsRunAsAdministrator() {
    BOOL fIsRunAsAdmin = FALSE;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 
        0, 0, 0, 0, 0, 0, &pAdministratorsGroup)) {
        CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin);
        FreeSid(pAdministratorsGroup);
    }

    return fIsRunAsAdmin;
}

void ElevatePrivileges() {
    if (!IsRunAsAdministrator()) {
        char szPath[MAX_PATH];
        if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
            SHELLEXECUTEINFO sei = { sizeof(sei) };
            sei.lpVerb = "runas";
            sei.lpFile = szPath;
            sei.hwnd = NULL;
            sei.nShow = SW_NORMAL;
            if (!ShellExecuteEx(&sei)) {
                exit(1);
            }
            exit(0);
        }
    }
}
int main(int argc, char *argv[]) {
    ElevatePrivileges();
}