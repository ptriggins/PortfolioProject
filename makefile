CC = gcc
CFLAGS = -I.

scrabble: newMain.c button.c board.c tile.c
	$(CC) -Wall newMain.c button.c board.c tile.c -lncurses -std=c11
