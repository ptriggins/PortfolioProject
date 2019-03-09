CC = gcc
CFLAGS = -I.

scrabble: main.c board.c tile.c
	$(CC) -Wall main.c board.c tile.c -lncurses -std=c11
