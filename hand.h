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

}HAND;

HAND* hand_create(int startRow, int startCol, TILEBAG* tilebag);
void hand_draw(HAND* self, WINDOW* win);
void hand_erase(HAND* self, WINDOW* win);
void hand_remove_tile(HAND* self, TILE* tile, TILEBAG* tilebag);
int hand_get_next_tile(HAND* self, int start);
int hand_get_last_tile(HAND* self, int start);

#endif
