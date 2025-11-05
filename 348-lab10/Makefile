CC=g++

CFLAGS= -c -Wall

OBJECTS= calculator.o

all:prog

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o prog