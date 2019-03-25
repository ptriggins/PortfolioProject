#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define TILE_HEIGHT 3
#define TILE_WIDTH 5

typedef struct TILE{

  char letter;
  int letterValue;
  int selected, chosen, played;

}TILE;

TILE* tile_create(char letter);
void tile_draw(TILE* self);
