CC=gcc
CFLAGS=-Os
CFLAGS+=-lm
CFLAGS+=-o clieca

all : clieca

clieca : clieca/main.c
	$(CC) $(CFLAGS) clieca/main.c