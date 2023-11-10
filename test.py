import ctypes

a = ctypes.CDLL("./blink.so")

servo = a.servo

pwmlight = a.pwmlight

