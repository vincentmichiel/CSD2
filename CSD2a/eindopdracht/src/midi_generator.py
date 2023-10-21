from midiutil.MidiFile import MIDIFile

def generateMidi(events, bpm):
    # general midi file info
    mf = MIDIFile(1, file_format=1)     # only 1 track
    track = 0
    time = 0
    mf.addTrackName(track, time, "Generated Beat")
    mf.addTempo(track, time, bpm)
    
    # add events to midi sequence
    channel = 0
    volume = 100

    for event in events:
        mf.addNote(track, channel, 60 + event["sample"], event["beat"], 0.1, volume)
    
    # write file to disk
    with open("/Users/vincent/documents/CSD2/CSD2a/eindopdracht/src/output.mid", 'wb') as outf:
        mf.writeFile(outf)