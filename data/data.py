import subprocess
import ctypes
import datetime

dev = ctypes.CDLL("/home/pilltong/pilltong/device.so")

def main():
    while(True):
        t = input()
        suffix = datetime.datetime.now().strftime("_%Y%m%d_%H%M")
        for i in range(1, 6):
            camera_snapshot(t, suffix, i * 100)


def camera_snapshot(prefix: str, suffix: str, bright: int):
    dev.LEDON(bright)
    suffix = str(bright) + suffix + ".jpeg"
    filename = "".join([prefix, suffix])
    subprocess.call("libcamera-jpeg -o {}".format(filename), shell=True)
    print(f'{filename} has captured')

if __name__ == "__main__":
    main()
