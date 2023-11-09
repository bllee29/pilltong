
# import firebase sdk
from firebase_admin import db
from firebase_admin import credentials
from firebase_admin import storage

# import camera
from device import *
from upload import *

enumerate

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

CAMERA = 1
TEST = 2

def main():
    # loop
    while(True):
        MODE = modeSelect()
        if(MODE == CAMERA):
            print("camera")
            filename = camera_snapshot(UID)
            storageUpload(filename, bucket)
            RTUpload(filename, bucket)

            
        if(MODE == TEST):
            print("test")
            filename = camera_snapshot(UID)
            storageUpload(filename, bucket)

if __name__ == "__main__":
    main()