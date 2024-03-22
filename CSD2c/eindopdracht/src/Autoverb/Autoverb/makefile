# Makefile voor HelloGoodbye
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS=-ljack
PROG = main
SRC = main.cpp Effect.cpp CircBuffer.cpp Oscillator.cpp Delay.cpp MultitapDelay.cpp Moddelay.cpp AllpassFilter.cpp AllpassBuffer.cpp interpolation.cpp
OBJS = main.o Effect.o CircBuffer.o Oscillator.o Delay.o MultitapDelay.o Moddelay.o AllpassFilter.o AllpassBuffer.o interpolation.o
$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)
