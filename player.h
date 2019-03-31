#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "hand.h"

typedef struct PLAYER{

  int score;
  char name[3];
  HAND* hand;
  WINDOW* window;

}PLAYER;

PLAYER* player_create(int startRow, int startCol, TILEBAG* tilebag, char name[3]);
void player_draw(PLAYER* self, int turn);
void player_erase(PLAYER* self);
