CC=gcc

CFLAGS= -c -Wall

OBJECTS= football.o temperature.o

all:prog

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o prog