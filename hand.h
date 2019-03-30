#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "bag.h"

#define LEFT 0
#define RIGHT 1

#ifndef HAND_H
#define HAND_H

typedef struct HAND{

  int numTiles, side;
  TILE* tiles[7];
  WINDOW* window;

}HAND;

HAND* hand_create(int startRow, int startCol, TILEBAG* tilebag);
void hand_draw(HAND* self);
void hand_erase(HAND* self);

#endif
