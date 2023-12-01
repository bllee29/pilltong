# import firebase sdk
import firebase_admin
from firebase_admin import db
from firebase_admin import credentials
from firebase_admin import storage

# import camera functions
from dev import *
import dev

# import upload functions
from upload import *

# import libraries
import datetime
import json

# setup
with open ("config.json", 'r') as f:
    config = json.load(f)
    UID = config['UID']
    PROJECT_ID = config['PROJECT_ID']
    RTDATABASE = config['RTDATABASE']
    cred = credentials.Certificate("./serviceKey.json")

firebase_admin.initialize_app(cred,{
    'databaseURL' : f'{RTDATABASE}',
    'storageBucket' : f'{PROJECT_ID}.appspot.com'
})
bucket = storage.bucket()

END = 22
CAMERA = 1
ROTATECAMERA = 2
TEST = 0

BRIGHT= 1

def main():
    # loop
    while(True):
        MODE = modeSelect()
        print(MODE)

        if(MODE == END):
            print("end")
            endProc()

        if(MODE == CAMERA):
            print("CAMERA")
            # state light on while capturing
            dev.ledInit()

            # picture set of one pill gets same timestamp
            timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M")
            index = 1

            # take 4 pictures with 1 LED
            for i in range(BRIGHT, BRIGHT + 4):
                print(f"take picture with 1LED")
                suffix = "L1_" + timestamp
                filename = camera_snapshot(UID, suffix, i * 100, 1)
                storageUpload(filename, bucket)
                RTUpload(filename, UID, bucket, index)   
                index += 1

            # take 6 pictures with 4 LED
            for i in range(BRIGHT, BRIGHT + 6):
                print(f"picture{i}")
                suffix = "L4_" + timestamp
                filename = camera_snapshot(UID, suffix, i * 100, 2)
                storageUpload(filename, bucket)
                RTUpload(filename, UID, bucket, index)
                index += 1
            
            alarm()

            ## use for other side of pill
            # suffix = "b" + suffix
            # for i in range(BRIGHT, BRIGHT+1):
            #     print(f"picture{i}")
            #     filename = camera_snapshot(UID, suffix, i * 100)
            #     storageUpload(filename,  bucket)
            #     RTUpload(filename, UID, bucket, BRIGHT + i)
            # 

        if(MODE == ROTATECAMERA):
            print("RCAMERA")            
            dev.ledInit()
            # picture set of one pill gets same timestamp
            timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M")
            index = 1

            for i in range(10):
                print(f"picture{i}")
                suffix = f"t{i}_" + timestamp
                filename = camera_snapshot(UID, suffix, 250)
                turn()
                storageUpload(filename, bucket)
                RTUpload(filename, UID, bucket, i)
             

        if(MODE == TEST):
            print("test")
            alarm()            
            break
            # suffix = "testPicture" + datetime.datetime.now().strftime(f"%Y%m%d_%H%M{i}")
            # filename = camera_snapshot(UID, suffix, 250)
            # storageUpload(filename, bucket)
            # RTUpload(filename, UID, bucket, i)

    dev.clean()      


if __name__ == "__main__":
    print("waiting for input...")
    init()
    main()
