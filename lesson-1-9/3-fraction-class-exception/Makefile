CC=g++
CFLAGS=-c
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): main.o Fraction.o
	$(CC) main.o Fraction.o -o main

main.o:	main.cpp 
	$(CC) $(CFLAGS) main.cpp

Fraction.o: Fraction.cpp
	$(CC) $(CFLAGS) Fraction.cpp

clean:
	rm -f main
	rm -f *.o

PHONY: all clean
