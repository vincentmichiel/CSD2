import wave
import simpleaudio as sa
import time

playing = True

# read wave files and store as wave object
#1
wave_read = wave.open("/Users/vincent/documents/CSD2/CSD2a/event_based_sequencer/assets/sample1.wav", 'rb')
sample1 = sa.WaveObject.from_wave_read(wave_read)
#2
wave_read = wave.open("/Users/vincent/documents/CSD2/CSD2a/event_based_sequencer/assets/sample2.wav", 'rb')
sample2 = sa.WaveObject.from_wave_read(wave_read)
#3
wave_read = wave.open("/Users/vincent/documents/CSD2/CSD2a/event_based_sequencer/assets/sample3.wav", 'rb')
sample3 = sa.WaveObject.from_wave_read(wave_read)


events = [
    {
        "timestamp": 1,
        "sample": 3
    },
    {
        "timestamp": 1.75,
        "sample": 3
    },
    {
        "timestamp": 2.75,
        "sample": 3
    },
    {
        "timestamp": 3,
        "sample": 3
    },
    {
        "timestamp": 3.5,
        "sample": 3
    },
    {
        "timestamp": 2,
        "sample": 2
    },
    {
        "timestamp": 4,
        "sample": 2
    },
    {
        "timestamp": 1,
        "sample": 1
    },
    {
        "timestamp": 1.5,
        "sample": 1
    },
    {
        "timestamp": 2,
        "sample": 1
    },
    {
        "timestamp": 2.25,
        "sample": 1
    },
    {
        "timestamp": 2.375,
        "sample": 1
    },
    {
        "timestamp": 2.5,
        "sample": 1
    },
    {
        "timestamp": 2.75,
        "sample": 1
    },
    {
        "timestamp": 3,
        "sample": 1
    },
    {
        "timestamp": 3.5,
        "sample": 1
    }
]


def playbackHandler(event):
    # handles playback events
    match event["sample"]:
        case 1:
            sample1.play()
        case 2:
            sample2.play()
        case 3:
            sample3.play()
        case _:
            # invalid sample
            print("playbackhandler error: invalid sample index")

# sort events by timestamps
events = sorted(events, key=lambda timestamp: timestamp['timestamp'])

# loop through events
iterator = 0
while iterator < len(events):
    # play sample
    playbackHandler(events[iterator])
    if iterator == len(events) - 1:
        break
    # wait for next timestamp
    time.sleep(float(events[iterator + 1]["timestamp"]) - float(events[iterator]["timestamp"]))
    iterator += 1