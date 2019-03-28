#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct PLAYER{

  int score;
  int hand;
  WINDOW* window;

}PLAYER;

PLAYER* player_create();
