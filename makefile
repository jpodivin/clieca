BIN=bin
TEMPOUT=.out
CC=gcc
CFLAGS=-O3
CFLAGS+= -Wall
CFLAGS+= -pedantic
CFLAGS+= -v

all : $(BIN)/clieca

$(BIN)/clieca : $(TEMPOUT)/clieca.o
	mkdir $(BIN) \
	&& $(CC) $(CFLAGS) $< -o $@


$(TEMPOUT)/clieca.o: clieca/main.c
	mkdir $(TEMPOUT)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(BIN) $(TEMPOUT)