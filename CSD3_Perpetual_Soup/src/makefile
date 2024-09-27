# Makefile voor Perpetual Soup
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS=
PROG = main
SRC = main.cpp FastFourierTransform.cpp
OBJS = main.o FastFourierTransform.o

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)

