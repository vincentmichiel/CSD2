''''
Python script to generate irregular beat patterns by Vincent Van den Broeck
Version 2.0 features:
    > more efficient input handling
    > improved playback timing

This project was made for HKU, CSD2a
'''

from midiutil.MidiFile import MIDIFile
import wave
import time
import simpleaudio as sa
import lightmap_generator
import midi_generator
import math

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
beatTime = float(60)/bpm

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

def playSeq(noteEvents):
    # play through note events
    startTime = time.time()
    i = 0
    while i < len(noteEvents):
        event = noteEvents[i]
        if time.time() - startTime >= event["timestamp"]:
            # play sample
            samples[event["sample"]]["audioObject"].play()
            i += 1
        time.sleep(0.001)

def main():
    noteEvents = []
    finalEvents = []
    for i in range (beatDivisions[division]["numerator"]):
        noteEvents.append([])

    # generate events
    image, eventData = lightmap_generator.generateEvents(beatDivisions[division]["numerator"])
    largestR = 0
    smallestR = 100

    # generate base events
    for event in eventData:
        beat = math.floor(event["x"] / (image[1]/beatDivisions[division]["numerator"]))
        if event["r"] > largestR:
            largestR = event["r"]
        if event["r"] < smallestR:
            smallestR = event["r"]

        newEvent = {
            "x": event["x"],
            "r": event["r"],
            "beat": beat,
            "timestamp": 0,
            "sample": 0
        }

        noteEvents[beat].append(newEvent)

    # divide radius in 3 bounds
    middle = (smallestR + largestR) / 2
    divider = middle/3
    small = middle - divider
    large = middle + divider

    # assign low mid or high sample based on radius
    for beat in noteEvents:
        eventAmount = 0
        for event in beat:
            eventAmount += 1
            sample = 0
            if event["r"] <= small:
                sample = 2
            elif event["r"] <= large:
                sample = 1

            event["sample"] = sample
        
        # shift beat timing based on number of hits in beat (spread evenly)
        iterator = 0
        if eventAmount > 0:
            beatTiming = 1/eventAmount
        else:
            beatTiming = 0
        for event in beat:
            event["beat"] = float(event["beat"] + beatTiming * iterator)
            event["timestamp"] = event["beat"] * beatTime
            finalEvents.append(event)
            iterator += 1

    noteEvents = finalEvents

    playSeq(noteEvents)

    next = userInput(int, "Type 1 to stop and store to midi, 2 to generate another rhythm: ", 1, 2) - 1

    if next == 1:
        main()
    else:
        midi_generator.generateMidi(noteEvents, bpm)

main()