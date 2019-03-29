#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "tile.h"

#define TILES_PER_BAG 98

typedef struct TILEBAG{

  int numTiles;
  TILE* tiles[TILES_PER_BAG];

}TILEBAG;

TILEBAG* bag_create(char* settingsFile);
TILE* bag_draw_tile(TILEBAG* self);
