:: https://mp.weixin.qq.com/s/JnglDCTIiLWw7dq2WPNq2A
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cl driver.c "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\km\x64\ntoskrnl.lib" /I "C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\km" /link /subsystem:native /driver:wdm  -entry:DriverEntry

ren driver.exe driver.sys