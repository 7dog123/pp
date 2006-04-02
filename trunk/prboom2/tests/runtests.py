#!/usr/bin/env python
import csv
import codecs
import os
import urllib2
import shutil
import zipfile
import sys
try:
    import subprocess
except ImportError:
    subprocess = None
from pprint import pprint

url_lookup = {
    'COMPETN': 'ftp://competn.doom2.net:8002/pub/compet-n',
    'IDGAMES': 'http://www.gamers.org/pub/idgames',
    'SDA': 'ftp://competn.doom2.net:8002/pub/sda',
}

basepath = None

def iterDemoSpecs(specs):
    #reader = csv.reader(codecs.open(specs,"r","utf-8"))
    reader = csv.reader(open(specs,"r"))
    headers = tuple(reader.next())
    for row in reader:
        row = [x.strip() for x in row]
        spec = dict(zip(headers, row))
        if len(spec):
            yield spec

def getPathToFile(name, path):
    if path == 'n/a':
        if os.path.exists(os.path.abspath(name)):
            return name
        return None
    if path == '':
        return ''
    if path != '':
        parts = path.split('/')
        dirpath = os.path.abspath(os.path.join(*parts[:-1]))
        filename = parts[-1]
        filepath = os.path.abspath(os.path.join(dirpath, name))
        if os.path.exists(filepath):
            return filepath
        if not os.path.exists(path):
            if not os.path.exists(dirpath):
                os.makedirs(dirpath)
            parts[0] = url_lookup.get(parts[0], parts[0])
            url = '/'.join(parts)
            if not url.startswith('http://') \
               and not url.startswith('ftp://'):
                raise ValueError, "unknown url '%s'" % url
            try:
                request = urllib2.urlopen(url)
            except urllib2.HTTPError:
                return None
            dst = open(path, 'wb')
            shutil.copyfileobj(request, dst)
            dst.close()
            request.close()
        if filename != name:
            if filename.lower().endswith('.zip'):
                package = zipfile.ZipFile(path, 'r')
                names = [x for x in package.namelist() if x.lower()==name.lower()]
                if len(names) == 0:
                    return None
                dst = open(filepath, 'wb')
                dst.write(package.read(names[0]))
                dst.close()
                package.close()
        return filepath

def runtest(iwad, demo, demopath, pwad):
    os.chdir(os.path.join(basepath, 'release'))
    options = [
        'prboom',
        '-nodraw',
        '-nosound',
    ]
    options.extend(('-iwad', iwad))
    if demopath is not None and demopath != '':
        options.extend(('-fastdemo', demopath))
    else:
        options.extend(('-fastdemo', demo))
    if pwad is not None and pwad != '':
        options.extend((pwad,))
    cmd = ' '.join(options)
    print cmd
    if subprocess is not None:
        p = subprocess.call(options)
        print p
    else:
        print os.system(cmd)
    result = open(os.path.join(basepath, 'release', 'stderr.txt'),'r').readlines()[-1]
    print result

def getBasePath():
    curpath = os.path.join(os.getcwd(), __file__)
    if not os.path.exists(curpath):
        return
    while 1:
        if os.path.isfile(curpath):
            curpath = os.path.split(curpath)[0]
        if os.path.isdir(curpath):
            contents = os.listdir(curpath)
            if 'prboom.spec.in' in contents:
                return curpath
        oldpath = curpath
        curpath = os.path.split(curpath)[0]
        if oldpath == curpath:
            return

def run():
    global basepath
    basepath = getBasePath()
    if basepath is None:
        raise ValueError, "Can't determine base path"
    for demospec in iterDemoSpecs(os.path.join(basepath, 'tests', 'demo-testing.csv')):
        os.chdir(os.path.join(basepath, 'tests'))
        demoname, demopath = demospec['Demo'], demospec['Demo URL']
        demopath = getPathToFile(demoname, demopath)
        pwadname, pwadpath = demospec['PWAD'], demospec['PWAD url']
        pwadpath = getPathToFile(pwadname, pwadpath)
        iwad = demospec['IWAD']
        runtest(iwad, demoname, demopath, pwadpath)

if __name__=='__main__':
    run()
