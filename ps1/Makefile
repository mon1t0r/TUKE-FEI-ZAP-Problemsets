# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lsuperkarel -lcurses
OUTPUT=$@

# targets
%: %.c
	$(CC) $(CFLAGS) $@.c $(LDLIBS) -o $(OUTPUT)


