''''
Python script to generate irregular beat patterns by Vincent Van den Broeck
Version 2.0 features:
    > better input handling
    > better playback timing

This project was made for HKU, CSD2a

> midi reference: https://stackoverflow.com/a/11060178

'''

from midiutil.MidiFile import MIDIFile
import wave
import time
import simpleaudio as sa

# general variables
sampleNames = [
    ["kick.wav", "orchestral_kick.wav", "lowsynth.wav"],
    ["snare.wav", "orchestral_snare.wav", "midsynth.wav"],
    ["hat.wav", "orchestral_hit.wav", "highsynth.wav"]
]

bpm = 120
beatDivisions = [
    {
        "type": "5/4",
        "numerator": 5,
        "denominator": 4
    },
    {
        "type": "7/8",
        "numerator": 7,
        "denominator": 8
    }
]


def userInput(dataType, prompt, minValue = 0, maxValue = 1):
    validInput = False
    while not validInput:
        try:
            userInput = dataType(input(prompt))

            # check min and max values if input is number
            if dataType == int or dataType == float:
                if userInput < minValue or userInput > maxValue:
                    # input out of range
                    print("Input must be between " + str(minValue) + " and " + str(maxValue))
                else:
                    validInput = True
            else:
                validInput = True
        except:
            # invalid dataType
            print("Input must be of type " + str(dataType))
    return userInput

# user input
division = userInput(int, "Choose beat division. Type 1 for 5/4 or type 2 for 7/8: ", 1, 2) - 1
bpm = userInput(float, "Choose BPM: ", 1.0, 512.0)
samples = [
    {
        "name": "low",
        "audioObject": ""
    },
    {
        "name": "mid",
        "audioObject": ""
    },
    {
        "name": "high",
        "audioObject": ""
    }
]

for i in range (3):
    index = userInput(int, "Choose " + samples[i]["name"] + " sample " + str(sampleNames[i]) + " (1 - 3): ", 1, 3) - 1
    samples[i]["audioObject"] = sa.WaveObject.from_wave_read(wave.open("/Users/vincent/documents/CSD2/CSD2a/eindopdracht/src/assets/" + sampleNames[i][index], 'rb'))

noteEvents = [
    {
        "dur": 0,
        "timestamp": 1.0,
        "sample": 0
    },
     {
        "dur": 0,
        "timestamp": 2.0,
        "sample": 1
    },
     {
        "dur": 0,
        "timestamp": 3.0,
        "sample": 0
    },
     {
        "dur": 0,
        "timestamp": 3.5,
        "sample": 2
    },
]


def playSeq():
    # play through note events
    noteEventsCopy = noteEvents
    startTime = time.time()
    while len(noteEventsCopy) > 0:
        event = noteEventsCopy[0]
        if time.time() - startTime >= event["timestamp"]:
            # play sample
            samples[event["sample"]]["audioObject"].play()
            # remove event from array
            noteEventsCopy.pop(0)
        time.sleep(0.001)
    
playSeq()