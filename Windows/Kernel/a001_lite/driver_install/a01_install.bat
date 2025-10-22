copy ..\*.sys C:\Windows\system32\drivers

echo 虚拟机: 一定要开启处理器虚拟化 intel vt-x或者amd-v
echo bcdedit /set testsigning on
echo 请不要在真机上配置这个插件，蓝屏警告
pause