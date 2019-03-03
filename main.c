#include <stdio.h>
#include <ncurses.h>
#include "tile.h"

void drawScrabble(WINDOW* win, int startY, int startX);

int main(void){

  // Starts curses mode and disables line buffering
  initscr();
  cbreak();
  // Draws the parent window
  refresh();

  // Starts curses mode and disables line buffering
  initscr();
  cbreak();

  WINDOW* win = newwin(100, 100, 3, 3);
  drawScrabble(win, 0, 0);

  // Draws the parent window
  refresh();

  getch();
  endwin();

  return 0;

}

// Draws a grid to be used as the scrabble board
void drawScrabble(WINDOW* win, int startY, int startX){

  for(int i = 0; i < 46; i++){
    for(int j = 0; j < 76; j++){

      // Draws the top edge of the grid
      if(i == 0){

        if(j == 0)
          mvwaddch(win, startY, startX, ACS_ULCORNER);
        else if(j == 75)
          mvwaddch(win, startY, startX + j, ACS_URCORNER);
        else if(j % 5 == 0)
          mvwaddch(win, startY, startX + j, ACS_TTEE);
        else
          mvwaddch(win, startY, startX + j, ACS_HLINE);

      }
      // Draws the bottom edge of the grid
      else if(i == 45){

        if(j == 0)
          mvwaddch(win, startY + i, startX, ACS_LLCORNER);
        else if(j == 75)
          mvwaddch(win, startY + i, startX + j, ACS_LRCORNER);
        else if(j % 5 == 0)
          mvwaddch(win, startY + i, startX + j, ACS_BTEE);
        else
          mvwaddch(win, startY + i, startX + j, ACS_HLINE);

      }
      // Draws intermediate rows of grid
      else if(i % 3 == 0){

        if(j == 0)
          mvwaddch(win, startY + i, startX, ACS_LTEE);
        else if(j == 75)
          mvwaddch(win, startY + i, startX + j, ACS_RTEE);
        else if(j % 5 == 0)
          mvwaddch(win, startY + i, startX + j, ACS_PLUS);
        else
          mvwaddch(win, startY + i, startX + j, ACS_HLINE);

      }
      // Draws connecting vertical lines
      else if( j % 5 == 0)
          mvwaddch(win, startY + i, startX + j, ACS_VLINE);

    }
  }
  wrefresh(win);

}
