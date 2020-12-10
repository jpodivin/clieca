BIN=bin
CC=gcc
CFLAGS=-Os
CFLAGS+= -Wall
CFLAGS+= -pedantic

all : $(BIN)/clieca
	

$(BIN)/clieca : clieca/main.c
	mkdir bin \
	&& $(CC) $(CFLAGS) $< -o $@
