import subprocess
import ctypes
import time

##########################################################################
# temporary alarm function
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(22, GPIO.OUT)
scale = [262, 294, 330, 349, 392, 440, 494, 523]

def alarm():
    try:
            p = GPIO.PWM(22, 100)
            p.start(100)
            p.ChangeDutyCycle(90)

            for i in range(8):
                    p.ChangeFrequency(scale[i])
                    time.sleep(0.1)
            p.stop()

    finally:
            GPIO.cleanup()
##########################################################################


# brightness corecction
correction = 200

# use absolute path for using in /etc/rc.local
dev = ctypes.CDLL("/home/pilltong/pilltong/device.so")

def ledInit() :
    dev.STATE(1)
    dev.LEDOFF()
     
def init():
    dev.setup()

def clean():
    GPIO.cleanup()

def modeSelect() -> int:
    # return int(input())
    return dev.main()

def camera_snapshot(UID: str, suffix: str, bright: int, pin: int) -> str:
    dev.LEDON(pin, bright + correction)
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
    tbright = 500
    print("this is testing for camera_snapshot")
    print(f"bright : {tbright}")
    UID = "tester"
    print(camera_snapshot(UID, "test", tbright))

if __name__ == "__main__":
    main()    
    