import subprocess
import ctypes
import json

def setting() -> str:
    with open ("config.json", 'r') as f:
        config = json.load(f)
    return config

# use absolute path for using in /etc/rc.local
dev = ctypes.CDLL("/home/pilltong/pilltong/device.so")
config = setting()

def modeSelect() -> int:
    return dev.userInput()

def camera_snapshot(UID: str, suffix: str, bright: int) -> str:
    dev.LEDON(bright);
    prefix = f"device_image/{UID}/"
    suffix = suffix + f"{bright}" + ".jpeg"
    filename = "".join([prefix, suffix])
    subprocess.call("libcamera-jpeg -o {}".format(filename), shell=True)
    return filename

def turn():
    dev.turn()

def endProc():
    subprocess.call("sudo shutdown now {}", shell=True)


def main():
    UID = '8084fca6-b5e0-4a46-b395-4874104142cb'
    print(camera_snapshot(UID))

if __name__ == "__main__":
    main()    