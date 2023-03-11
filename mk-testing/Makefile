CC=g++
CFLAGS=-c
EXTRA_FLAGS=-lgtest
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): main.o
	$(CC) main.o -o test $(EXTRA_FLAGS)

main.o:	main.cpp 
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f main
	rm -f *.o

PHONY: all clean
