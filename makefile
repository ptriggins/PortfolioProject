CC = gcc
CFLAGS = -I.

scrabble: newMain.c button.c
	$(CC) -Wall newMain.c button.c -lncurses -std=c11
