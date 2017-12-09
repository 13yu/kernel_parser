from subprocess import Popen, PIPE
import json

def read_physical(offset, size):
    memf = open('/dev/fmem', 'r')
    memf.seek(offset)

    data = memf.read(size)
    return data

def parse(bytes, struct_name):
    p = Popen(['./a.out', bytes], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    output, err = p.communicate(b"input data that is passed to subprocess' stdin")
    if err != '':
        print 'error: ' + err

    return output

data = read_physical(0x1883440, 1024 * 5)
data = data.encode('hex')
dict = parse(data, 'ijfiew')
print dict
dict = json.loads(dict)
print dict
# data = read_physical(0, 100)
# print data.encode('hex')
