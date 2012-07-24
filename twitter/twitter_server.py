import lightblue
import twitter
import sys
import time

api = twitter.Api(consumer_key='A04Um45pa3mfDYy0gyl5g',
                  consumer_secret='rzDhek1VjTSaeHNV4NwrFxj3IcRuGVIffgtv474Vq5U',
                  access_token_key='15821652-aNPNuwCivPFByvYyPWNGieLB4FK9G70QVP7gqcL3x',
                  access_token_secret='Xsr0DvQXlLnt9nYoFzfHm0P5deks3sBrKnlURcz0')


print 'Connecting to the bluetooth chip'
s = lightblue.socket()
s.connect(('00:12:04:06:71:54', 1))

range = 0
twitter = None

while True:
    if range == 30 or twitter is None:
        statuses = api.GetUserTimeline('tarek_ziade')
        twitter = statuses[0].text.encode('utf8')
        range = 0

    start = 0
    pos = 32

    while start < len(twitter):
        s.sendall('*')
        s.sendall(twitter[start:pos])
        start += 32
        pos += 32
        time.sleep(2.)

    range += 1
