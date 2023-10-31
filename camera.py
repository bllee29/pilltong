import datetime
import firebase_admin
from firebase_admin import credentials
from firebase_admin import storage
from uuid import uuid4
import subprocess # Shell Script

# 프로젝트 id
PROJECT_ID = "pilltong-9b8cd" 

# firebase에 연동하기 위한 Key의 디렉토리
cred = credentials.Certificate("./Key/serviceKey.json") 

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
    subtitle = "camera_image/adea78a3388b48afba01ead2b0830b55" # Directory/UID
    suffix = datetime.datetime.now().strftime("%Y%m%d_%H%M%S") + '.jpg' # 현재시간
    filename = "_".join([subtitle, suffix]) # '_' 기준으로 합침
    subprocess.call("libcamera-jpeg -o {}".format(filename), shell=True) # Shell Script(libcamera)
    fileUpload(filename)

print("Start")
camera_snapshot()
print("End")