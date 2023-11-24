
# import firebase sdk
import firebase_admin
from firebase_admin import db
from firebase_admin import credentials
from firebase_admin import storage

# import camera
from dev import *
import dev
from upload import *

import datetime


# setup
UID = dev.config['UID']
PROJECT_ID = dev.config['PROJECT_ID']
RTDATABASE = dev.config['RTDATABASE']
cred = credentials.Certificate("./serviceKey.json")

firebase_admin.initialize_app(cred,{
    'databaseURL' : f'{RTDATABASE}',
    'storageBucket' : f'{PROJECT_ID}.appspot.com'
})
bucket = storage.bucket()

END = 0
CAMERA = 1
ROTATECAMERA = 2
TEST = 22
BRIGHT_MAX = 5
BRIGHT_MIN = 1

def main():
    # loop
    while(True):
        MODE = modeSelect()
        print(MODE)

        if(MODE == END):
            print("end")
            endProc()

        if(MODE == CAMERA):
            # 일련의 사진 set은 같은 시간정보를 가지게_ 인덱스만 다르게
            suffix = datetime.datetime.now().strftime("%Y%m%d_%H%M")
            # take 5 pictures of one side
            for i in range(BRIGHT_MIN, BRIGHT_MAX+1):
                print(f"picture{i}")
                filename = camera_snapshot(UID, suffix, i * 100)
                storageUpload(filename, UID, bucket)
                RTUpload(filename, UID, bucket, i)

            # alarm
            # wait for button input
            modeSelect()
            # take 5pictures of opposite side
            suffix = "b" + suffix
            for i in range(BRIGHT_MIN, BRIGHT_MAX+1):
                print(f"picture{i}")
                filename = camera_snapshot(UID, suffix, i * 100)
                storageUpload(filename, UID, bucket)
                RTUpload(filename, UID, bucket, i)

        if(MODE == ROTATECAMERA): 
            for i in range(10):
                print(f"picture{i}")
                suffix = "t" + datetime.datetime.now().strftime(f"%Y%m%d_%H%M{i}")
                filename = camera_snapshot(UID, suffix, i)
                turn()
                storageUpload(filename, bucket)
                RTUpload(filename, UID, bucket, i)

        if(MODE == TEST):
            print("test")
            filename = camera_snapshot(UID)
            storageUpload(filename, bucket)

if __name__ == "__main__":
    main()
