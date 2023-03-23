CC=gcc
CFLAGS=-Wall -std=c17
LDFLAGS=-lMLV
REPOBJ=bin/shootem.o bin/view.o
OBJ=shootem.o view.o
MAIN=shootem
BIN= ./bin/

shootem: $(OBJ)
	$(CC) -o $(MAIN) $(REPOBJ) $(LDFLAGS)

shootem.o: src/shootem.c
	$(CC) -c src/shootem.c $(CFLAGS) -o $(BIN)$@

view.o: src/view.c include/view.h
	$(CC) -c src/view.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)

clean: 
	rm -f bin/*
	rm -f *.o
	rm -f *~
	rm -f $(MAIN)
