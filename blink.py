import ctypes

a = ctypes.CDLL("./liba.so")
blink = a.blink
blink()