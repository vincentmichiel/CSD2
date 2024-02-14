''''
Python script to generate irregular beat patterns by Vincent Van den Broeck
This project was made for HKU, CSD2a

> midi reference: https://stackoverflow.com/a/11060178

'''

from midiutil.MidiFile import MIDIFile
import wave
import simpleaudio as sa
import time
import random

beatDivisions = [
    {
        "division": "5/4",
        "counts": 5,
        "timeMultiplier": 2,
        "16ths": [
            # 1
            [
                [90, 5, 60] # low mid high chance
            ],
            [
                [5, 5, 90]
            ],
            [
                [5, 3, 60]
            ],
            [
                [5, 2, 80]
            ],
            # 2
            [
                [70, 5, 60] # low mid high chance
            ],
            [
                [2, 10, 90]
            ],
            [
                [4, 80, 50]
            ],
            [
                [5, 4, 90]
            ],
            # 3
            [
                [75, 10, 30] # low mid high chance
            ],
            [
                [2, 5, 90]
            ],
            [
                [5, 10, 50]
            ],
            [
                [1, 1, 90]
            ],
            # 4
            [
                [90, 10, 30] # low mid high chance
            ],
            [
                [5, 12, 90]
            ],
            [
                [5, 65, 50]
            ],
            [
                [5, 2, 80]
            ],
            # 5
            [
                [85, 10, 60] # low mid high chance
            ],
            [
                [5, 10, 90]
            ],
            [
                [20, 70, 30]
            ],
            [
                [3, 25, 60]
            ],
        ]
    },
    {
        "division": "7/8",
        "counts": 7,
        "timeMultiplier": 3,
        "16ths": [
            #1
            [[90, 6, 5]],
            [[5, 2, 70]],
            [[10, 80, 30]],
            [[2, 3, 65]],
            [[85, 3, 10]],
            [[5, 5, 80]],
            [[60, 20, 90]],
            #2
            [[90, 10, 3]],
            [[5, 5, 85]],
            [[10, 40, 70]],
            [[5, 80, 40]],
            [[70, 4, 4]],
            [[2, 5, 90]],
            [[60, 2, 70]],
        ]
    }
]

bpm = 120
division = 0

# user input
# beat division
divisionInput = False
while not divisionInput:
    try:
        division = int(input("Choose beat division. Type 1 for 5/4 or type 2 for 7/8: ")) - 1
        if division < 0 or division > 1:
            # input out of range
            print("Choose either 1 or 2!")
        else:
            # got valid input
            divisionInput = True
    except:
        # not an integer
        print("Choose either 1 or 2!")

# bpm input
bpmInput = False
while not bpmInput:
    try:
        bpm = int(input("Choose BPM: "))
        bpmInput = True
    except:
        print("BPM must be a number!")


# sample selection
def sampleSelect(sample):
    match sample:
        case "low":
            print("samples: 1. kick 2. orchestral kick 3. bass")
        case "mid":
            print("samples: 1. snare 2. orchestral snare 3. cello")
        case "high":
            print("samples: 1. hi-hat 2. orchestral hit 3. violin")

    sampleInput = False
    while not sampleInput:
        try:
            sampleStore = int(input("Choose " + sample + " sample (1 - 3): "))
            if sampleStore < 1 or sampleStore > 3:
                # input out of range
                print("Must be a number between 1 and 3")
            else:
                # valid input
                sampleInput = True
        except:
            # not a number
            print("Must be a number!")

    return sampleStore

low_sample = sampleSelect("low")
mid_sample = sampleSelect("mid")
high_sample = sampleSelect("high")

selectedSamples = [low_sample, mid_sample, high_sample]

# calculate 16th time in seconds
beatTime = ((60/(bpm)) / beatDivisions[division]["counts"]) * beatDivisions[division]["timeMultiplier"]

# load audio samples
sampleNames = [
    ["kick.wav", "orchestral_kick.wav", "lowsynth.wav"],
    ["snare.wav", "orchestral_snare.wav", "midsynth.wav"],
    ["hat.wav", "orchestral_hit.wav", "highsynth.wav"]
]

samples = []

assignSample = 0
while assignSample < 3:
    samples.append(sa.WaveObject.from_wave_read(wave.open("/Users/vincent/documents/CSD2/CSD2a/eindopdracht/src/assets/" + sampleNames[assignSample][selectedSamples[assignSample] - 1], 'rb')))
    assignSample += 1

# play events
def playbackHandler(event):
    # handles playback events
    samples[event["sample"] - 1].play()

def createMidiFile(importEvents):
    # general midi file info
    mf = MIDIFile(1, file_format=1)     # only 1 track
    track = 0
    time = 0
    mf.addTrackName(track, time, "Generated Beat")
    mf.addTempo(track, time, bpm)
    
    # add events to midi sequence
    channel = 0
    volume = 100

    for event in importEvents:
        mf.addNote(track, channel, event["midiPitch"], event["midiTime"], event["midiDuration"], volume)
    
    # write file to disk
    with open("/Users/vincent/documents/CSD2/CSD2a/eindopdracht/src/output.mid", 'wb') as outf:
        mf.writeFile(outf)

events = []
def generateSequence():
    # generate events for low mid and high samples

    events = []

    sampleIterator = 0
    while sampleIterator < 3: # loop through low mid and high samples
        _16th = 0
        while _16th < len(beatDivisions[division]["16ths"]): # < total amount of 16ths
            # chance to generate event                                            chance from beatdivisions array
            if random.randint(1, 100) < beatDivisions[division]["16ths"][_16th][0][sampleIterator]:
                # generate event on 16th timestamp
                eventStore = {
                    "timestamp": _16th * beatTime,
                    "sample": sampleIterator + 1,
                    "midiPitch": 60 + sampleIterator,
                    "midiTime": _16th/2,
                    "midiDuration": 0.25
                }
                events.append(eventStore)
            _16th += 1
        sampleIterator += 1
    
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

    # ask user to store midi file
    storeMidi = 0
    gotMidiStore = False
    while not gotMidiStore:
        try:
            storeMidi = int(input("Save to MIDI?. 1. Yes 2. No: ")) - 1
            if division < 0 or division > 1:
                # input out of range
                print("Choose either 1 or 2!")
            else:
                # got valid input
                gotMidiStore = True
        except:
            # not an integer
            print("Choose either 1 or 2!")

    if storeMidi == 1:
        # user doesnt want to store midi, generate new sequence
        generateSequence()
    else:
        createMidiFile(events)

generateSequence()