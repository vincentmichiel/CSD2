import wave
import simpleaudio as sa
import time

beatDivisions = [
    {
        "division": "5/4",
        "16ths": [
            # 1
            {
                "low chance": 90,
                "mid chance": 40,
                "high chance": 60
            },
            {
                "low chance": 10,
                "mid chance": 40,
                "high chance": 90
            },
            {
                "low chance": 10,
                "mid chance": 65,
                "high chance": 50
            },
            {
                "low chance": 30,
                "mid chance": 25,
                "high chance": 90
            },
            # 2
            {
                "low chance": 30,
                "mid chance": 40,
                "high chance": 60
            },
            {
                "low chance": 10,
                "mid chance": 40,
                "high chance": 90
            },
            {
                "low chance": 10,
                "mid chance": 65,
                "high chance": 50
            },
            {
                "low chance": 15,
                "mid chance": 25,
                "high chance": 90
            },
            # 3
            {
                "low chance": 50,
                "mid chance": 40,
                "high chance": 60
            },
            {
                "low chance": 10,
                "mid chance": 40,
                "high chance": 90
            },
            {
                "low chance": 10,
                "mid chance": 65,
                "high chance": 50
            },
            {
                "low chance": 30,
                "mid chance": 25,
                "high chance": 90
            },
            # 4
            {
                "low chance": 75,
                "mid chance": 40,
                "high chance": 60
            },
            {
                "low chance": 10,
                "mid chance": 40,
                "high chance": 90
            },
            {
                "low chance": 10,
                "mid chance": 65,
                "high chance": 50
            },
            {
                "low chance": 30,
                "mid chance": 25,
                "high chance": 60
            },
            # 5
            {
                "low chance": 30,
                "mid chance": 40,
                "high chance": 60
            },
            {
                "low chance": 10,
                "mid chance": 40,
                "high chance": 90
            },
            {
                "low chance": 10,
                "mid chance": 65,
                "high chance": 50
            },
            {
                "low chance": 30,
                "mid chance": 25,
                "high chance": 30
            }
        ]
    },
    {
        "division": "7/8",
        "16ths": []
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
            print("samples: 1. kick 2. djembe 3. bass")
        case "mid":
            print("samples: 1. snare 2. bongo 3. cello")
        case "high":
            print("samples: 1. hi-hat 2. glass 3. violin")

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