#include "board.h"

// Initializes all of a board's attributes
void board_init(BOARD* self, int numRows, int numCols, int availableRows, int availableCols){

  if (numRows <= availableRows)
    self->startRow = ((availableRows / 2) - (numRows / 2));
  else
    self->startRow = 0;

  if(numCols <= availableCols)
    self->startCol = ((availableCols / 2) - (numCols / 2));
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

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {

      if (i != 0)
        self->cells[i][j]->aboveCell = self->cells[i - 1][j];
      if (i != numRows - 1)
        self->cells[i][j]->belowCell = self->cells[i + 1][j];
      if (j != 0)
        self->cells[i][j]->leftCell = self->cells[i][j - 1];
      if (j != numCols - 1)
        self->cells[i][j]->rightCell = self->cells[i][j + 1];

    }
  }

  self->viewframe = frame_create(numRows, numCols, availableRows, availableCols);
  self->window = newwin(availableRows * CELL_HEIGHT, availableCols * CELL_WIDTH, self->startRow * CELL_HEIGHT, self->startCol * CELL_WIDTH);

}

// Allocates memory for a board with variable rows and columns
BOARD* board_create(int numRows, int numCols, int availableRows, int availableCols){

  BOARD* newBoard = (BOARD*) malloc(sizeof(BOARD));

  // Allocates memory for a two dimensional array of cell pointers
  newBoard->cells = (CELL***) malloc(numRows * sizeof(CELL**));
  for (int i = 0; i < numRows; i++){
    newBoard->cells[i] = (CELL**) malloc(numCols * sizeof(CELL*));
  }

  board_init(newBoard, numRows, numCols, availableRows, availableCols);
  return newBoard;

}

void board_draw(BOARD* self){

  int y = 0, x = 0;

  for (int i = self->viewframe->topRow; i <= self->viewframe->bottomRow; i++){
    for (int j = self->viewframe->leftCol; j <= self->viewframe->rightCol; j++){

      cell_draw(self->window, y, x, self->cells[i][j]);
      x += CELL_WIDTH;

    }

    x = 0;
    y += CELL_HEIGHT;

  }

  wrefresh(self->window);
}
