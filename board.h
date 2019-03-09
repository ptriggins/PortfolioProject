#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "tile.h"

typedef struct BOARD{

  // Size and location of the gmae board
  int rows, cols;
  int startX;
  int startY;

  WINDOW* win;
  TILE* tiles[20][20];

}BOARD;

BOARD* createBoard(int rows, int cols);
void drawBoard(BOARD* self);
