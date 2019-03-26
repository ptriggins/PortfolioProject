#include "board.h"

// Initializes all of a board's attributes
void board_init(BOARD* self, int numRows, int numCols, int screenRows, int screenCols){

  if (numRows <= screenRows)
    self->startRow = ((screenRows / 2) - (numRows / 2));
  else
    self->startRow = 0;

  if(numCols <= screenCols - (2 * MARGIN_WIDTH))
    self->startCol = ((screenCols / 2) - (numCols / 2));
  else
    self->startCol = MARGIN_WIDTH;

  self->numRows = numRows;
  self->numCols = numCols;

  int cellRow, cellCol;
  char type[3];

  int topY = -numRows / 2;
  int topX = -numCols / 2;

  for(int i = topY; i < topY + numRows; i++){
    for(int j = topX; j < topX + numCols; j++){

      cellRow = i + numRows / 2;
      cellCol = j + numCols / 2;

      cell_get_type(type, abs(i), abs(j));

      self->cells[cellRow][cellCol] = cell_create(type);

    }
  }

  if (numRows <= screenRows){
    self->topVisibleRow = 0;
    self->bottomVisibleRow = numRows - 1;
  }
  else{
    self->topVisibleRow = (numRows - screenRows) / 2;
    self->bottomVisibleRow = (numRows - self->topVisibleRow) - 1;
  }

  if (numCols <= screenCols - (2 * MARGIN_WIDTH)){
    self->leftVisibleCol = 0;
    self->rightVisibleCol = numCols - 1;
  }
  else{
    self->leftVisibleCol = (numCols - (screenCols - (2 * MARGIN_WIDTH))) / 2;
    self->rightVisibleCol = (numCols - self->leftVisibleCol) - 2;
  }

  self->window = newwin(screenRows * CELL_HEIGHT, (screenCols - MARGIN_WIDTH) * CELL_WIDTH, self->startRow * CELL_HEIGHT, self->startCol * CELL_WIDTH);

}

// Allocates memory for a board with variable rows and columns
BOARD* board_create(int numRows, int numCols, int screenRows, int screenCols){

  BOARD* newBoard = (BOARD*) malloc(sizeof(BOARD));

  // Allocates memory for a two dimensional array of cell pointers
  newBoard->cells = (CELL***) malloc(numRows * sizeof(CELL**));
  for (int i = 0; i < numRows; i++){
    newBoard->cells[i] = (CELL**) malloc(numCols * sizeof(CELL*));
  }

  board_init(newBoard, numRows, numCols, screenRows, screenCols);
  return newBoard;

}

void board_draw(BOARD* self){

  int y = 0, x = 0;

  for (int i = self->topVisibleRow; i <= self->bottomVisibleRow; i++){
    for (int j = self->leftVisibleCol; j <= self->rightVisibleCol; j++){

      cell_draw(self->window, y, x, self->cells[i][j]);
      x += CELL_WIDTH;

    }

    x = 0;
    y += CELL_HEIGHT;

  }

  wrefresh(self->window);
}
