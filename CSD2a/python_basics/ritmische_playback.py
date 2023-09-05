import wave
import simpleaudio as sa
import time

# read wave file and store as wave object
wave_read = wave.open("/Users/vincent/documents/CSD2/CSD2a/python_basics/bongo.wav", 'rb')
wave_obj = sa.WaveObject.from_wave_read(wave_read)

gotPlaybackTimes = False
gotBpm = False
rhythm = []

# get playback times from user
while not gotPlaybackTimes:
    try:
        numPlaybackTimes = int(input("hoe vaak moet de sample afgespeeld worden?: "))
        gotPlaybackTimes = True
    except:
        # no valid input
        print("Vul een getal in!")


print("Vul nu het ritme in (kwartnoot = 1, halve noot = 2 etc): ")
x = 0
# loop through playback nums
while x < numPlaybackTimes - 1:
    gotRhythmX = False
    # get rhythm for playback num
    while not gotRhythmX:
        try:
            rhythm.append(float(input(str(x + 1) + ": ")))
            gotRhythmX = True
        except:
            # no valid input
            print("Vul een getal in!")
    x += 1

# get bpm from user
while not gotBpm:
    try:
        bpm = int(input("Vul hier het bpm in: "))
        gotBpm = True
    except:
        # no valid input
        print("Vul een getal in!")

# main

# calculate seconds from bpm and rhythm
beats = []
for num in rhythm:
    # convert relative times to seconds
    beats.append(60/(bpm/num))

# play
x = 0
while x < numPlaybackTimes:
    # function to play sample
    wave_obj.play()
    # dont add sleep after last sample play
    if x == numPlaybackTimes - 1:
       break
    # wait for next sample
    time.sleep(beats[x])
    x += 1