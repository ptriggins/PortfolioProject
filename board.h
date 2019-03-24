#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "cell.h"

typedef struct BOARD{

  int y, x;
  int numRows, numCols;
  int topVisibleRow, bottomVisibleRow, leftVisibleCol, rightVisibleCol;
  CELL*** cells;
  WINDOW* window;

}BOARD;

BOARD* board_create(int numRows, int numCols, int screenRows, int screenCols);
void board_draw(BOARD* self);
