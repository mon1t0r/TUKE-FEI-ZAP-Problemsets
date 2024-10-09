# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wno-vla-parameter
LDLIBS=-lm -lcurses
OUTPUT=ballsortpuzzle

# targets
all: $(OUTPUT)

$(OUTPUT): ballsortpuzzle.o c4.o main.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) ballsortpuzzle.o c4.o main.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

ballsortpuzzle.o: ballsortpuzzle.c ballsortpuzzle.h
	$(CC) $(CFLAGS) -c ballsortpuzzle.c $(LDLIBS) -o ballsortpuzzle.o

c4.o: c4.c c4.h
	$(CC) $(CFLAGS) -c c4.c $(LDLIBS) -o c4.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o
