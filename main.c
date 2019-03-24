#include <stdio.h>
#include <ncurses.h>
#include "board.h"

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

  BOARD* gameboard = board_create(numRows, numCols, LINES / CELL_HEIGHT, COLS / CELL_WIDTH);

  int ch = getch()
  while (1){

    if (ch == KEY_UP){

    }
    else if (ch == KEY_DOWN){

    }
    else if (ch == KEY_LEFT){

    }
    else if (ch == KEY_RIGHT){

    }

  }

  board_draw(gameboard);

  endwin();


}
