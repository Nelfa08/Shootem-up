CC=gcc
CFLAGS=-Wall -lm
LDFLAGS=-lMLV
BIN= bin/
SRC=src/
REPBIN= $(BIN)main.o $(BIN)window.o $(BIN)player.o $(BIN)enemy.o $(BIN)keyboard_listener.o $(BIN)party.o $(BIN)bullet_player.o $(BIN)bullet_enemy.o $(BIN)bonus.o $(BIN)penalty.o $(BIN)sprite.o
OBJ= main.o window.o player.o enemy.o keyboard_listener.o party.o bullet_player.o bullet_enemy.o bonus.o penalty.o sprite.o
MAIN=shootemup

$(MAIN): $(REPBIN)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(BIN)%.o: $(SRC)%.c
	$(CC) -c -o $@ $< $(CFLAGS)

all:
	make
	make doc

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