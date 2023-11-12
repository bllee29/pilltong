import datetime
import subprocess
import ctypes

# use absolute path for using in /etc/rc.local
dev = ctypes.CDLL("./home/pilltong/pilltong/device.so")

def modeSelect() -> int:
    return dev.userInput()

def camera_snapshot(UID: str, bright: int) -> str:
    dev.LEDON(bright);
    prefix = f"device_image/{UID}/FindPill"
    suffix = datetime.datetime.now().strftime("%Y%m%d_%H%M%S") + '.jpeg'
    filename = "_".join([prefix, suffix])
    subprocess.call("libcamera-jpeg -o {}".format(filename), shell=True)
    return filename

def endProc():
    subprocess.call("sudo shutdown now {}", shell=True)


def main():
    UID = '8084fca6-b5e0-4a46-b395-4874104142cb'
    print(camera_snapshot(UID))

if __name__ == "__main__":
    main()    