import wave
import simpleaudio as sa
import time

# function to play sound multiple times
def loopSound(playAmount):
    x = 0
    while x < playAmount:
        # function to play sample
        wave_obj.play()
        time.sleep(1)
        x += 1


# read wave file and store as wave object
wave_read = wave.open("/Users/vincent/documents/CSD2/CSD2a/python_basics/bongo.wav", 'rb')
wave_obj = sa.WaveObject.from_wave_read(wave_read)

samplePlayed = False
while True:
    # ask user how many times to play sample
    playAmountInput = input("Hoe vaak moet de sample afgespeel worden? Vul een getal in: ")

    try:
        # play sample x times
        loopSound(int(playAmountInput))
    except:
        print("Vul een getal in")



