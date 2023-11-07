import ctypes

a = ctypes.CDLL("./blink.so")
blink = a.blink

servo = a.servo
servo()