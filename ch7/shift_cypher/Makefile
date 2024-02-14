# Makefile
CC = gcc
CFLAGS = -g -Wall
EXE = main
OBJ = main.o

all: $(OBJ)
	$(CC) -o $(EXE) $(OBJ)
%.o: %.c
	$(CC) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ) $(EXE)
