#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "bag.h"

#define TILES_PER_HAND 7
#define LEFT 0
#define RIGHT 1

typedef struct HAND{

  int startRow, startCol;
  int side;
  int numTiles;
  TILE* tiles[TILES_PER_HAND];
  WINDOW* window;

}HAND;

HAND* hand_create(int startRow, int startCol, TILEBAG* tilebag);
void hand_draw(HAND* self);
void hand_erase(HAND* self);
