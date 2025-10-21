CC=gcc

CFLAGS= -c -Wall

all: football temperature

football: football.o
	$(CC) football.o -o football

temperature: temperature.o
	$(CC) temperature.o -o temperature

%.o: %.c
	$(CC) $(CFLAGS) $

clean:
	rm -rf *.o football temperature
