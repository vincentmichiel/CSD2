# Makefile voor HelloGoodbye
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS=-ljack
PROG = main
SRC = main.cpp Effect.cpp Tremolo.cpp Delay.cpp Waveshaper.cpp CircBuffer.cpp Oscillator.cpp Interpolate.cpp WavetableGenerator.cpp
OBJS = main.o Effect.o Tremolo.o Delay.o Waveshaper.o CircBuffer.o Oscillator.o Interpolate.o WavetableGenerator.o

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)
