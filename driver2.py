import sys
import tty
import termios
import lightblue

print 'connecting to the bluetooth chip'
s = lightblue.socket()
s.connect(('00:12:04:06:71:54', 1))
print 'connected'
print 'use the arrows to drive'


def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ord(ch)

def up():
    s.sendall('F')

def down():
    s.sendall('B')

def left():
    s.sendall('L')

def right():
    s.sendall('R')

def stop():
    s.sendall('S')

code = -1
buffer = []

while code != 3:
    code = getch()
    if code == 27 and len(buffer) == 0:
        buffer.append(code)
    elif code == 91 and len(buffer) == 1:
        buffer.append(code)
    elif code in (65, 66, 67, 68) and len(buffer) == 2:
        buffer = []
        if code == 65:
            up()
        elif code == 66:
            down()
        elif code == 67:
            right()
        else:
            left()
    else:
        stop()

