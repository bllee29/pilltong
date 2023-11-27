import subprocess
import ctypes

dev = ctypes.CDLL("/home/pilltong/pilltong/device.so")

def main():
    while(True):
        t = input()
        for i in range(1, 6):
            camera_snapshot(t, i * 100)


def camera_snapshot(prefix: str, bright: int):
    dev.LEDON(bright)
    subprocess.call("libcamera-jpeg -o {}".format(prefix), shell=True)
    print(f'{prefix} has captured')