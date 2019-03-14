#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "tile.h"

typedef struct BOARD{

  int rows;               // # ROWS IN THE GAMEBOARD
  int cols;               // # COLS IN THE GAMEBOARD
  int x;                  // X COORDINATE OF THE TILE'S TOP RIGHT CORNER
  int y;                  // Y COORDINATE OF THE TILE'S TOP RIGHT CORNER
  int currentTile[2];     // Currently selected tile on the gameboard

  TILE* tiles[20][20];    // ARRAY OF TILES THAT MAKEUP THE GAMEBOARD

}BOARD;

BOARD* create_board(int rows, int , int y, int x);
int handle_board_events(BOARD* self, int event);
void draw_board(BOARD* self);
void erase_board(BOARD* self);
