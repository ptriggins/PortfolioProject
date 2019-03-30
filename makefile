CC = gcc
CFLAGS = -I.

scrabble: main.c board.c cell.c hand.c bag.c dictionary.c player.c word.c frame.c tile.c
	$(CC) -Wall main.c board.c cell.c hand.c bag.c dictionary.c player.c word.c frame.c tile.c -lncurses -std=c11
