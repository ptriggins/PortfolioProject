#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct FRAME{

  int topRow, bottomRow, leftCol, rightCol;
  int centerRow, centerCol;

}FRAME;

FRAME *frame_create(int numRows, int numCols, int availableRows, int availableCols);
void frame_move_up(FRAME* self);
void frame_move_down(FRAME* self);
void frame_move_left(FRAME* self);
void frame_move_right(FRAME* self);
