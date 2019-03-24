#include <stdio.h>
#include <ncurses.h>
#include "board.h"

#define MARGIN_WIDTH 3

int main(int argc, char* argv[]){

  // Initializes drawing with ncurses
  initscr();
  start_color();
  //noecho();

  // Enables getting input from the keyboard
  keypad(stdscr, TRUE);
  cbreak();
  //nodelay(stdscr, TRUE);

  refresh();

  // Gets the number of rows and cols of the gameboard and calculates coordinates such that the gameboard is center
  int numRows = atoi(argv[1]);
  int numCols = atoi(argv[2]);

  int screenRows = LINES / CELL_HEIGHT;
  int screenCols = COLS / CELL_WIDTH;

  BOARD* gameboard = board_create(numRows, numCols, screenRows, screenCols - 2 * MARGIN_WIDTH);
  int currentRow = numRows / 2;
  int currentCol = numCols / 2;

  board_draw(gameboard);

  while (1){

    int ch = getch();
    int currentCenterRow = gameboard->topVisibleRow + (screenRows / 2);
    int currentCenterCol = gameboard->leftVisibleCol + ((screenCols / 2) - MARGIN_WIDTH);

    if (ch == KEY_UP && currentRow > 0){

      if (gameboard->topVisibleRow > 0 && currentRow == currentCenterRow){
        gameboard->topVisibleRow--;
        gameboard->bottomVisibleRow--;
      }

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentRow--;

    }
    if (ch == KEY_DOWN && currentRow < numRows - 1){

      if (gameboard->bottomVisibleRow < numRows - 1 && currentRow == currentCenterRow){
        gameboard->topVisibleRow++;
        gameboard->bottomVisibleRow++;
      }

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentRow++;

    }
    if (ch == KEY_LEFT && currentCol > 0){

      if (gameboard->leftVisibleCol > 0 && currentCol == currentCenterCol){
        gameboard->leftVisibleCol--;
        gameboard->rightVisibleCol--;
      }

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentCol--;

    }
    if (ch == KEY_RIGHT && currentCol < numCols - 1){

      if (gameboard->rightVisibleCol < numCols - 1 && currentCol == currentCenterCol){
        gameboard->leftVisibleCol++;
        gameboard->rightVisibleCol++;
      }

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentCol++;

    }
    gameboard->cells[currentRow][currentCol]->selected = 1;

    board_draw(gameboard);

  }

  endwin();

}
