#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "tile.h"

#define TILES_PER_BAG 100

typedef struct TILEBAG{

  int numTiles;
  TILE* tiles[TILES_PER_BAG];

}TILEBAG;

TILEBAG* bag_create();
TILE* bag_draw_tile(TILEBAG* self);
