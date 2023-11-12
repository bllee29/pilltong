# import firebase_admin
from firebase_admin import db

# captured time, UID, firebase bucket
def storageUpload(fileName, bucket):
    """for upload firebase storage

    Args:
        fileName: filename
        bucket: firebase bucket

    Returns:
        NONE
    """    
    blob = bucket.blob(fileName)
    blob.upload_from_filename(filename=fileName, content_type='jpeg')
    blob.make_public()
    print(blob.public_url)
    print(blob.public_url.split('/')[-1])

# filename, deviceID, firebasebucket, index
def RTUpload(fileName, UID, bucket, index):
    blob = bucket.blob(fileName)
    dir = db.reference(f'/requests/{UID}')
    users_ref = dir.child('images')
    users_ref.update({
        f'{index}' : f'{blob.public_url}'
    })
    # set
    # users_ref.set(
    #     f'{blob.public_url}'
    # )

def main():
    import firebase_admin
    import firebase_admin
    from firebase_admin import credentials
    from firebase_admin import storage    
    UID = '8084fca6-b5e0-4a46-b395-4874104142cb'
    PROJECT_ID = 'pilltong-9b8cd'
    RTDATABASE = 'https://pilltong-9b8cd-default-rtdb.firebaseio.com'
    fileName = 'camera_image/adea78a3388b48afba01ead2b0830b55_20231108_151351.jpg'
    cred = credentials.Certificate("./serviceKey.json")
    firebase_admin.initialize_app(cred,{
        'databaseURL' : f'{RTDATABASE}',
        'storageBucket' : f'{PROJECT_ID}.appspot.com'
    })
    bucket = storage.bucket()
    blob = bucket.blob(fileName)
    blob.make_public()
    print("Start")
    RTUpload(fileName, UID, bucket)
    print("End")
    # ref = db.reference(f'/requests/{UID}/images')
    # print(type(ref.get()))
    # print(type(ref.get().items()))
    
    

if __name__ == "__main__":
    main()