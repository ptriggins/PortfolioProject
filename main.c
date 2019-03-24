#include <stdio.h>
#include <ncurses.h>
#include "board.h"

#define GAMEBOARD 0

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

  BOARD* gameboard = board_create(numRows, numCols, screenRows, screenCols - 6);
  int currentRow = numRows / 2;
  int currentCol = numCols / 2;

  board_draw(gameboard);

  int ch = getch();

  while (1){

    if (ch == KEY_UP && currentRow > 0){

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentRow--;

      if (gameboard->topVisibleRow > 0){
        gameboard->topVisibleRow--;
        gameboard->bottomVisibleRow--;
      }

    }
    if (ch == KEY_DOWN && currentRow < numRows - 1){

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentRow++;

      if (gameboard->bottomVisibleRow < numRows - 1){
        gameboard->topVisibleRow++;
        gameboard->bottomVisibleRow++;
      }

    }
    if (ch == KEY_LEFT && currentCol > 0){

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentCol--;

      if (gameboard->leftVisibleCol > 0){
        gameboard->leftVisibleCol--;
        gameboard->rightVisibleCol--;
      }

    }
    if (ch == KEY_RIGHT && currentCol < numCols - 1){

      gameboard->cells[currentRow][currentCol]->selected = 0;
      currentCol++;

      if (gameboard->rightVisibleCol < numCols - 1){
        gameboard->leftVisibleCol++;
        gameboard->rightVisibleCol++;
      }

    }
    gameboard->cells[currentRow][currentCol]->selected = 1;
    board_draw(gameboard);
    ch = getch();

  }

  endwin();

}
