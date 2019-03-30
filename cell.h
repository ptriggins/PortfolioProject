#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "tile.h"

#define CELL_WIDTH 5
#define CELL_HEIGHT 3

#define YELLOW 1
#define MAGENTA 2
#define CYAN 3
#define BLUE 4
#define RED 5

#ifndef CELL_H
#define CELL_H

typedef struct CELL{

  char type[3];
  int letterScore, wordScore;
  int color;
  int selected, occupied;
  TILE* temp, *tile;
  struct CELL *above, *below, *left, *right;

}CELL;

CELL* cell_create(char type[3]);
void cell_get_type(char type[3], int yDistance, int xDistance);
void cell_draw(WINDOW* win, int y, int x, CELL* cell);
void cell_place_tile(CELL* self);
void cell_switch_selection(CELL* oldCell, CELL* newCell);
void cell_switch_tile(CELL* oldCell, CELL* newCell);

#endif
