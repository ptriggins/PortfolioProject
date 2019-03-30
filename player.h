#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "hand.h"

typedef struct PLAYER{

  int score, turn;
  HAND* hand;

}PLAYER;

PLAYER* player_create(int startRow, int startCol, TILEBAG* tilebag);
