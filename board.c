#include "board.h"


// Initializes a board of a customizable size
void board_init(BOARD* self, int numRows, int numCols, int availableRows, int availableCols){

  // Determines the top left coordinates of where the board will be drawn on the screen
  if (numRows <= availableRows)
    self->startRow = ((availableRows / 2) - (numRows / 2));
  else
    self->startRow = 0;

  if(numCols <= availableCols)
    self->startCol = ((availableCols / 2) - (numCols / 2) + MARGIN_WIDTH);
  else
    self->startCol = MARGIN_WIDTH;

  self->numRows = numRows;
  self->numCols = numCols;

  int cellRow, cellCol;
  char type[3];

  int topY = -numRows / 2;
  int topX = -numCols / 2;

  // Initializes each cell based on its coordinates
  for(int i = topY; i < topY + numRows; i++){
    for(int j = topX; j < topX + numCols; j++){

      cellRow = i + numRows / 2;
      cellCol = j + numCols / 2;

      cell_get_type(type, abs(i), abs(j));

      self->cells[cellRow][cellCol] = cell_create(type);

    }
  }


  // Sets adjacent tiles for each tile in the graph
  CELL* dummy = cell_create("DM");
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {

      if (i != 0)
        self->cells[i][j]->above = self->cells[i - 1][j];
      else
        self->cells[i][j]->above = dummy;

      if (i != numRows - 1)
        self->cells[i][j]->below = self->cells[i + 1][j];
      else
        self->cells[i][j]->below = dummy;

      if (j != 0)
        self->cells[i][j]->left = self->cells[i][j - 1];
      else
        self->cells[i][j]->left = dummy;

      if (j != numCols - 1)
        self->cells[i][j]->right = self->cells[i][j + 1];
      else
        self->cells[i][j]->right = dummy;

    }
  }

  // Creates the portion of the gameboard that is viewable at a given time and the window that it will be drawn to
  self->viewframe = frame_create(numRows, numCols, availableRows, availableCols);
  self->window = newwin(availableRows * CELL_HEIGHT, availableCols * CELL_WIDTH, self->startRow * CELL_HEIGHT, self->startCol * CELL_WIDTH);

}


// Allocates memory for a board of a given size
BOARD* board_create(int numRows, int numCols, int availableRows, int availableCols){

  BOARD* newBoard = (BOARD*) malloc(sizeof(BOARD));

  // ALlocates memory for the board's array of cells
  newBoard->cells = (CELL***) malloc(numRows * sizeof(CELL**));
  for (int i = 0; i < numRows; i++){
    newBoard->cells[i] = (CELL**) malloc(numCols * sizeof(CELL*));
  }

  board_init(newBoard, numRows, numCols, availableRows, availableCols);
  return newBoard;

}


// Draws the gameboard to the screen
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

// Switches which cell the cursor is currently over
void board_switch_cells(CELL* currentCell, CELL* nextCell){

  cell_switch_selection(currentCell, nextCell);
  if (currentCell->temp != NULL)
    cell_switch_tile(currentCell, nextCell);

}
