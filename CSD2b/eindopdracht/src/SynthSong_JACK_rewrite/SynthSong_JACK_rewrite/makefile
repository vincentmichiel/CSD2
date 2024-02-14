# Makefile voor HelloGoodbye
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS=-ljack -lportmidi
PROG = main
SRC = main.cpp Oscillator.cpp Synth.cpp AnalogSynth.cpp FMSynth.cpp UI.cpp Melody.cpp midi_io.cpp
OBJS = main.o Oscillator.o Synth.o AnalogSynth.o FMSynth.o UI.o Melody.o midi_io.o

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)
