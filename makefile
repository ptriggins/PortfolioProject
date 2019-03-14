CC = gcc
CFLAGS = -I.

scrabble: newMain.c menu.c button.c board.c tile.c
	$(CC) -Wall newMain.c menu.c button.c board.c tile.c -lncurses -std=c11
