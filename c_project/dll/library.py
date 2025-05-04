from ctypes import *

dll = cdll.LoadLibrary("./library.dll")
print(dir(dll))
print(dll.hello())
