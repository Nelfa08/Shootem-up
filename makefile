CC=gcc
CFLAGS=-Wall
LDFLAGS=-lMLV
REPOBJ=bin/main.o bin/window.o
OBJ=main.o window.o
MAIN=shootem
BIN= ./bin/

main: $(OBJ)
	$(CC) -o $(MAIN) $(REPOBJ) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS) -o $(BIN)$@

window.o: src/window.c include/window.h include/const.h
	$(CC) -c src/window.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)

clean: 
	rm -f bin/*
	rm -f *.o
	rm -f *~
	rm -f $(MAIN)
