# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=#-lm
OUTPUT=hangman

# targets
all: $(OUTPUT)

$(OUTPUT): hangman.o main.o morse.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) hangman.o main.o morse.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

hangman.o: hangman.c hangman.h
	$(CC) $(CFLAGS) -c hangman.c $(LDLIBS) -o hangman.o

morse.o: hangman.c hangman.h
	$(CC) $(CFLAGS) -c morse.c $(LDLIBS) -o morse.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o


