
# import firebase sdk
import firebase_admin
from firebase_admin import db
from firebase_admin import credentials
from firebase_admin import storage

# import camera
from device import *
from upload import *

UID = '8084fca6-b5e0-4a46-b395-4874104142cb'
PROJECT_ID = "pilltong-9b8cd"
RTDATABASE = "https://pilltong-9b8cd-default-rtdb.firebaseio.com"

# setup
cred = credentials.Certificate("./serviceKey.json")
firebase_admin.initialize_app(cred,{
    'databaseURL' : f'{RTDATABASE}',
    'storageBucket' : f'{PROJECT_ID}.appspot.com'
})
bucket = storage.bucket()

END = 0;
CAMERA = 1
ROTATECAMERA = 2
TEST = 22

def main():
    # loop
    while(True):
        MODE = modeSelect()

        if(MODE == END):
            print("end")
            endProc()

        if(MODE == CAMERA):
            for i in range(5):
                print(f"picture{i}")
                filename = camera_snapshot(UID, i * 100)
                storageUpload(filename, UID, bucket)
                RTUpload(filename, UID, bucket, i)

        if(MODE == ROTATECAMERA):
            for i in range(10):
                print(f"picture{i}")
                filename = camera_snapshot(UID, 100)
                storageUpload(filename, UID, bucket)
                RTUpload(filename, UID, bucket, i)

        if(MODE == TEST):
            print("test")
            filename = camera_snapshot(UID)
            storageUpload(filename, bucket)

if __name__ == "__main__":
    main()
