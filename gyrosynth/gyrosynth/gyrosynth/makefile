# Makefile voor HelloGoodbye
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS=-ljack -llo
PROG = main
SRC = main.cpp Oscillator.cpp Synth.cpp FMSynth.cpp osc.cpp
OBJS = main.o Oscillator.o Synth.o FMSynth.o osc.o

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)
