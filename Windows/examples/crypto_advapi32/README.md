# ADVAPI32 Functions 

https://www.geoffchappell.com/studies/windows/win32/advapi32/history/index.htm

The large table on this page lists all the functions that appear in the export  directory of any known version of ADVAPI32.DLL. For each function, the table gives  just a brief summary of the applicable ADVAPI32 versions and of the function’s status  with respect to Microsoft’s documentation. 

This master list is the key to other lists. More detail on each function’s availability  and documentation status may be found by looking for each function in other lists  according to the function’s first version. In the Table of Contents, expand the  entry for [ADVAPI32 Versions](https://www.geoffchappell.com/studies/windows/win32/advapi32/history/index.htm) to get pages for  each version. Additional explanatory notes follow the table. 

| Function                                             | Applicable Versions                                          | Documentation Status |
| ---------------------------------------------------- | ------------------------------------------------------------ | -------------------- |
| A_SHAFinal                                           | 5.1 and higher                                               |                      |
| A_SHAInit                                            | 5.1 and higher                                               |                      |
| A_SHAUpdate                                          | 5.1 and higher                                               |                      |
| AbortSystemShutdownA                                 | 3.10 and higher                                              | documented           |
| AbortSystemShutdownW                                 | 3.10 and higher                                              | documented           |
| AccessCheck                                          | 3.10 and higher                                              | documented           |
| AccessCheckAndAuditAlarmA                            | 3.10 and higher                                              | documented           |
| AccessCheckAndAuditAlarmW                            | 3.10 and higher                                              | documented           |
| AccessCheckByType                                    | 5.0 and higher                                               | documented           |
| AccessCheckByTypeAndAuditAlarmA                      | 5.0 and higher                                               | documented           |
| AccessCheckByTypeAndAuditAlarmW                      | 5.0 and higher                                               | documented           |
| AccessCheckByTypeResultList                          | 5.0 and higher                                               | documented           |
| AccessCheckByTypeResultListAndAuditAlarmA            | 5.0 and higher                                               | documented           |
| AccessCheckByTypeResultListAndAuditAlarmByHandleA    | 5.0 and higher                                               | documented           |
| AccessCheckByTypeResultListAndAuditAlarmByHandleW    | 5.0 and higher                                               | documented           |
| AccessCheckByTypeResultListAndAuditAlarmW            | 5.0 and higher                                               | documented           |
| AddAccessAllowedAce                                  | 3.10 and higher                                              | documented           |
| AddAccessAllowedAceEx                                | 5.0 and higher                                               | documented           |
| AddAccessAllowedObjectAce                            | 5.0 and higher                                               | documented           |
| AddAccessDeniedAce                                   | 3.10 and higher                                              | documented           |
| AddAccessDeniedAceEx                                 | 5.0 and higher                                               | documented           |
| AddAccessDeniedObjectAce                             | 5.0 and higher                                               | documented           |
| AddAce                                               | 3.10 and higher                                              | documented           |
| AddAuditAccessAce                                    | 3.10 and higher                                              | documented           |
| AddAuditAccessAceEx                                  | 5.0 and higher                                               | documented           |
| AddAuditAccessObjectAce                              | 5.0 and higher                                               | documented           |
| AddConditionalAce                                    | 6.1 and higher                                               | documented           |
| AddMandatoryAce                                      | 6.0 and higher                                               | documented           |
| AddUsersToEncryptedFile                              | 5.0 and higher                                               | documented           |
| AddUsersToEncryptedFileEx                            | 6.0 and higher                                               |                      |
| AdjustTokenGroups                                    | 3.10 and higher                                              | documented           |
| AdjustTokenPrivileges                                | 3.10 and higher                                              | documented           |
| AllocateAndInitializeSid                             | 3.10 and higher                                              | documented           |
| AllocateLocallyUniqueId                              | 3.10 and higher                                              | documented           |
| AreAllAccessesGranted                                | 3.10 and higher                                              | documented           |
| AreAnyAccessesGranted                                | 3.10 and higher                                              | documented           |
| AuditComputeEffectivePolicyBySid                     | 6.0 and higher                                               | documented           |
| AuditComputeEffectivePolicyByToken                   | 6.0 and higher                                               | documented           |
| AuditEnumerateCategories                             | 6.0 and higher                                               | documented           |
| AuditEnumeratePerUserPolicy                          | 6.0 and higher                                               | documented           |
| AuditEnumerateSubCategories                          | 6.0 and higher                                               | documented           |
| AuditFree                                            | 6.0 and higher                                               | documented           |
| AuditLookupCategoryGuidFromCategoryId                | 6.0 and higher                                               | documented           |
| AuditLookupCategoryIdFromCategoryGuid                | 6.0 and higher                                               | documented           |
| AuditLookupCategoryNameA                             | 6.0 and higher                                               | documented           |
| AuditLookupCategoryNameW                             | 6.0 and higher                                               | documented           |
| AuditLookupSubCategoryNameA                          | 6.0 and higher                                               | documented           |
| AuditLookupSubCategoryNameW                          | 6.0 and higher                                               | documented           |
| AuditQueryGlobalSaclA                                | 6.1 and higher                                               |                      |
| AuditQueryGlobalSaclW                                | 6.1 and higher                                               |                      |
| AuditQueryPerUserPolicy                              | 6.0 and higher                                               | documented           |
| AuditQuerySecurity                                   | 6.0 and higher                                               | documented           |
| AuditQuerySystemPolicy                               | 6.0 and higher                                               | documented           |
| AuditSetGlobalSaclA                                  | 6.1 and higher                                               |                      |
| AuditSetGlobalSaclW                                  | 6.1 and higher                                               |                      |
| AuditSetPerUserPolicy                                | 6.0 and higher                                               | documented           |
| AuditSetSecurity                                     | 6.0 and higher                                               | documented           |
| AuditSetSystemPolicy                                 | 6.0 and higher                                               | documented           |
| BackupEventLogA                                      | 3.10 and higher                                              | documented           |
| BackupEventLogW                                      | 3.10 and higher                                              | documented           |
| BaseRegCloseKey                                      | 6.2 and higher                                               |                      |
| BaseRegCreateKey                                     | 6.2 and higher                                               |                      |
| BaseRegDeleteKeyEx                                   | 6.2 and higher                                               |                      |
| BaseRegDeleteValue                                   | 6.2 and higher                                               |                      |
| BaseRegFlushKey                                      | 6.2 and higher                                               |                      |
| BaseRegGetVersion                                    | 6.2 and higher                                               |                      |
| BaseRegLoadKey                                       | 6.2 and higher                                               |                      |
| BaseRegOpenKey                                       | 6.2 and higher                                               |                      |
| BaseRegRestoreKey                                    | 6.2 and higher                                               |                      |
| BaseRegSaveKeyEx                                     | 6.2 and higher                                               |                      |
| BaseRegSetKeySecurity                                | 6.2 and higher                                               |                      |
| BaseRegSetValue                                      | 6.2 and higher                                               |                      |
| BaseRegUnLoadKey                                     | 6.2 and higher                                               |                      |
| BuildAccessRequestA                                  | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| BuildAccessRequestW                                  | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| BuildExplicitAccessWithNameA                         | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildExplicitAccessWithNameW                         | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildImpersonateExplicitAccessWithNameA              | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildImpersonateExplicitAccessWithNameW              | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildImpersonateTrusteeA                             | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildImpersonateTrusteeW                             | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildSecurityDescriptorA                             | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildSecurityDescriptorW                             | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildTrusteeWithNameA                                | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildTrusteeWithNameW                                | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildTrusteeWithObjectsAndNameA                      | 5.0 and higher                                               | documented           |
| BuildTrusteeWithObjectsAndNameW                      | 5.0 and higher                                               | documented           |
| BuildTrusteeWithObjectsAndSidA                       | 5.0 and higher                                               | documented           |
| BuildTrusteeWithObjectsAndSidW                       | 5.0 and higher                                               | documented           |
| BuildTrusteeWithSidA                                 | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| BuildTrusteeWithSidW                                 | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| CancelOverlappedAccess                               | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| ChangeServiceConfig2A                                | 5.0 and higher                                               | documented           |
| ChangeServiceConfig2W                                | 5.0 and higher                                               | documented           |
| ChangeServiceConfigA                                 | 3.10 and higher                                              | documented           |
| ChangeServiceConfigW                                 | 3.10 and higher                                              | documented           |
| CheckAppInitBlockedServiceIdentity                   | 6.0 only                                                     |                      |
| CheckForHiberboot                                    | 6.2 and higher                                               |                      |
| CheckTokenMembership                                 | 5.0 and higher                                               | documented           |
| ClearEventLogA                                       | 3.10 and higher                                              | documented           |
| ClearEventLogW                                       | 3.10 and higher                                              | documented           |
| CloseCodeAuthzLevel                                  | 5.1 and higher                                               |                      |
| CloseEncryptedFileRaw                                | 5.0 and higher                                               | documented           |
| CloseEventLog                                        | 3.10 and higher                                              | documented           |
| CloseServiceHandle                                   | 3.10 and higher                                              | documented           |
| CloseThreadWaitChainSession                          | 6.0 and higher                                               | documented           |
| CloseTrace                                           | 5.0 and higher                                               | documented           |
| CommandLineFromMsiDescriptor                         | 5.0 and higher                                               |                      |
| ComputeAccessTokenFromCodeAuthzLevel                 | 5.1 and higher                                               |                      |
| ControlService                                       | 3.10 and higher                                              | documented           |
| ControlServiceExA                                    | 6.0 and higher                                               | documented           |
| ControlServiceExW                                    | 6.0 and higher                                               | documented           |
| ControlTraceA                                        | 5.0 and higher                                               | documented           |
| ControlTraceW                                        | 5.0 and higher                                               | documented           |
| ConvertAccessToSecurityDescriptorA                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| ConvertAccessToSecurityDescriptorW                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| ConvertSDToStringSDDomainW                           | 6.2 and higher                                               |                      |
| ConvertSDToStringSDRootDomainA                       | 5.0 and higher                                               |                      |
| ConvertSDToStringSDRootDomainW                       | 5.0 and higher                                               |                      |
| ConvertSecurityDescriptorToAccessA                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| ConvertSecurityDescriptorToAccessW                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| ConvertSecurityDescriptorToAccessNamedA              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| ConvertSecurityDescriptorToAccessNamedW              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| ConvertSecurityDescriptorToStringSecurityDescriptorA | 5.0 and higher                                               | documented           |
| ConvertSecurityDescriptorToStringSecurityDescriptorW | 5.0 and higher                                               | documented           |
| ConvertSidToStringSidA                               | 5.0 and higher                                               | documented           |
| ConvertSidToStringSidW                               | 5.0 and higher                                               | documented           |
| ConvertStringSDToSDDomainA                           | 5.1 and higher                                               | documented           |
| ConvertStringSDToSDDomainW                           | 5.1 and higher                                               | documented           |
| ConvertStringSDToSDRootDomainA                       | 5.0 and higher                                               |                      |
| ConvertStringSDToSDRootDomainW                       | 5.0 and higher                                               |                      |
| ConvertStringSecurityDescriptorToSecurityDescriptorA | 5.0 and higher                                               | documented           |
| ConvertStringSecurityDescriptorToSecurityDescriptorW | 5.0 and higher                                               | documented           |
| ConvertStringSidToSidA                               | 5.0 and higher                                               | documented           |
| ConvertStringSidToSidW                               | 5.0 and higher                                               | documented           |
| ConvertToAutoInheritPrivateObjectSecurity            | 5.0 and higher                                               | documented           |
| CopySid                                              | 3.10 and higher                                              | documented           |
| CreateCodeAuthzLevel                                 | 5.1 and higher                                               |                      |
| CreatePrivateObjectSecurity                          | 3.10 and higher                                              | documented           |
| CreatePrivateObjectSecurityEx                        | 5.0 and higher                                               | documented           |
| CreatePrivateObjectSecurityWithMultipleInheritance   | 5.1 and higher                                               | documented           |
| CreateProcessAsUserA                                 | 3.51 and higher                                              | documented           |
| CreateProcessAsUserSecure                            | some 5.0 and some 5.1 only;  5.0 from Windows 2000 SP4;  5.1 from     Windows XP SP2 and SP3 |                      |
| CreateProcessAsUserW                                 | 3.51 and higher                                              | documented           |
| CreateProcessWithLogonW                              | 5.0 and higher                                               | documented           |
| CreateProcessWithTokenW                              | 5.2 and higher                                               | documented           |
| CreateRestrictedToken                                | 5.0 and higher                                               | documented           |
| CreateServiceA                                       | 3.10 and higher                                              | documented           |
| CreateServiceW                                       | 3.10 and higher                                              | documented           |
| CreateTraceInstanceId                                | 5.0 and higher                                               | documented           |
| CreateWellKnownSid                                   | 5.0 from Windows 2000 SP2, and higher                        | documented           |
| CredBackupCredentials                                | 6.0 and higher                                               |                      |
| CredDeleteA                                          | 5.1 and higher                                               | documented           |
| CredDeleteW                                          | 5.1 and higher                                               | documented           |
| CredEncryptAndMarshalBinaryBlob                      | 6.0 and higher                                               |                      |
| CredEnumerateA                                       | 5.1 and higher                                               | documented           |
| CredEnumerateW                                       | 5.1 and higher                                               | documented           |
| CredFindBestCredentialA                              | 6.0 and higher                                               | documented           |
| CredFindBestCredentialW                              | 6.0 and higher                                               | documented           |
| CredFree                                             | 5.1 and higher                                               | documented           |
| CredGetSessionTypes                                  | 5.1 and higher                                               | documented           |
| CredGetTargetInfoA                                   | 5.1 and higher                                               | documented           |
| CredGetTargetInfoW                                   | 5.1 and higher                                               | documented           |
| CredIsMarshaledCredentialA                           | 5.1 and higher                                               | documented           |
| CredIsMarshaledCredentialW                           | 5.1 and higher                                               | documented           |
| CredIsProtectedA                                     | 6.0 and higher                                               | documented           |
| CredIsProtectedW                                     | 6.0 and higher                                               | documented           |
| CredMarshalCredentialA                               | 5.1 and higher                                               | documented           |
| CredMarshalCredentialW                               | 5.1 and higher                                               | documented           |
| CredProfileLoaded                                    | 5.1 and higher                                               |                      |
| CredProfileLoadedEx                                  | 6.2 and higher                                               |                      |
| CredProfileUnloaded                                  | 6.0 and higher                                               |                      |
| CredProtectA                                         | 6.0 and higher                                               | documented           |
| CredProtectW                                         | 6.0 and higher                                               | documented           |
| CredReadA                                            | 5.1 and higher                                               | documented           |
| CredReadByTokenHandle                                | 6.0 and higher                                               |                      |
| CredReadDomainCredentialsA                           | 5.1 and higher                                               | documented           |
| CredReadDomainCredentialsW                           | 5.1 and higher                                               | documented           |
| CredReadW                                            | 5.1 and higher                                               | documented           |
| CredRenameA                                          | 5.1 and higher                                               | documented           |
| CredRenameW                                          | 5.1 and higher                                               | documented           |
| CredRestoreCredentials                               | 6.0 and higher                                               |                      |
| CredUnmarshalCredentialA                             | 5.1 and higher                                               | documented           |
| CredUnmarshalCredentialW                             | 5.1 and higher                                               | documented           |
| CredUnprotectA                                       | 6.0 and higher                                               | documented           |
| CredUnprotectW                                       | 6.0 and higher                                               | documented           |
| CredWriteA                                           | 5.1 and higher                                               | documented           |
| CredWriteDomainCredentialsA                          | 5.1 and higher                                               | documented           |
| CredWriteDomainCredentialsW                          | 5.1 and higher                                               | documented           |
| CredWriteW                                           | 5.1 and higher                                               | documented           |
| CredpConvertCredential                               | 5.1 and higher                                               |                      |
| CredpConvertOneCredentialSize                        | 6.0 and higher                                               |                      |
| CredpConvertTargetInfo                               | 5.1 and higher                                               |                      |
| CredpDecodeCredential                                | 5.1 and higher                                               |                      |
| CredpEncodeCredential                                | 5.1 and higher                                               |                      |
| CredpEncodeSecret                                    | 6.0 and higher                                               |                      |
| CryptAcquireContextA                                 | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptAcquireContextW                                 | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| CryptContextAddRef                                   | 4.80 and higher                                              | documented           |
| CryptCreateHash                                      | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptDecrypt                                         | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptDeriveKey                                       | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptDestroyHash                                     | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptDestroyKey                                      | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptDuplicateHash                                   | 4.80 and higher                                              | documented           |
| CryptDuplicateKey                                    | 4.80 and higher                                              | documented           |
| CryptEncrypt                                         | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptEnumProviderTypesA                              | 4.80 and higher                                              | documented           |
| CryptEnumProviderTypesW                              | 4.80 and higher                                              | documented           |
| CryptEnumProvidersA                                  | 4.80 and higher                                              | documented           |
| CryptEnumProvidersW                                  | 4.80 and higher                                              | documented           |
| CryptExportKey                                       | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptGenKey                                          | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptGenRandom                                       | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptGetDefaultProviderA                             | 4.80 and higher                                              | documented           |
| CryptGetDefaultProviderW                             | 4.80 and higher                                              | documented           |
| CryptGetHashParam                                    | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptGetKeyParam                                     | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptGetLocalKeyLimits                               | 4.90 only                                                    | documented           |
| CryptGetProvParam                                    | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptGetUserKey                                      | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptHashData                                        | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptHashSessionKey                                  | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptImportKey                                       | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptReleaseContext                                  | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptSetHashParam                                    | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptSetKeyParam                                     | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptSetProvParam                                    | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptSetProviderA                                    | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptSetProviderExA                                  | 4.80 and higher                                              | documented           |
| CryptSetProviderExW                                  | 4.80 and higher                                              | documented           |
| CryptSetProviderW                                    | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| CryptSignHashA                                       | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptSignHashW                                       | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| CryptVerifySignatureA                                | 4.0 from Windows NT 4.0, and higher                          | documented           |
| CryptVerifySignatureW                                | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| DecryptFileA                                         | 5.0 and higher                                               | documented           |
| DecryptFileW                                         | 5.0 and higher                                               | documented           |
| DeleteAce                                            | 3.10 and higher                                              | documented           |
| DeleteService                                        | 3.10 and higher                                              | documented           |
| DenyAccessRightsA                                    | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| DenyAccessRightsW                                    | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| DeregisterEventSource                                | 3.10 and higher                                              | documented           |
| DestroyPrivateObjectSecurity                         | 3.10 and higher                                              | documented           |
| DuplicateEncryptionInfoFile                          | 5.0 and higher                                               | documented           |
| DuplicateToken                                       | 3.10 and higher                                              | documented           |
| DuplicateTokenEx                                     | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| ElfBackupEventLogFileA                               | 3.10 and higher (NT only)                                    |                      |
| ElfBackupEventLogFileW                               | 3.10 and higher (NT only)                                    |                      |
| ElfChangeNotify                                      | 3.10 and higher (NT only)                                    |                      |
| ElfClearEventLogFileA                                | 3.10 and higher (NT only)                                    |                      |
| ElfClearEventLogFileW                                | 3.10 and higher (NT only)                                    |                      |
| ElfCloseEventLog                                     | 3.10 and higher (NT only)                                    |                      |
| ElfDeregisterEventSource                             | 3.10 and higher (NT only)                                    |                      |
| ElfFlushEventLog                                     | some 5.0, some 5.1, and higher;      5.0 from Windows 2000 SP4;      5.1 from Windows XP SP2 and SP3 |                      |
| ElfNumberOfRecords                                   | 3.10 and higher (NT only)                                    |                      |
| ElfOldestRecord                                      | 3.10 and higher (NT only)                                    |                      |
| ElfOpenBackupEventLogA                               | 3.10 and higher (NT only)                                    |                      |
| ElfOpenBackupEventLogW                               | 3.10 and higher (NT only)                                    |                      |
| ElfOpenEventLogA                                     | 3.10 and higher (NT only)                                    |                      |
| ElfOpenEventLogW                                     | 3.10 and higher (NT only)                                    |                      |
| ElfReadEventLogA                                     | 3.10 and higher (NT only)                                    |                      |
| ElfReadEventLogW                                     | 3.10 and higher (NT only)                                    |                      |
| ElfRegisterEventSourceA                              | 3.10 and higher (NT only)                                    |                      |
| ElfRegisterEventSourceW                              | 3.10 and higher (NT only)                                    |                      |
| ElfReportEventA                                      | 3.10 and higher (NT only)                                    |                      |
| ElfReportEventAndSourceW                             | 5.2 from Windows Server 2003 SP1, and higher                 |                      |
| ElfReportEventW                                      | 3.10 and higher (NT only)                                    |                      |
| EnableTrace                                          | 5.0 and higher                                               | documented           |
| EnableTraceEx                                        | 6.0 and higher                                               | documented           |
| EnableTraceEx2                                       | 6.1 and higher                                               | documented           |
| EncryptedFileKeyInfo                                 | 5.1 and higher                                               |                      |
| EncryptFileA                                         | 5.0 and higher                                               | documented           |
| EncryptFileW                                         | 5.0 and higher                                               | documented           |
| EncryptionDisable                                    | 5.0 and higher                                               | documented           |
| EnumDependentServicesA                               | 3.10 and higher                                              | documented           |
| EnumDependentServicesW                               | 3.10 and higher                                              | documented           |
| EnumDynamicTimeZoneInformation                       | 6.2 and higher                                               |                      |
| EnumServiceGroupW                                    | 4.0 and higher (NT only)                                     |                      |
| EnumServicesStatusA                                  | 3.10 and higher                                              | documented           |
| EnumServicesStatusExA                                | 4.0 from Windows NT 4.0 SP4, and higher (NT only)            | documented           |
| EnumServicesStatusExW                                | 4.0 from Windows NT 4.0 SP4, and higher (NT only)            | documented           |
| EnumServicesStatusW                                  | 3.10 and higher                                              | documented           |
| EnumerateTraceGuids                                  | 5.1 and higher                                               | documented           |
| EnumerateTraceGuidsEx                                | 6.0 and higher                                               | documented           |
| EqualDomainSid                                       | 5.0 from Windows 2000 SP2, and higher                        | documented           |
| EqualPrefixSid                                       | 3.10 and higher                                              | documented           |
| EqualSid                                             | 3.10 and higher                                              | documented           |
| EtwLogSysConfigExtension                             | 6.2 and higher                                               |                      |
| EventAccessControl                                   | 6.0 and higher                                               | documented           |
| EventAccessQuery                                     | 6.0 and higher                                               | documented           |
| EventAccessRemove                                    | 6.0 and higher                                               | documented           |
| EventActivityIdControl                               | 6.0 and higher                                               | documented           |
| EventEnabled                                         | 6.0 and higher                                               | documented           |
| EventProviderEnabled                                 | 6.0 and higher                                               | documented           |
| EventRegister                                        | 6.0 and higher                                               | documented           |
| EventSetInformation                                  | 6.2 and higher                                               |                      |
| EventUnregister                                      | 6.0 and higher                                               | documented           |
| EventWrite                                           | 6.0 and higher                                               | documented           |
| EventWriteEndScenario                                | 6.0 and higher                                               |                      |
| EventWriteEx                                         | 6.1 and higher                                               | documented           |
| EventWriteStartScenario                              | 6.0 and higher                                               |                      |
| EventWriteString                                     | 6.0 and higher                                               | documented           |
| EventWriteTransfer                                   | 6.0 and higher                                               | documented           |
| FileEncryptionStatusA                                | 5.0 and higher                                               | documented           |
| FileEncryptionStatusW                                | 5.0 and higher                                               | documented           |
| FindFirstFreeAce                                     | 3.10 and higher                                              | documented           |
| FlushEfsCache                                        | 6.0 and higher                                               |                      |
| FlushTraceA                                          | 5.1 and higher                                               | documented           |
| FlushTraceW                                          | 5.1 and higher                                               | documented           |
| FreeEncryptedFileKeyInfo                             | 5.1 and higher                                               |                      |
| FreeEncryptedFileMetadata                            | 6.0 and higher                                               |                      |
| FreeEncryptionCertificateHashList                    | 5.0 and higher                                               | documented           |
| FreeInheritedFromArray                               | 5.1 and higher                                               | documented           |
| FreeSid                                              | 3.10 and higher                                              | documented           |
| GetAccessPermissionsForObjectA                       | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| GetAccessPermissionsForObjectW                       | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| GetAce                                               | 3.10 and higher                                              | documented           |
| GetAclInformation                                    | 3.10 and higher                                              | documented           |
| GetAuditedPermissionsFromAclA                        | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetAuditedPermissionsFromAclW                        | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetAuditedPermissionsFromSDA                         | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetAuditedPermissionsFromSDW                         | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetCurrentHwProfileA                                 | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetCurrentHwProfileW                                 | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetDynamicTimeZoneInformationEffectiveYears          | 6.2 and higher                                               |                      |
| GetEffectiveAccessRightsA                            | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetEffectiveAccessRightsW                            | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetEffectiveRightsFromAclA                           | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetEffectiveRightsFromAclW                           | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetEffectiveRightsFromSDA                            | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetEffectiveRightsFromSDW                            | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetEncryptedFileMetadata                             | 6.0 and higher                                               |                      |
| GetEventLogInformation                               | 5.0 and higher                                               | documented           |
| GetExplicitAccessRightsA                             | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetExplicitAccessRightsW                             | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GetExplicitEntriesFromAclA                           | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetExplicitEntriesFromAclW                           | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetFileSecurityA                                     | 3.10 and higher                                              | documented           |
| GetFileSecurityW                                     | 3.10 and higher                                              | documented           |
| GetInformationCodeAuthzLevelW                        | 5.1 and higher                                               |                      |
| GetInformationCodeAuthzPolicyW                       | 5.1 and higher                                               |                      |
| GetInheritanceSourceA                                | 5.1 and higher                                               | documented           |
| GetInheritanceSourceW                                | 5.1 and higher                                               | documented           |
| GetKernelObjectSecurity                              | 3.10 and higher                                              | documented           |
| GetLengthSid                                         | 3.10 and higher                                              | documented           |
| GetLocalManagedApplicationData                       | 5.1 and higher                                               |                      |
| GetLocalManagedApplications                          | 5.0 and higher                                               | documented           |
| GetManagedApplicationCategories                      | 5.1 and higher                                               | documented           |
| GetManagedApplications                               | 5.0 and higher                                               | documented           |
| GetMangledSiteSid                                    | 5.0 only                                                     |                      |
| GetMultipleTrusteeA                                  | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetMultipleTrusteeOperationA                         | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetMultipleTrusteeOperationW                         | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetMultipleTrusteeW                                  | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetNamedSecurityInfoA                                | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetNamedSecurityInfoExA                              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| GetNamedSecurityInfoExW                              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| GetNamedSecurityInfoW                                | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetNumberOfEventLogRecords                           | 3.10 and higher                                              | documented           |
| GetOldestEventLogRecord                              | 3.10 and higher                                              | documented           |
| GetOverlappedAccessResults                           | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| GetPrivateObjectSecurity                             | 3.10 and higher                                              | documented           |
| GetSecurityDescriptorControl                         | 3.10 and higher                                              | documented           |
| GetSecurityDescriptorDacl                            | 3.10 and higher                                              | documented           |
| GetSecurityDescriptorGroup                           | 3.10 and higher                                              | documented           |
| GetSecurityDescriptorLength                          | 3.10 and higher                                              | documented           |
| GetSecurityDescriptorOwner                           | 3.10 and higher                                              | documented           |
| GetSecurityDescriptorRMControl                       | 5.0 and higher                                               | documented           |
| GetSecurityDescriptorSacl                            | 3.10 and higher                                              | documented           |
| GetSecurityInfo                                      | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetSecurityInfoExA                                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| GetSecurityInfoExW                                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| GetServiceDisplayNameA                               | 3.10 and higher                                              | documented           |
| GetServiceDisplayNameW                               | 3.10 and higher                                              | documented           |
| GetServiceKeyNameA                                   | 3.10 and higher                                              | documented           |
| GetServiceKeyNameW                                   | 3.10 and higher                                              | documented           |
| GetSidIdentifierAuthority                            | 3.10 and higher                                              | documented           |
| GetSidLengthRequired                                 | 3.10 and higher                                              | documented           |
| GetSidSubAuthority                                   | 3.10 and higher                                              | documented           |
| GetSidSubAuthorityCount                              | 3.10 and higher                                              | documented           |
| GetSiteDirectoryA                                    | 5.0 only                                                     |                      |
| GetSiteDirectoryW                                    | 5.0 only                                                     |                      |
| GetSiteNameFromSid                                   | 5.0 only                                                     |                      |
| GetSiteSidFromToken                                  | 5.0 only                                                     |                      |
| GetSiteSidFromUrl                                    | 5.0 only                                                     |                      |
| GetStringConditionFromBinary                         | 6.2 and higher                                               |                      |
| GetThreadWaitChain                                   | 6.0 and higher                                               | documented           |
| GetTokenInformation                                  | 3.10 and higher                                              | documented           |
| GetTraceEnableFlags                                  | 5.0 and higher                                               | documented           |
| GetTraceEnableLevel                                  | 5.0 and higher                                               | documented           |
| GetTraceLoggerHandle                                 | 5.0 and higher                                               | documented           |
| GetTrusteeFormA                                      | 5.0 and higher                                               | documented           |
| GetTrusteeFormW                                      | 5.0 and higher                                               | documented           |
| GetTrusteeNameA                                      | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetTrusteeNameW                                      | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetTrusteeTypeA                                      | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetTrusteeTypeW                                      | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| GetUserNameA                                         | 3.10 and higher                                              | documented           |
| GetUserNameW                                         | 3.10 and higher                                              | documented           |
| GetWindowsAccountDomainSid                           | 5.0 from Windows 2000 SP2, and higher                        | documented           |
| GrantAccessRightsA                                   | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| GrantAccessRightsW                                   | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| I_QueryTagInformation                                | 5.2 from Windows Server 2003 SP1, and higher                 |                      |
| I_ScGetCurrentGroupStateW                            | 4.0 and higher (NT only)                                     |                      |
| I_ScIsSecurityProcess                                | 5.0 and higher                                               |                      |
| I_ScPnPGetServiceName                                | 5.0 and higher                                               |                      |
| I_ScQueryServiceConfig                               | 6.0 and higher                                               |                      |
| I_ScRegisterPreshutdownRestart                       | 6.2 and higher                                               |                      |
| I_ScSendPnPMessage                                   | 6.0 and higher                                               |                      |
| I_ScSendTSMessage                                    | 5.1 and higher                                               |                      |
| I_ScSetServiceBitsA                                  | 3.10 and higher (NT only)                                    |                      |
| I_ScSetServiceBitsW                                  | 3.10 and higher (NT only)                                    |                      |
| I_ScValidatePnPService                               | 6.0 and higher                                               |                      |
| IdentifyCodeAuthzLevelW                              | 5.1 and higher                                               |                      |
| ImpersonateAnonymousToken                            | 5.0 and higher                                               | documented           |
| ImpersonateLoggedOnUser                              | 3.51 and higher                                              | documented           |
| ImpersonateNamedPipeClient                           | 3.10 and higher                                              | documented           |
| ImpersonateSelf                                      | 3.10 and higher                                              | documented           |
| InitializeAcl                                        | 3.10 and higher                                              | documented           |
| InitializeSecurityDescriptor                         | 3.10 and higher                                              | documented           |
| InitializeSid                                        | 3.10 and higher                                              | documented           |
| InitiateShutdownA                                    | 6.0 and higher                                               | documented           |
| InitiateShutdownW                                    | 6.0 and higher                                               | documented           |
| InitiateSystemShutdownA                              | 3.10 and higher                                              | documented           |
| InitiateSystemShutdownExA                            | 5.0 and higher                                               | documented           |
| InitiateSystemShutdownExW                            | 5.0 and higher                                               | documented           |
| InitiateSystemShutdownW                              | 3.10 and higher                                              | documented           |
| InstallApplication                                   | 5.0 and higher                                               | documented           |
| IsAccessPermittedA                                   | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| IsAccessPermittedW                                   | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| IsInSandbox                                          | 5.0 only                                                     |                      |
| IsProcessRestricted                                  | 5.0 only                                                     |                      |
| IsTextUnicode                                        | 3.51 and higher                                              | documented           |
| IsTokenRestricted                                    | 5.0 and higher                                               | documented           |
| IsTokenUntrusted                                     | 5.1 and higher                                               |                      |
| IsValidAcl                                           | 3.10 and higher                                              | documented           |
| IsValidRelativeSecurityDescriptor                    | 6.0 and higher                                               |                      |
| IsValidSecurityDescriptor                            | 3.10 and higher                                              | documented           |
| IsValidSid                                           | 3.10 and higher                                              | documented           |
| IsWellKnownSid                                       | 5.0 from Windows 2000 SP2, and higher                        | documented           |
| LockServiceDatabase                                  | 3.10 and higher                                              | documented           |
| LogonUserA                                           | 3.51 and higher                                              | documented           |
| LogonUserExA                                         | 5.1 and higher                                               | documented           |
| LogonUserExExW                                       | 6.0 and higher                                               | documented           |
| LogonUserExW                                         | 5.1 and higher                                               | documented           |
| LogonUserW                                           | 3.51 and higher                                              | documented           |
| LookupAccountNameA                                   | 3.10 and higher                                              | documented           |
| LookupAccountNameW                                   | 3.10 and higher                                              | documented           |
| LookupAccountSidA                                    | 3.10 and higher                                              | documented           |
| LookupAccountSidW                                    | 3.10 and higher                                              | documented           |
| LookupPrivilegeDisplayNameA                          | 3.10 and higher                                              | documented           |
| LookupPrivilegeDisplayNameW                          | 3.10 and higher                                              | documented           |
| LookupPrivilegeNameA                                 | 3.10 and higher                                              | documented           |
| LookupPrivilegeNameW                                 | 3.10 and higher                                              | documented           |
| LookupPrivilegeValueA                                | 3.10 and higher                                              | documented           |
| LookupPrivilegeValueW                                | 3.10 and higher                                              | documented           |
| LookupSecurityDescriptorPartsA                       | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| LookupSecurityDescriptorPartsW                       | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| LsaAddAccountRights                                  | 3.51 and higher (NT only)                                    | documented           |
| LsaAddPrivilegesToAccount                            | 3.10 and higher (NT only)                                    |                      |
| LsaClearAuditLog                                     | 3.10 and higher (NT only)                                    |                      |
| LsaClose                                             | 3.10 and higher (NT only)                                    | documented           |
| LsaCreateAccount                                     | 3.10 and higher (NT only)                                    |                      |
| LsaCreateSecret                                      | 3.10 and higher (NT only)                                    |                      |
| LsaCreateTrustedDomain                               | 3.10 and higher (NT only)                                    | documented           |
| LsaCreateTrustedDomainEx                             | 5.0 and higher                                               | documented           |
| LsaDelete                                            | 3.10 and higher (NT only)                                    |                      |
| LsaDeleteTrustedDomain                               | 3.51 and higher (NT only)                                    | documented           |
| LsaEnumerateAccountRights                            | 3.51 and higher (NT only)                                    | documented           |
| LsaEnumerateAccounts                                 | 3.10 and higher (NT only)                                    |                      |
| LsaEnumerateAccountsWithUserRight                    | 3.51 and higher (NT only)                                    | documented           |
| LsaEnumeratePrivileges                               | 3.10 and higher (NT only)                                    |                      |
| LsaEnumeratePrivilegesOfAccount                      | 3.10 and higher (NT only)                                    |                      |
| LsaEnumerateTrustedDomains                           | 3.10 and higher (NT only)                                    | documented           |
| LsaEnumerateTrustedDomainsEx                         | 5.0 and higher                                               | documented           |
| LsaFreeMemory                                        | 3.10 and higher (NT only)                                    | documented           |
| LsaGetAppliedCAPIDs                                  | 6.2 and higher                                               |                      |
| LsaGetQuotasForAccount                               | 3.10 and higher (NT only)                                    |                      |
| LsaGetRemoteUserName                                 | 4.0 from Windows NT 4.0 SP4, and higher (NT only)            |                      |
| LsaGetSystemAccessAccount                            | 3.10 and higher (NT only)                                    |                      |
| LsaGetUserName                                       | 4.0 and higher (NT only)                                     |                      |
| LsaICLookupNames                                     | 3.10 and higher (NT only)                                    |                      |
| LsaICLookupNamesWithCreds                            | 5.1 and higher                                               |                      |
| LsaICLookupSids                                      | 3.10 and higher (NT only)                                    |                      |
| LsaICLookupSidsWithCreds                             | 5.1 and higher                                               |                      |
| LsaLookupNames                                       | 3.10 and higher (NT only)                                    | documented           |
| LsaLookupNames2                                      | 5.1 and higher                                               | documented           |
| LsaLookupPrivilegeDisplayName                        | 3.10 and higher (NT only)                                    |                      |
| LsaLookupPrivilegeName                               | 3.10 and higher (NT only)                                    |                      |
| LsaLookupPrivilegeValue                              | 3.10 and higher (NT only)                                    |                      |
| LsaLookupSids                                        | 3.10 and higher (NT only)                                    | documented           |
| LsaLookupSids2                                       | 6.2 and higher                                               |                      |
| LsaManageSidNameMapping                              | 6.0 and higher                                               |                      |
| LsaNtStatusToWinError                                | 3.51 and higher (NT only)                                    | documented           |
| LsaOpenAccount                                       | 3.10 and higher (NT only)                                    |                      |
| LsaOpenPolicy                                        | 3.10 and higher (NT only)                                    | documented           |
| LsaOpenPolicySce                                     | 5.0 from Windows 2000 SP2, and higher                        |                      |
| LsaOpenSecret                                        | 3.10 and higher (NT only)                                    |                      |
| LsaOpenTrustedDomain                                 | 3.10 and higher (NT only)                                    |                      |
| LsaOpenTrustedDomainByName                           | 5.0 and higher                                               | documented           |
| LsaQueryCAPs                                         | 6.2 and higher                                               |                      |
| LsaQueryDomainInformationPolicy                      | 5.0 and higher                                               | documented           |
| LsaQueryForestTrustInformation                       | 5.1 and higher                                               | documented           |
| LsaQueryInfoTrustedDomain                            | 3.10 and higher (NT only)                                    |                      |
| LsaQueryInformationPolicy                            | 3.10 and higher (NT only)                                    | documented           |
| LsaQuerySecret                                       | 3.51 and higher (NT only)                                    |                      |
| LsaQuerySecurityObject                               | 3.51 and higher (NT only)                                    |                      |
| LsaQueryTrustedDomainInfo                            | 3.51 and higher (NT only)                                    | documented           |
| LsaQueryTrustedDomainInfoByName                      | 5.0 and higher                                               | documented           |
| LsaRemoveAccountRights                               | 3.51 and higher (NT only)                                    | documented           |
| LsaRemovePrivilegesFromAccount                       | 3.10 and higher (NT only)                                    |                      |
| LsaRetrievePrivateData                               | 3.51 and higher (NT only)                                    | documented           |
| LsaSetCAPs                                           | 6.2 and higher                                               |                      |
| LsaSetDomainInformationPolicy                        | 5.0 and higher                                               | documented           |
| LsaSetForestTrustInformation                         | 5.1 and higher                                               | documented           |
| LsaSetInformationPolicy                              | 3.10 and higher (NT only)                                    | documented           |
| LsaSetInformationTrustedDomain                       | 3.10 and higher (NT only)                                    |                      |
| LsaSetQuotasForAccount                               | 3.10 and higher NT only)                                     |                      |
| LsaSetSecret                                         | 3.10 and higher (NT only)                                    |                      |
| LsaSetSecurityObject                                 | 3.10 and higher (NT only)                                    |                      |
| LsaSetSystemAccessAccount                            | 3.10 and higher (NT only)                                    |                      |
| LsaSetTrustedDomainInfoByName                        | 5.0 and higher                                               | documented           |
| LsaSetTrustedDomainInformation                       | 3.51 and higher (NT only)                                    | documented           |
| LsaStorePrivateData                                  | 3.51 and higher (NT only)                                    | documented           |
| MD4Final                                             | 5.1 and higher                                               |                      |
| MD4Init                                              | 5.1 and higher                                               |                      |
| MD4Update                                            | 5.1 and higher                                               |                      |
| MD5Final                                             | 5.1 and higher                                               |                      |
| MD5Init                                              | 5.1 and higher                                               |                      |
| MD5Update                                            | 5.1 and higher                                               |                      |
| MIDL_user_free_Ext                                   | 6.2 and higher                                               |                      |
| MSChapSrvChangePassword                              | 5.1 and higher                                               | documented           |
| MSChapSrvChangePassword2                             | 5.1 and higher                                               | documented           |
| MakeAbsoluteSD                                       | 3.10 and higher                                              | documented           |
| MakeAbsoluteSD2                                      | 5.0 and higher                                               |                      |
| MakeSelfRelativeSD                                   | 3.10 and higher                                              | documented           |
| MapGenericMask                                       | 3.10 and higher                                              | documented           |
| NTAccessMaskToProvAccessRights                       | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| NotifyBootConfigStatus                               | 3.10 and higher                                              | documented           |
| NotifyChangeEventLog                                 | 3.51 and higher                                              | documented           |
| NotifyServiceStatusChange                            | 6.0 and higher                                               | documented           |
| NotifyServiceStatusChangeA                           | 6.0 and higher                                               | documented           |
| NotifyServiceStatusChangeW                           | 6.0 and higher                                               | documented           |
| NpGetUserName                                        | 10.0 and higher                                              |                      |
| ObjectCloseAuditAlarmA                               | 3.10 and higher                                              | documented           |
| ObjectCloseAuditAlarmW                               | 3.10 and higher                                              | documented           |
| ObjectDeleteAuditAlarmA                              | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| ObjectDeleteAuditAlarmW                              | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| ObjectOpenAuditAlarmA                                | 3.10 and higher                                              | documented           |
| ObjectOpenAuditAlarmW                                | 3.10 and higher                                              | documented           |
| ObjectPrivilegeAuditAlarmA                           | 3.10 and higher                                              | documented           |
| ObjectPrivilegeAuditAlarmW                           | 3.10 and higher                                              | documented           |
| OpenBackupEventLogA                                  | 3.10 and higher                                              | documented           |
| OpenBackupEventLogW                                  | 3.10 and higher                                              | documented           |
| OpenEncryptedFileRawA                                | 5.0 and higher                                               | documented           |
| OpenEncryptedFileRawW                                | 5.0 and higher                                               | documented           |
| OpenEventLogA                                        | 3.10 and higher                                              | documented           |
| OpenEventLogW                                        | 3.10 and higher                                              | documented           |
| OpenProcessToken                                     | 3.10 and higher                                              | documented           |
| OpenSCManagerA                                       | 3.10 and higher                                              | documented           |
| OpenSCManagerW                                       | 3.10 and higher                                              | documented           |
| OpenServiceA                                         | 3.10 and higher                                              | documented           |
| OpenServiceW                                         | 3.10 and higher                                              | documented           |
| OpenThreadToken                                      | 3.10 and higher                                              | documented           |
| OpenThreadWaitChainSession                           | 6.0 and higher                                               | documented           |
| OpenTraceA                                           | 5.0 and higher                                               | documented           |
| OpenTraceW                                           | 5.0 and higher                                               | documented           |
| OperationEnd                                         | 6.2 and higher                                               |                      |
| OperationStart                                       | 6.2 and higher                                               |                      |
| PerfAddCounters                                      | 6.0 and higher                                               |                      |
| PerfCloseQueryHandle                                 | 6.0 and higher                                               |                      |
| PerfCreateInstance                                   | 6.0 and higher                                               | documented           |
| PerfDecrementULongCounterValue                       | 6.0 and higher                                               | documented           |
| PerfDecrementULongLongCounterValue                   | 6.0 and higher                                               | documented           |
| PerfDeleteCounters                                   | 6.0 and higher                                               |                      |
| PerfDeleteInstance                                   | 6.0 and higher                                               | documented           |
| PerfEnumerateCounterSet                              | 6.0 and higher                                               |                      |
| PerfEnumerateCounterSetInstances                     | 6.0 and higher                                               |                      |
| PerfIncrementULongCounterValue                       | 6.0 and higher                                               | documented           |
| PerfIncrementULongLongCounterValue                   | 6.0 and higher                                               | documented           |
| PerfOpenQueryHandle                                  | 6.0 and higher                                               |                      |
| PerfQueryCounterData                                 | 6.0 and higher                                               |                      |
| PerfQueryCounterInfo                                 | 6.0 and higher                                               |                      |
| PerfQueryCounterSetRegistrationInfo                  | 6.0 and higher                                               |                      |
| PerfQueryInstance                                    | 6.0 and higher                                               | documented           |
| PerfRegCloseKey                                      | 6.2 and higher                                               |                      |
| PerfRegEnumKey                                       | 6.2 and higher                                               |                      |
| PerfRegEnumValue                                     | 6.2 and higher                                               |                      |
| PerfRegQueryInfoKey                                  | 6.2 and higher                                               |                      |
| PerfRegQueryValue                                    | 6.2 and higher                                               |                      |
| PerfRegSetValue                                      | 6.2 and higher                                               |                      |
| PerfSetCounterRefValue                               | 6.0 and higher                                               | documented           |
| PerfSetCounterSetInfo                                | 6.0 and higher                                               | documented           |
| PerfSetULongCounterValue                             | 6.0 and higher                                               | documented           |
| PerfSetULongLongCounterValue                         | 6.0 and higher                                               | documented           |
| PerfStartProvider                                    | 6.0 and higher                                               | documented           |
| PerfStartProviderEx                                  | 6.0 and higher                                               | documented           |
| PerfStopProvider                                     | 6.0 and higher                                               | documented           |
| PrivilegeCheck                                       | 3.10 and higher                                              | documented           |
| PrivilegedServiceAuditAlarmA                         | 3.10 and higher                                              | documented           |
| PrivilegedServiceAuditAlarmW                         | 3.10 and higher                                              | documented           |
| ProcessIdleTasks                                     | 5.1 and higher                                               |                      |
| ProcessIdleTasksW                                    | 6.0 and higher                                               |                      |
| ProcessTrace                                         | 5.0 and higher                                               | documented           |
| ProvAccessRightsToNTAccessMask                       | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| PsmActivateApplication                               | 6.2 only                                                     |                      |
| PsmAdjustActivationToken                             | 6.2 only                                                     |                      |
| PsmQueryBackgroundActivationType                     | 6.2 only                                                     |                      |
| PsmRegisterApplicationProcess                        | 6.2 only                                                     |                      |
| QueryAllTracesA                                      | 5.0 and higher                                               | documented           |
| QueryAllTracesW                                      | 5.0 and higher                                               | documented           |
| QueryRecoveryAgentsOnEncryptedFile                   | 5.0 and higher                                               | documented           |
| QuerySecurityAccessMask                              | 6.0 and higher                                               | documented           |
| QueryServiceConfig2A                                 | 5.0 and higher                                               | documented           |
| QueryServiceConfig2W                                 | 5.0 and higher                                               | documented           |
| QueryServiceConfigA                                  | 3.10 and higher                                              | documented           |
| QueryServiceConfigW                                  | 3.10 and higher                                              | documented           |
| QueryServiceDynamicInformation                       | 6.2 and higher                                               |                      |
| QueryServiceLockStatusA                              | 3.10 and higher                                              | documented           |
| QueryServiceLockStatusW                              | 3.10 and higher                                              | documented           |
| QueryServiceObjectSecurity                           | 3.10 and higher                                              | documented           |
| QueryServiceStatus                                   | 3.10 and higher                                              | documented           |
| QueryServiceStatusEx                                 | 4.0 and higher (NT only)                                     | documented           |
| QueryTraceA                                          | 5.1 and higher                                               | documented           |
| QueryTraceW                                          | 5.1 and higher                                               | documented           |
| QueryUsersOnEncryptedFile                            | 5.0 and higher                                               | documented           |
| QueryWindows31FilesMigration                         | 3.10 to 5.1 (NT only)                                        |                      |
| ReadEncryptedFileRaw                                 | 5.0 and higher                                               | documented           |
| ReadEventLogA                                        | 3.10 and higher                                              | documented           |
| ReadEventLogW                                        | 3.10 and higher                                              | documented           |
| RegCloseKey                                          | 3.10 and higher                                              | documented           |
| RegConnectRegistryA                                  | 3.10 and higher                                              | documented           |
| RegConnectRegistryW                                  | 3.10 and higher                                              | documented           |
| RegConnectRegistryExA                                | 5.2 from Windows Server 2003 SP1, and higher                 |                      |
| RegConnectRegistryExW                                | 5.2 from Windows Server 2003 SP1, and higher                 |                      |
| RegCopyTreeA                                         | 6.0 and higher                                               | documented           |
| RegCopyTreeW                                         | 6.0 and higher                                               | documented           |
| RegCreateKeyA                                        | 3.10 and higher                                              | documented           |
| RegCreateKeyExA                                      | 3.10 and higher                                              | documented           |
| RegCreateKeyExW                                      | 3.10 and higher                                              | documented           |
| RegCreateKeyTransactedA                              | 6.0 and higher                                               | documented           |
| RegCreateKeyTransactedW                              | 6.0 and higher                                               | documented           |
| RegCreateKeyW                                        | 3.10 and higher                                              | documented           |
| RegDeleteKeyA                                        | 3.10 and higher                                              | documented           |
| RegDeleteKeyExA                                      | 5.2 from Windows Server 2003 SP1, and higher                 | documented           |
| RegDeleteKeyExW                                      | 5.2 from Windows Server 2003 SP1, and higher                 | documented           |
| RegDeleteKeyTransactedA                              | 6.0 and higher                                               | documented           |
| RegDeleteKeyTransactedW                              | 6.0 and higher                                               | documented           |
| RegDeleteKeyValueA                                   | 6.0 and higher                                               | documented           |
| RegDeleteKeyValueW                                   | 6.0 and higher                                               | documented           |
| RegDeleteKeyW                                        | 3.10 and higher                                              | documented           |
| RegDeleteTreeA                                       | 6.0 and higher                                               | documented           |
| RegDeleteTreeW                                       | 6.0 and higher                                               | documented           |
| RegDeleteValueA                                      | 3.10 and higher                                              | documented           |
| RegDeleteValueW                                      | 3.10 and higher                                              | documented           |
| RegDisablePredefinedCache                            | 5.0 and higher                                               | documented           |
| RegDisablePredefinedCacheEx                          | 5.1 from Windows XP SP3, and 6.0 and higher                  | documented           |
| RegDisableReflectionKey                              | 5.2 from Windows Server 2003 SP1, and higher                 | documented           |
| RegEnableReflectionKey                               | 5.2 from Windows Server 2003 SP1, and higher                 | documented           |
| RegEnumKeyA                                          | 3.10 and higher                                              | documented           |
| RegEnumKeyExA                                        | 3.10 and higher                                              | documented           |
| RegEnumKeyExW                                        | 3.10 and higher                                              | documented           |
| RegEnumKeyW                                          | 3.10 and higher                                              | documented           |
| RegEnumValueA                                        | 3.10 and higher                                              | documented           |
| RegEnumValueW                                        | 3.10 and higher                                              | documented           |
| RegFlushKey                                          | 3.10 and higher                                              | documented           |
| RegGetKeySecurity                                    | 3.10 and higher                                              | documented           |
| RegGetValueA                                         | 5.2 from Windows Server 2003 SP1, and higher                 | documented           |
| RegGetValueW                                         | 5.2 from Windows Server 2003 SP1, and higher                 | documented           |
| RegLoadAppKeyA                                       | 6.0 and higher                                               | documented           |
| RegLoadAppKeyW                                       | 6.0 and higher                                               | documented           |
| RegLoadKeyA                                          | 3.10 and higher                                              | documented           |
| RegLoadKeyW                                          | 3.10 and higher                                              | documented           |
| RegLoadMUIStringA                                    | 6.0 and higher                                               | documented           |
| RegLoadMUIStringW                                    | 6.0 and higher                                               | documented           |
| RegNotifyChangeKeyValue                              | 3.10 and higher                                              | documented           |
| RegOpenCurrentUser                                   | 5.0 and higher                                               | documented           |
| RegOpenKeyA                                          | 3.10 and higher                                              | documented           |
| RegOpenKeyExA                                        | 3.10 and higher                                              | documented           |
| RegOpenKeyExW                                        | 3.10 and higher                                              | documented           |
| RegOpenKeyTransactedA                                | 6.0 and higher                                               | documented           |
| RegOpenKeyTransactedW                                | 6.0 and higher                                               | documented           |
| RegOpenKeyW                                          | 3.10 and higher                                              | documented           |
| RegOpenUserClassesRoot                               | 5.0 and higher                                               | documented           |
| RegOverridePredefKey                                 | 5.0 and higher                                               | documented           |
| RegQueryInfoKeyA                                     | 3.10 and higher                                              | documented           |
| RegQueryInfoKeyW                                     | 3.10 and higher                                              | documented           |
| RegQueryMultipleValuesA                              | 3.51 and higher                                              | documented           |
| RegQueryMultipleValuesW                              | 3.51 and higher                                              | documented           |
| RegQueryReflectionKey                                | 5.2 from Windows Server 2003 SP1, and higher                 | documented           |
| RegQueryValueA                                       | 3.10 and higher                                              | documented           |
| RegQueryValueExA                                     | 3.10 and higher                                              | documented           |
| RegQueryValueExW                                     | 3.10 and higher                                              | documented           |
| RegQueryValueW                                       | 3.10 and higher                                              | documented           |
| RegRemapPreDefKey                                    | 4.0 to 4.90 (Windows only)                                   |                      |
| RegRenameKey                                         | 6.0 and higher                                               |                      |
| RegReplaceKeyA                                       | 3.10 and higher                                              | documented           |
| RegReplaceKeyW                                       | 3.10 and higher                                              | documented           |
| RegRestoreKeyA                                       | 3.10 and higher                                              | documented           |
| RegRestoreKeyW                                       | 3.10 and higher                                              | documented           |
| RegSaveKeyA                                          | 3.10 and higher                                              | documented           |
| RegSaveKeyExA                                        | 5.1 and higher                                               | documented           |
| RegSaveKeyExW                                        | 5.1 and higher                                               | documented           |
| RegSaveKeyW                                          | 3.10 and higher                                              | documented           |
| RegSetKeySecurity                                    | 3.10 and higher                                              | documented           |
| RegSetKeyValueA                                      | 6.0 and higher                                               | documented           |
| RegSetKeyValueW                                      | 6.0 and higher                                               | documented           |
| RegSetValueA                                         | 3.10 and higher                                              | documented           |
| RegSetValueExA                                       | 3.10 and higher                                              | documented           |
| RegSetValueExW                                       | 3.10 and higher                                              | documented           |
| RegSetValueW                                         | 3.10 and higher                                              | documented           |
| RegUnLoadKeyA                                        | 3.10 and higher                                              | documented           |
| RegUnLoadKeyW                                        | 3.10 and higher                                              | documented           |
| RegisterEventSourceA                                 | 3.10 and higher                                              | documented           |
| RegisterEventSourceW                                 | 3.10 and higher                                              | documented           |
| RegisterIdleTask                                     | 5.1 and higher                                               |                      |
| RegisterServiceCtrlHandlerA                          | 3.10 and higher                                              | documented           |
| RegisterServiceCtrlHandlerExA                        | 5.0 and higher                                               | documented           |
| RegisterServiceCtrlHandlerExW                        | 5.0 and higher                                               | documented           |
| RegisterServiceCtrlHandlerW                          | 3.10 and higher                                              | documented           |
| RegisterTraceGuidsA                                  | 5.0 and higher                                               | documented           |
| RegisterTraceGuidsW                                  | 5.0 and higher                                               | documented           |
| RegisterWaitChainCOMCallback                         | 6.0 and higher                                               | documented           |
| RemoteRegEnumKeyWrapper                              | 6.2 and higher                                               |                      |
| RemoteRegEnumValueWrapper                            | 6.2 and higher                                               |                      |
| RemoteRegQueryInfoKeyWrapper                         | 6.2 and higher                                               |                      |
| RemoteRegQueryValueWrapper                           | 6.2 and higher                                               |                      |
| RemoveTraceCallback                                  | 5.0 and higher                                               | documented           |
| RemoveUsersFromEncryptedFile                         | 5.0 and higher                                               | documented           |
| ReplaceAllAccessRightsA                              | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| ReplaceAllAccessRightsW                              | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| ReportEventA                                         | 3.10 and higher                                              | documented           |
| ReportEventW                                         | 3.10 and higher                                              | documented           |
| RevertToSelf                                         | 3.10 and higher                                              | documented           |
| RevokeExplicitAccessRightsA                          | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| RevokeExplicitAccessRightsW                          | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| SafeBaseRegGetKeySecurity                            | 6.2 and higher                                               |                      |
| SaferCloseLevel                                      | 5.1 and higher                                               | documented           |
| SaferComputeTokenFromLevel                           | 5.1 and higher                                               | documented           |
| SaferCreateLevel                                     | 5.1 and higher                                               | documented           |
| SaferGetLevelInformation                             | 5.1 and higher                                               | documented           |
| SaferGetPolicyInformation                            | 5.1 and higher                                               | documented           |
| SaferIdentifyLevel                                   | 5.1 and higher                                               | documented           |
| SaferRecordEventLogEntry                             | 5.1 and higher                                               | documented           |
| SaferSetLevelInformation                             | 5.1 and higher                                               |                      |
| SaferSetPolicyInformation                            | 5.1 and higher                                               |                      |
| SaferiChangeRegistryScope                            | 5.1 and higher                                               |                      |
| SaferiCompareTokenLevels                             | 5.1 and higher                                               |                      |
| SaferiIsDllAllowed                                   | 6.1 and higher                                               |                      |
| SaferiIsExecutableFileType                           | 5.1 and higher                                               | documented           |
| SaferiPopulateDefaultsInRegistry                     | 5.1 and higher                                               |                      |
| SaferiRecordEventLogEntry                            | 5.1 and higher                                               |                      |
| SaferiRegisterExtensionDll (1000)                    | 6.1 and higher                                               |                      |
| SaferiReplaceProcessThreadTokens                     | 5.1 to 6.0                                                   |                      |
| SaferiSearchMatchingHashRules                        | 5.1 and higher                                               |                      |
| SetAccessRightsA                                     | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| SetAccessRightsW                                     | 4.0 before Windows NT 4.0 SP4 (NT only)                      |                      |
| SetAclInformation                                    | 3.10 and higher                                              | documented           |
| SetEncryptedFileMetadata                             | 6.0 and higher                                               |                      |
| SetEntriesInAccessListA                              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetEntriesInAccessListW                              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetEntriesInAclA                                     | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| SetEntriesInAclW                                     | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| SetEntriesInAuditListA                               | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetEntriesInAuditListW                               | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetFileSecurityA                                     | 3.10 and higher                                              | documented           |
| SetFileSecurityW                                     | 3.10 and higher                                              | documented           |
| SetInformationCodeAuthzLevelW                        | 5.1 and higher                                               |                      |
| SetInformationCodeAuthzPolicyW                       | 5.1 and higher                                               |                      |
| SetKernelObjectSecurity                              | 3.10 and higher                                              | documented           |
| SetNamedSecurityInfoA                                | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| SetNamedSecurityInfoExA                              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetNamedSecurityInfoExW                              | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetNamedSecurityInfoW                                | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| SetPrivateObjectSecurity                             | 3.10 and higher                                              | documented           |
| SetPrivateObjectSecurityEx                           | 5.0 and higher                                               | documented           |
| SetSecurityAccessMask                                | 6.0 and higher                                               | documented           |
| SetSecurityDescriptorControl                         | 5.0 and higher                                               | documented           |
| SetSecurityDescriptorDacl                            | 3.10 and higher                                              | documented           |
| SetSecurityDescriptorGroup                           | 3.10 and higher                                              | documented           |
| SetSecurityDescriptorOwner                           | 3.10 and higher                                              | documented           |
| SetSecurityDescriptorRMControl                       | 5.0 and higher                                               | documented           |
| SetSecurityDescriptorSacl                            | 3.10 and higher                                              | documented           |
| SetSecurityInfo                                      | 4.0 and higher (NT);      4.80 and higher (Windows)          | documented           |
| SetSecurityInfoExA                                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetSecurityInfoExW                                   | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| SetServiceBits                                       | 3.51 and higher                                              | documented           |
| SetServiceObjectSecurity                             | 3.10 and higher                                              | documented           |
| SetServiceStatus                                     | 3.10 and higher                                              | documented           |
| SetThreadToken                                       | 3.10 and higher                                              | documented           |
| SetTokenInformation                                  | 3.10 and higher                                              | documented           |
| SetTraceCallback                                     | 5.0 and higher                                               | documented           |
| SetUserFileEncryptionKey                             | 5.0 and higher                                               | documented           |
| SetUserFileEncryptionKeyEx                           | 6.0 and higher                                               |                      |
| StartServiceA                                        | 3.10 and higher                                              | documented           |
| StartServiceCtrlDispatcherA                          | 3.10 and higher                                              | documented           |
| StartServiceCtrlDispatcherW                          | 3.10 and higher                                              | documented           |
| StartServiceW                                        | 3.10 and higher                                              | documented           |
| StartTraceA                                          | 5.0 and higher                                               | documented           |
| StartTraceW                                          | 5.0 and higher                                               | documented           |
| StopTraceA                                           | 5.1 and higher                                               | documented           |
| StopTraceW                                           | 5.1 and higher                                               | documented           |
| SynchronizeWindows31FilesAndWindowsNTRegistry        | 3.10 to 5.1 (NT only)                                        |                      |
| SystemFunction001                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction002                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction003                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction004                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction005                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction006                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction007                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction008                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction009                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction010                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction011                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction012                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction013                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction014                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction015                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction016                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction017                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction018                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction019                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction020                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction021                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction022                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction023                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction024                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction025                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction026                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction027                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction028                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction029                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction030                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction031                                    | 3.10 and higher (NT only)                                    |                      |
| SystemFunction032                                    | 3.51 and higher (NT only)                                    |                      |
| SystemFunction033                                    | 3.51 and higher (NT only)                                    |                      |
| SystemFunction034                                    | 5.0 and higher                                               |                      |
| SystemFunction035                                    | 5.0 and higher                                               |                      |
| SystemFunction036                                    | 5.1 and higher                                               | documented           |
| SystemFunction040                                    | 5.0 from Windows 2000 SP2, and higher                        | documented           |
| SystemFunction041                                    | 5.0 from Windows 2000 SP2, and higher                        | documented           |
| TraceEvent                                           | 5.0 and higher                                               | documented           |
| TraceEventInstance                                   | 5.0 and higher                                               | documented           |
| TraceMessage                                         | 5.1 and higher                                               | documented           |
| TraceMessageVa                                       | 5.1 and higher                                               | documented           |
| TraceQueryInformation                                | 6.2 and higher                                               |                      |
| TraceSetInformation                                  | 6.1 and higher                                               | documented           |
| TreeResetNamedSecurityInfoA                          | 5.1 and higher                                               | documented           |
| TreeResetNamedSecurityInfoW                          | 5.1 and higher                                               | documented           |
| TreeSetNamedSecurityInfoA                            | 6.0 and higher                                               | documented           |
| TreeSetNamedSecurityInfoW                            | 6.0 and higher                                               | documented           |
| TrusteeAccessToObjectA                               | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| TrusteeAccessToObjectW                               | 4.0 from Windows NT 4.0 SP4, and higher (NT);      4.80 and higher (Windows) |                      |
| UninstallApplication                                 | 5.0 and higher                                               | documented           |
| UnlockServiceDatabase                                | 3.10 and higher                                              | documented           |
| UnregisterIdleTask                                   | 5.1 and higher                                               |                      |
| UnregisterTraceGuids                                 | 5.0 and higher                                               | documented           |
| UpdateTraceA                                         | 5.1 and higher                                               | documented           |
| UpdateTraceW                                         | 5.1 and higher                                               | documented           |
| UsePinForEncryptedFilesA                             | 6.0 and higher                                               |                      |
| UsePinForEncryptedFilesW                             | 6.0 and higher                                               |                      |
| WaitServiceState                                     | 6.2 and higher                                               |                      |
| WdmWmiServiceMain                                    | 5.1 and 5.2 only                                             |                      |
| WmiCloseBlock                                        | 5.0 and higher                                               |                      |
| WmiCloseTraceWithCursor                              | 5.1 from Windows XP SP1 to 5.2                               |                      |
| WmiConvertTimestamp                                  | 5.1 from Windows XP SP1 to 5.2                               |                      |
| WmiDevInstToInstanceNameA                            | 5.0 and higher                                               |                      |
| WmiDevInstToInstanceNameW                            | 5.0 and higher                                               |                      |
| WmiEnumerateGuids                                    | 5.0 and higher                                               |                      |
| WmiExecuteMethodA                                    | 5.0 and higher                                               |                      |
| WmiExecuteMethodW                                    | 5.0 and higher                                               |                      |
| WmiFileHandleToInstanceNameA                         | 5.0 and higher                                               |                      |
| WmiFileHandleToInstanceNameW                         | 5.0 and higher                                               |                      |
| WmiFreeBuffer                                        | 5.0 and higher                                               |                      |
| WmiGetFirstTraceOffset                               | 5.1 and 5.2 only                                             |                      |
| WmiGetNextEvent                                      | 5.1 from Windows XP SP1 to 5.2                               |                      |
| WmiGetTraceHeader                                    | 5.1 and 5.2 only                                             |                      |
| WmiMofEnumerateResourcesA                            | 5.0 and higher                                               |                      |
| WmiMofEnumerateResourcesW                            | 5.0 and higher                                               |                      |
| WmiNotificationRegistrationA                         | 5.0 and higher                                               |                      |
| WmiNotificationRegistrationW                         | 5.0 and higher                                               |                      |
| WmiOpenBlock                                         | 5.0 and higher                                               |                      |
| WmiOpenTraceWithCursor                               | 5.1 from Windows XP SP1 to 5.2                               |                      |
| WmiParseTraceEvent                                   | 5.1 and 5.2 only                                             |                      |
| WmiQueryAllDataA                                     | 5.0 and higher                                               |                      |
| WmiQueryAllDataMultipleA                             | 5.1 and higher                                               |                      |
| WmiQueryAllDataMultipleW                             | 5.1 and higher                                               |                      |
| WmiQueryAllDataW                                     | 5.0 and higher                                               |                      |
| WmiQueryGuidInformation                              | 5.0 and higher                                               |                      |
| WmiQuerySingleInstanceA                              | 5.0 and higher                                               |                      |
| WmiQuerySingleInstanceMultipleA                      | 5.1 and higher                                               |                      |
| WmiQuerySingleInstanceMultipleW                      | 5.1 and higher                                               |                      |
| WmiQuerySingleInstanceW                              | 5.0 and higher                                               |                      |
| WmiReceiveNotificationsA                             | 5.1 and higher                                               |                      |
| WmiReceiveNotificationsW                             | 5.1 and higher                                               |                      |
| WmiSetSingleInstanceA                                | 5.0 and higher                                               |                      |
| WmiSetSingleInstanceW                                | 5.0 and higher                                               |                      |
| WmiSetSingleItemA                                    | 5.0 and higher                                               |                      |
| WmiSetSingleItemW                                    | 5.0 and higher                                               |                      |
| Wow64Win32ApiEntry                                   | 5.1 to 6.0                                                   |                      |
| WriteEncryptedFileRaw                                | 5.0 and higher                                               |                      |

## Names 

Function names are reproduced from the export directory of the ADVAPI32.DLL executable.  All exports from ADVAPI32 are by name, until version 6.1 (Windows 7) introduces  one that is exported only by ordinal. Its name is inferred from symbol files that  Microsoft publishes for customer support. Its ordinal is given in brackets after  the name. 

## Versions 

The [ADVAPI32 versions](https://www.geoffchappell.com/studies/windows/win32/advapi32/history/index.htm) shown for each function  are inferred from a study of public releases such as I have managed to find on old  MSDN discs or have since downloaded from free Microsoft websites. My holdings are  incomplete and I anyway have no time (or interest in) examining pre-release builds  or hotfixes. Of necessity then, the table makes what I hope are reasonable assumptions  about likely continuity, especially to suppose that a function will exist in future  versions or that a function exists in all (released) builds of a version if no counter-example  is yet known. If you want more accurate or comprehensive information, try getting  it from Microsoft. 

This study refers to applicable products and service packs in ascending order  of versions and build numbers. Be aware that this is not chronological order. A  quick list of the studied versions, in ascending order, is: 

- # ADVAPI32 Versions 

  Only in the NT versions of Windows is ADVAPI32.DLL fully functional. Client and  server editions were separated for versions 5.1 and 5.2 before being reunited  for version 6.0. 

  For the versions of Windows that run on MS-DOS, ADVAPI32 is significantly smaller  and much less capable, enough that it might more usefully be considered a different  executable. Still, this survey tries to keep them all together. Version 4.0 is common  to both Windows products, but the Windows that runs on DOS never gets past 4 as  its major version number. Beware, however, that ADVAPI32’s minor version numbers  in that series differ from those of NTDLL and KERNEL32. 

  | Version | Distribution    |                                        |
  | ------- | --------------- | -------------------------------------- |
  | Windows | NT              |                                        |
  | 3.10    |                 | Windows NT 3.10                        |
  | 3.51    |                 | Windows NT 3.51                        |
  | 4.0     | Windows 95      | Windows NT 4.0                         |
  | 4.70    | Windows 95 OSR2 |                                        |
  | 4.80    | Windows 98      |                                        |
  | 4.90    | Windows Me      |                                        |
  | 5.0     |                 | Windows 2000                           |
  | 5.1     |                 | Windows XP                             |
  | 5.2     |                 | Windows Server 2003                    |
  | 6.0     |                 | Windows Vista      Windows Server 2008 |
  | 6.1     |                 | Windows 7      Windows Server 2008 R2  |
  | 6.2     |                 | Windows 8                              |
  | 6.3     |                 | Windows 8.1                            |
  | 10.0    |                 | Windows 10                             |

  The version numbering gets arguably quirky for Windows 7, Windows 8 and Windows  8.1. These were each in their time promoted as a significant—even major—release,  yet they all have the same major version number which anyway isn’t in any of the  names. As if to acknowledge this as unsatisfactory, the major version number for  Windows 10 actually is 10. 

  ## Builds 

  The following builds have been inspected for these notes. Most are from MSDN  discs. Some, especially since Microsoft greatly reduced its shipment of operating  systems on MSDN discs, are from service packs downloaded (typically as self-extracting  executables) from a Microsoft website. 

  Builds are arranged in increasing order of the file version as recorded in the  executable’s resources. This version number is readily visible using Windows Explorer  either in a so-called infotip for the file or by accessing the Version tab in the  Properties dialog for the file. Programmers know this version number as coming from  the so-called root block of the version-information resource, specifically from  the dwFileVersionMS and dwFileVersionLS  members of a VS_FIXEDFILEINFO structure. 

  The date stamp shown for each version is more obscure. File dates are easily  modified after the executable is built and are anyway liable to be shown differently  when read from different time zones. However, there is in each executable’s header  a date stamp which is set when the executable is built and which is not commonly  changed afterwards. It is readily accessible to anyone with programming knowledge  and appropriate tools, e.g., Microsoft’s own DUMPBIN utility. 

  | File Version     | File Header Date Stamp                                     | File Size | Package                                    |
  | ---------------- | ---------------------------------------------------------- | --------- | ------------------------------------------ |
  | 3.10.505.1       | 2C44511E (14th July 1993)                                  | 257,156   | Windows NT 3.10                            |
  | 3.51.1016.1      | 2FB911B6 (17th May 1995)                                   | 177,920   | Windows NT 3.51                            |
  | 3.51.1057.6      | 322751E0 (31st August 1996)                                | 181,504   | Windows NT 3.51 SP5                        |
  | 4.0.0.950        | 2FF383BF (30th June 1995)                                  | 13,824    | Windows 95                                 |
  | 4.0.1371.1       | 31F91A37 (27th July 1996)                                  | 246,032   | Windows NT 4.0                             |
  | 4.0.1381.4       | 334EC81B (12th April 1997)                                 | 246,544   | Windows NT 4.0 SP3                         |
  | 4.0.1381.121     | 36115C05 (30th September 1998)                             | 247,056   | Windows NT 4.0 SP4                         |
  | 4.0.1381.203     | 371CCA7E (21st April 1999)                                 | 247,056   | Windows NT 4.0 SP5                         |
  | 4.0.1381.281     | 37584510 (5th June 1999)                                   | 247,056   | Windows NT 4.0 SP6                         |
  | 4.70.0.1155      | 320D0358 (11th August 1996)                                | 43,008    | Windows 95 OSR2                            |
  | 4.80.0.1675      | 35474F62 (30th April 1998)      3720A1CD (24th April 1999) | 65,536    | Windows 98      Windows 98 SE              |
  | 4.90.0.3000      | 39403BE1 (9th June 2000)                                   | 65,536    | Windows Me                                 |
  | 5.0.2191.1       | 3844D034 (1st December 1999)                               | 357,648   | Windows 2000                               |
  | 5.0.2195.1600    | 394193D2 (10th June 2000)                                  | 357,648   | Windows 2000 SP1                           |
  | 5.0.2195.4453    | 3C1FE610 (19th December 2001)                              | 364,816   | Windows 2000 SP2                           |
  | 5.0.2195.5385    | 3D3D020A (23rd July 2002)                                  | 367,376   | Windows 2000 SP3                           |
  | 5.0.2195.6710    | 3EF274DC (20th June 2003)                                  | 387,344   | Windows 2000 SP4                           |
  | 5.1.2600.0       | 3B7DFE0E (18th August 2001)                                | 549,888   | Windows XP                                 |
  | 5.1.2600.1106    | 3D6DFA28 (29th August 2002)                                | 558,080   | Windows XP SP1                             |
  | 5.1.2600.2180    | 411096A7 (4th August 2004)                                 | 616,960   | Windows XP SP2                             |
  | 5.1.2600.5512    | 4802A0B2 (14th April 2008)                                 | 617,472   | Windows XP SP3                             |
  | 5.2.3790.0       | 3E802495 (25th March 2003)                                 | 572,928   | Windows Server 2003                        |
  | 5.2.3790.1830    | 424377B4 (25th March 2005)                                 | 620,032   | Windows Server 2003 SP1                    |
  | 5.2.3790.3959    | 45D70A26 (17th February 2007)                              | 618,496   | Windows Server 2003 SP2                    |
  | 6.0.6000.16386   | 4549BCD2 (2nd November 2006)                               | 770,048   | Windows Vista                              |
  | 6.0.6001.18000   | 4791A64B (19th January 2008)                               | 798,720   | Windows Vista SP1      Windows Server 2008 |
  | 6.0.6002.18005   | 49E03717 (11th April 2009)                                 | 800,768   | Windows Vista SP2                          |
  | 6.1.7600.16385   | 4A5BD97E (14th July 2009)                                  | 640,000   | Windows 7                                  |
  | 6.1.7601.17514   | 4CE7B706 (20th November 2010)                              | 640,512   | Windows 7 SP1                              |
  | 6.2.9200.16384   | 5010A891 (25th July 2012)                                  | 702,464   | Windows 8                                  |
  | 6.3.9600.16384   | 52158D81 (22nd August 2013)                                | 489,088   | Windows 8.1                                |
  | 6.3.9600.17031   | 5308859E (22nd February 2014)                              | 490,136   | Windows 8.1 Update                         |
  | 10.0.10240.16384 | 559F3DB6 (9th July 2015)                                   | 497,896   | Windows 10                                 |

  The Windows 98 versions (original and SE) differ only from rebasing, including  to change the file header’s date stamp and checksum. 

  The executables for Windows Vista SP1 and Windows Server 2008 are exactly  identical. 

  ### 64-Bit Windows 

  Microsoft’s distribution of early 64-bit Windows on MSDN discs is even less reliable  than is my renewal of subscriptions. I seem never to have received a 64-bit edition  of Windows XP. Since a subscription in 2007 produced no x64 build of the original  Windows Vista, the copy inspected of that is from an OEM disc. The builds inspected  for service packs are from self-extracting executables that have been downloaded  from a free Microsoft website (which is, curiously, an order of magnitude faster  than downloading disc images from the paid MSDN website). 

  | File Version     | File Header Date Stamp        | File Size | Package                                                      |
  | ---------------- | ----------------------------- | --------- | ------------------------------------------------------------ |
  | 5.2.3790.1830    | 42438B4B (25th March 2005)    | 1,051,136 | Windows Server 2003 SP1                                      |
  | 5.2.3790.3959    | 45D6CBF1 (17th February 2007) | 1,051,648 | Windows Server 2003 SP2                                      |
  | 6.0.6000.16386   | 4549D267 (2nd November 2006)  | 1,031,680 | Windows Vista                                                |
  | 6.0.6001.18000   | 4791AC8C (19th January 2008)  | 1,062,400 | Windows Vista SP1      Windows Server 2008                   |
  | 6.0.6002.18005   | 49E040CB (11th April 2009)    | 1,065,472 | Windows Vista SP2                                            |
  | 6.1.7600.16385   | 4A5BDE6B (14th July 2009)     | 877,056   | Windows 7      Windows Server 2008 R2      Windows 7 SP1      Windows Server 2008 R2 SP1 |
  | 6.2.9200.16384   | 5010A732 (25th July 2012)     | 894,464   | Windows 8                                                    |
  | 6.3.9600.16384   | 5215F6B0 (22nd August 2013)   | 669,392   | Windows 8.1                                                  |
  | 6.3.9600.17031   | 530891B2 (22nd February 2014) | 669,896   | Windows 8.1 Update                                           |
  | 10.0.10240.16384 | 559F3B5B (9th July 2015)      | 667,344   | Windows 10                                                   |

  Again, where two packages are shown for the same build, the executables are  identical. 

  The self-extracting executable for 64-bit Windows 7 SP1 and Windows Server 2008  R2 SP1 does not contain a 64-bit ADVAPI32.DLL. The ADVAPI32.DLL that is installed  for 64-bit Windows 7 SP1 is exactly the same as for the original 64-bit Windows 7. 

  This page was created on 18th November 2008 and was last modified   on 30th May 2020. 

  Copyright © 2008-2020. Geoff Chappell. All rights reserved.  [Conditions apply](https://www.geoffchappell.com/about/terms.htm). 

## Documentation Status 

This study’s reference version of Microsoft’s documentation is the [ Microsoft Windows Software Development Kit (SDK) for Windows 7 and .NET Framework  3.51 Service Pack 1](http://download.microsoft.com/download/2/E/9/2E911956-F90F-4BFB-8231-E292A7B6F287/GRMSDK_EN_DVD.iso)![External link](https://www.geoffchappell.com/_images/external.gif), apparently released in August 2009. The build date shown  on the opening pages of this documentation is 22nd June 2009. 

Choosing one reference edition is not ideal for all purposes. Functions inevitably  will be added for versions released afterwards, and will typically not be listed  above as documented until a new reference edition is adopted. There is also a loss  of history. Of interest to many is that Microsoft sometimes does not document new  functions until years have passed: that a function is marked above as documented  does not mean it has always been documented, only that it is documented in the chosen  reference edition. Of interest perhaps only to historians is that even documented  functions are sometimes discontinued, meaning specifically that later versions do  not export them. Do not rely on me to have searched old editions of the SDK or MSDN  Library to find whether discontinued functions ever were documented. 

The great majority of functions that are exported from ADVAPI32 in currently  supported Windows versions are documented, even as being exported from ADVAPI32.  Unfortunately, although the SDK documentation does have a Windows API Reference  with a master list of Functions in Alphabetical Order, a moment’s checking shows  it to be unreliable as a master list. Individual pages for ADVAPI32 functions are  scattered all over Microsoft’s documentation, under all sorts of headings. That  a function is not marked above as “documented” does not mean for certain that Microsoft  does not document it, just that I haven’t yet found where. 

This page was created on 31st May 2010 and was last modified   on 30th May 2020. 

Copyright © 2010-2020. Geoff Chappell. All rights reserved.  [Conditions apply](https://www.geoffchappell.com/about/terms.htm). 





