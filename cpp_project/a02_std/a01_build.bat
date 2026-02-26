call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /O2 /DNDEBUG /MD a01_basic_stdstl.cpp
:: /O2: 核心参数。开启最大速度优化，通常也会减小体积。
:: /DNDEBUG: 定义“非调试”宏，去掉代码里的 assert 等调试逻辑。