CC = gcc
CFLAGS = -I.

scrabble: main.c board.c cell.c
	$(CC) -Wall main.c board.c cell.c -lncurses -std=c11
