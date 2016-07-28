import threading
import urllib2

threads = []
parts = {}
# Initialize threads
# def download(start):
#     req = urllib2.Request(url)
#     req.headers['Range'] = 'bytes=%s-%s' % (start, start + chunk_size)
#     f = urllib2.urlopen(req)
#     parts[start] = f.read()
#
# for i in range(0, 20):
#     t = threading.Thread(download(i * chunk_size))
#     t.start()
#     threads.append(t)
# # Join threads back (order doesn't matter, you just want them all)
# for i in threads:
#     i.join()
#
# for x in parts:uu
#     print parts[x]

def download(start,url,chunk_size):
    req = urllib2.Request(url)
    print "downloading : "+str(start)
    req.headers['Range'] = 'bytes=%s-%s' % (start, start + chunk_size)
    f = urllib2.urlopen(req)
    parts[start] = f.read()

def get_metas(url):
    """
    returns metas of the file in url
    :return: content-length,type
    """
    site = urllib2.urlopen(url)
    meta = site.info()
    return meta['Content-Length'],meta['Content-Type']

def init_downloader(url):
    length,type = get_metas(url)
    chunk_size = int(length)/20
    prev = -1
    for i in range(0,20):
        t = threading.Thread(download(prev+1,url,chunk_size))
        if prev==-1:
            prev=0
        t.start()
        threads.append(t)
        prev+=chunk_size

url = "http://www.vivaan2k16.com/videos/Pick%20&%20place.mp4"
init_downloader(url)
for x in threads:
    while True:
        if x.isAlive():
            continue
        else:
            break

print("Download complete....")
print("Appending")
indices = sorted(parts)
msg = """"""
for x in indices:
    msg+=parts[x]
import os
k = "a.mp4"
print "File name : "+"a.mp4"
f = open(k,"w+")
f.write(msg)
f.close()