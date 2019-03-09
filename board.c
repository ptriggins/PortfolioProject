#include "board.h"

///////////////////////////////////////////////////////////////////////////////

// Sets the board size and initializes its tiles
void initBoard(int size){

  self->size = size;

  // Calculates the midpoint of the scrabble board
  int mid =  (size / 2) + 1

  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){

      // Initializes the starting tile
      if(i == mid  && j == mid)
        self->tiles[i][j] = createTile("ST", j, i);

      // Initializes tripple letter tiles
      if()

    }
  }


}

///////////////////////////////////////////////////////////////////////////////

// Allocates memory for a game board of a given size
BOARD* createBoard(BOARD* self, FILE* initFile){

  BOARD* newBoard = (BOARD*) malloc(sizeof(BOARD));

}

///////////////////////////////////////////////////////////////////////////////

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
