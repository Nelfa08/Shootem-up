CC=gcc
CFLAGS=-Wall
LDFLAGS=-lMLV
REPOBJ=bin/main.o bin/window.o bin/player.o bin/enemy.o
OBJ=main.o window.o player.o enemy.o
MAIN=shootem
BIN= ./bin/

all: $(OBJ)
	$(CC) -o $(MAIN) $(REPOBJ) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS) -o $(BIN)$@

window.o: src/window.c include/window.h include/const.h include/struct.h
	$(CC) -c src/window.c $(CFLAGS) -o $(BIN)$@

player.o: src/player.c include/player.h include/const.h include/struct.h
	$(CC) -c src/player.c $(CFLAGS) -o $(BIN)$@

enemy.o: src/enemy.c include/enemy.h include/const.h include/struct.h
	$(CC) -c src/enemy.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)

clean: 
	rm -f bin/*
	rm -f *.o
	rm -f *~
	rm -f $(MAIN)
