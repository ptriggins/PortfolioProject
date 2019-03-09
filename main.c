#include <stdio.h>
#include <ncurses.h>
#include "board.h"

void drawScrabble(WINDOW* win, int startY, int startX);

int main(void){

  // Starts curses mode and disables line buffering
  initscr();
  cbreak();

  refresh();

  BOARD* gameBoard = createBoard(15, 15);
  drawBoard(gameBoard);

  // Draws the parent window
  refresh();

  getch();
  endwin();

  return 0;

}
