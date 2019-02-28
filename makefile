CC = gcc
CFLAGS = -I.

scrabble: main.c tile.c
	$(CC) -Wall main.c tile.c -lncurses
