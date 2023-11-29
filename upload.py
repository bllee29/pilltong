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

if __name__ == "__main__":
    print("excute main.py")
    