#include <stdio.h>
#include <ncurses.h>
#include "tile.h"

int main(void){

  // Declares a window and size for the gameBoard
  tile* testTile;
  testTile = createTile(3, 5, 2, 2);

  // Starts curses mode and disables line buffering
  initscr();
  cbreak();
  refresh();

  testTile->window = drawTile(testTile);

  getch();
  endwin();

  return 0;

}
