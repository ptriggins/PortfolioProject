#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "cell.h"
#include "frame.h"

#define MARGIN_WIDTH 3

#ifndef BOARD_H
#define BOARD_H

typedef struct BOARD{

  int startRow, startCol;
  int numRows, numCols;
  int topVisibleRow, bottomVisibleRow, leftVisibleCol, rightVisibleCol;
  CELL*** cells;
  FRAME* viewframe;
  WINDOW* window;

}BOARD;

BOARD* board_create(int numRows, int numCols, int availableRows, int availableCols);
void board_draw(BOARD* self);
void board_switch_cells(CELL* currentCell, CELL* nextCell);

#endif
