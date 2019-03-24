#include "board.h"

// Initializes all of a board's attributes
void board_init(BOARD* self, int numRows, int numCols, int screenRows, int screenCols){

  if (numRows <= screenRows)
    self->y = ((screenRows / 2) - (numRows / 2)) * CELL_HEIGHT;
  else
    self->y = 0;

  if(numCols <= screenCols)
    self->x = ((screenCols / 2) - (numCols / 2)) * CELL_WIDTH;
  else
    self->x = 3 * CELL_WIDTH;

  self->numRows = numRows;
  self->numCols = numCols;

  // Variables relating to a cell's attributes
  int cellRow, cellCol;
  char type[3];

  // Calculates coordinates such that the loop centers around 0, 0
  int topY = -numRows / 2;
  int topX = -numCols / 2;

  // Creates each cell in the gameboard
  for(int i = topY; i < topY + numRows; i++){
    for(int j = topX; j < topX + numCols; j++){

      // Calculates the row and column a cell falls in
      cellRow = j + numRows / 2;
      cellCol = i + numCols / 2;

      // Gets a cell's type based on its distance from row 0 and column 0
      cell_get_type(type, abs(i), abs(j));

      // Creates the cell of previously determined type at a given row and column
      self->cells[cellRow][cellCol] = cell_create(type);

    }
  }

  if (numRows <= screenRows){
    self->topVisibleRow = 0;
    self->bottomVisibleRow = numRows - 1;
  }
  else{
    self->topVisibleRow = ((numRows - screenRows) / 2);
    self->bottomVisibleRow = (numRows - self->topVisibleRow) - 1;
  }

  if (numCols <= screenCols){
    self->leftVisibleCol = 0;
    self->rightVisibleCol = numCols - 1;
  }
  else{
    self->leftVisibleCol = ((numCols - screenCols) / 2);
    self->rightVisibleCol = (numCols - self->leftVisibleCol) - 1;
  }

  self->window = newwin(screenRows * CELL_HEIGHT, screenCols * CELL_WIDTH, self->y, self->x);

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

  // Defines background a foreground combinations for each cell type in the board
  init_pair(1, COLOR_WHITE, COLOR_YELLOW);
  init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(3, COLOR_WHITE, COLOR_CYAN);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);
  init_pair(5, COLOR_WHITE, COLOR_RED);

  int y = 0, x = 0;

  for (int i = self->topVisibleRow; i <= self->bottomVisibleRow; i++){
    for (int j = self->leftVisibleCol; j <= self->rightVisibleCol; j++){

      wattron(self->window, A_BOLD);
      wattron(self->window, COLOR_PAIR(self->cells[i][j]->color));

      mvwprintw(self->window, y, x, "     ");
      mvwprintw(self->window, y + 1, x, "     ");
      mvwprintw(self->window, y + 2, x, "     ");

      if (self->cells[i][j]->selected == 1){
        mvwaddch(self->window, y, x, ACS_ULCORNER);
        mvwaddch(self->window, y, x + 4, ACS_URCORNER);
        mvwaddch(self->window, y + 2, x, ACS_LLCORNER);
        mvwaddch(self->window, y + 2, x + 4, ACS_LRCORNER);
      }

      mvwprintw(self->window, y, x, "%s", self->cells[i][j]->type);
      x += CELL_WIDTH;

    }

    x = 0;
    y += CELL_HEIGHT;

  }

  wrefresh(self->window);

}
