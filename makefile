CC = gcc

main.exe: main.c
	$(CC) -Wall main.c  -lncurses
