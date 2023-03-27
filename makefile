CC=gcc
CFLAGS=-Wall -std=c17 -pthread
LDFLAGS=-lMLV
REPOBJ=bin/main.o bin/window.o bin/player.o bin/enemy.o bin/keyboard_listener.o bin/party.o
OBJ=main.o window.o player.o enemy.o keyboard_listener.o party.o
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

keyboard_listener.o: src/keyboard_listener.c include/keyboard_listener.h include/const.h include/struct.h
	$(CC) -c src/keyboard_listener.c $(CFLAGS) -o $(BIN)$@

party.o: src/party.c include/party.h include/const.h include/struct.h
	$(CC) -c src/party.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)

clean: 
	rm -f bin/*
	rm -f *.o
	rm -f *~
	rm -f $(MAIN)
