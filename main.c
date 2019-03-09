#include <stdio.h>
#include <ncurses.h>
#include "board.h"

void drawScrabble(WINDOW* win, int startY, int startX);

int main(void){

  // Starts curses mode and disables line buffering
  initscr();
  cbreak();

  // Draws the parent window
  refresh();

  getch();
  endwin();

  return 0;

}
