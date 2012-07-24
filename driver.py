import lightblue


print 'connecting to the bluetooth chip'
s = lightblue.socket()
s.connect(('00:12:04:06:71:54', 1))

while True:
    data = raw_input('Type data ')
    s.sendall(data)
