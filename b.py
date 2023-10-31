import ctypes

a = ctypes.CDLL("./liba.so")
mul = a.mul
print(mul(13,43))