import datetime
import firebase_admin
from firebase_admin import credentials
from firebase_admin import storage
from uuid import uuid4
import subprocess # For using Shell Script

PROJECT_ID = "pilltong-9b8cd" # Owner Project ID

cred = credentials.Certificate("./Key/serviceKey.json") # Service Key Path

default_app = firebase_admin.initialize_app(cred, {
    'storageBucket': f"{PROJECT_ID}.appspot.com"
})
bucket = storage.bucket()

def fileUpload(file):
    blob = bucket.blob(file)
    new_token = uuid4()
    metadata = {"firebaseStorageDownloadTokens": new_token}
    blob.metadata = metadata
    blob.upload_from_filename(filename=file, content_type='image/jpeg')
    print(blob.public_url) # Storage path print
    print(blob.public_url.split('/')[-1])

def camera_snapshot():
    subtitle = "camera_image/adea78a3388b48afba01ead2b0830b55" # 직접 지정해준 Directory/UID
    suffix = datetime.datetime.now().strftime("%Y%m%d_%H%M%S") + '.jpg' # 현재시간
    filename = "_".join([subtitle, suffix]) # 둘을 '_' 기준으로 합침
    subprocess.call("libcamera-jpeg -o {}".format(filename), shell=True) # Shell Script 실행 (libcamera 이용)
    fileUpload(filename)

print("Start ......")
camera_snapshot()
print("End Of File")