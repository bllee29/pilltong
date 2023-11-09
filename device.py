import subprocess
import datetime
from firebase_admin import db
import subprocess # Shell Script

import ctypes

a = ctypes.CDLL("./blink.so")
userInput = a.input

def modeSelect() -> int:
    return userInput()

def camera_snapshot(UID: str) -> str:
    subtitle = f"camera_image/{UID}" # Directory/UID
    suffix = datetime.datetime.now().strftime("%Y%m%d_%H%M%S") + '.jpeg' # 현재시간
    filename = "_".join([subtitle, suffix]) # '_' 기준으로 합침
    subprocess.call("libcamera-jpeg -o {}".format(filename), shell=True) # Shell Script(libcamera)
    return filename

def endProc(fileName: str):
    subprocess.call("libcamera-jpeg -o {}".format(filename), shell=True)


# users_ref.set({
#     'alanisawesome': {
#         'date_of_birth': 'June 23, 1912',
#         'full_name': 'Alan Turing'
#     },
#     'gracehop': {
#         'date_of_birth': 'December 9, 1906',
#         'full_name': 'Grace Hopper'
#     }
# })

# hopper_ref = users_ref.child('gracehop')
# hopper_ref.update({
#     'nickname': 'Amazing Grace'
# })