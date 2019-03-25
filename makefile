CC = gcc
CFLAGS = -I.

scrabble: main.c board.c cell.c hand.c bag.c tile.c cursor.c
	$(CC) -Wall main.c board.c cell.c hand.c bag.c tile.c cursor.c -lncurses -std=c11
