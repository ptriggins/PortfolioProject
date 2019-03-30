#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "tile.h"

typedef struct TILEBAG{

  int numTiles;
  TILE* tiles[100];

}TILEBAG;

void bag_init(TILEBAG* self, char* settingsFile);
TILEBAG* bag_create(char* settingsFile);
TILE* bag_draw_tile(TILEBAG* self);
