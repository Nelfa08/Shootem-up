CC=gcc
CFLAGS=-Wall -pthread -g
LDFLAGS=-lMLV
BIN= bin/
SRC=src/
INCLUDE=include/
REPBIN= $(BIN)main.o $(BIN)window.o $(BIN)player.o $(BIN)enemy.o $(BIN)keyboard_listener.o $(BIN)party.o
OBJ= main.o window.o player.o enemy.o keyboard_listener.o party.o
MAIN=shootemup

all: $(MAIN)

$(MAIN): $(REPBIN)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(BIN)%.o: $(SRC)%.c
	$(CC) -c -o $@ $< $(CFLAGS) -I $(INCLUDE)

doc:
	doxygen

open-doc:
	firefox generated-docs/html/index.html

clean-doc:
	rm -rf generated-docs/

run:
	./$(MAIN)

rebuild: 
	make clean
	make

clean:
	rm -f $(REPBIN) $(MAIN)

.PHONY: clean
clean-all:
	rm -f $(REPBIN) $(MAIN)
	rm -rf generated-docs/