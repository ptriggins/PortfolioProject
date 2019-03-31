#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "hand.h"

typedef struct PLAYER{

  int score;
  HAND* hand;
  WINDOW* window;

}PLAYER;

PLAYER* player_create(int startRow, int startCol, TILEBAG* tilebag);
void player_draw(PLAYER* self, int turn);
void player_erase(PLAYER* self);
