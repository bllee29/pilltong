# import firebase_admin
from firebase_admin import db

def storageUpload(fileName, bucket):
    blob = bucket.blob(fileName)
    blob.upload_from_filename(filename=fileName, content_type='jpeg')
    blob.make_public()
    print(blob.public_url)
    print(blob.public_url.split('/')[-1])


def RTUpload(fileName, bucket):
    blob = bucket.blob(fileName)
    dir = db.reference("/test")
    dir.update({'test1':'user1'})

    users_ref = dir.child('images')
    users_ref.update({
        'image' : f'{blob.public_url}'
    })

def main():
    print("Start")
    
    print("End")

if __name__ == "__main__":
    main()