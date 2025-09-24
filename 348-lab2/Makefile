CC=g++

CFLAGS=-c-Wall

OBJECTS= main.o isOdd.o isEven.o

all:prog

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o prog