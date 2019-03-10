#include <stdio.h>
#include <ncurses.h>
#include "board.h"

void drawScrabble(WINDOW* win, int startY, int startX);

int main(void){

  // INITIALIZES NCURSES
  initscr();
  keypad(stdscr, TRUE);
  clear();
  //noecho();
  cbreak();
  start_color();

  // DECLARES A GAMEBOARD OF GIVEN SIZE
  BOARD* gameBoard = createBoard(15, 15);

  // DRAWS THE PARENT SCREEN
  refresh();

  // DRAWS THE GAMEBOARD ON TOP OF THE PARENT SCREEN
  drawBoard(gameBoard);

  // HANDLES USER INPUT
  while(1){

    // GETS A KEYPRESS FROM THE USER
    int ch = getch();

    // ENDS THE PROGRAM IF THE USER PRESSES F1
    if(ch == 265)
      break;

  }
  endwin();

  return 0;

}
