#include "board.h"

///////////////////////////////////////////////////////////////////////////////

// SETS BOARD SIZE AND INITIALIZES ITS TILES
void init_board(BOARD* self, int rows, int cols, int y, int x){

  self->rows = rows;
  self->cols = cols;
  self->y = y;
  self->x = x;

  // SETS LOOP VARIABLES RELATIVE TO THE START TILE
  int topY = -rows / 2;
  int topX = -cols / 2;

  // INITIALIZES EACH TILE ON THE SCRABBLE BOARD
  for(int i = topY; i < topY + rows; i++){
    for(int j = topX; j < topX + cols; j++){

      // Calculates the actual coordinates of the tile on the board
      int t_x = i + rows / 2;
      int t_y = j + rows / 2;

      // Initializes the starting tile
      if(i == 0 && j == 0)
        self->tiles[t_x][t_y] = create_tile("ST", y + t_y * TILE_H, x +t_x * TILE_W);
      // Initializes triple word tiles
      else if(i % 7 == 0 && j % 7 == 0)
        self->tiles[t_x][t_y] = create_tile("TW", y + t_y * TILE_H, x + t_x * TILE_W);
      // Initializes double word tiles
      else if(abs(i) > 2 && abs(j) > 2 && abs(i) == abs(j))
        self->tiles[t_x][t_y] = create_tile("DW", y + t_y * TILE_H, x + t_x * TILE_W);
      // Initializes tripple letter tiles
      else if(abs(i) % 4 == 2 && abs(j) % 4 == 2)
        self->tiles[t_x][t_y] = create_tile("TL", y + t_y * TILE_H, x + t_x * TILE_W);
      // Initializes double letter tiles
      else if((abs(i) % 7 == 0 && abs(j) % 4 == 0) || (abs(i) % 4 == 0 && abs(j) % 7 == 0))
        self->tiles[t_x][t_y] = create_tile("DL", y + t_y * TILE_H, x + t_x * TILE_W);
      else if((abs(i) == 1 && abs(j) % 4 == 1) || (abs(j) == 1 && abs(i) % 4 == 1))
        self->tiles[t_x][t_y] = create_tile("DL", y+  t_y * TILE_H, x + t_x * TILE_W);
      else
        self->tiles[t_x][t_y] = create_tile("  ", y + t_y * TILE_H, x + t_x * TILE_W);

    }
  }

}

/////////////////////////////////////////////////////////////////////////////

// ALLOCATES MEMORY FOR A BOARD OF A GIVEN SIZE
BOARD* create_board(int rows, int cols, int y, int x){

  BOARD* newBoard = (BOARD*) malloc(sizeof(BOARD));
  init_board(newBoard, rows, cols, y, x);
  return newBoard;

}

/////////////////////////////////////////////////////////////////////////////

// DRAWS ALL THE TILES IN A BOARD
void draw_board(BOARD* self){

  for(int i = 0; i < self->rows; i++){
    for(int j = 0; j < self->cols; j++){
      draw_tile(self->tiles[i][j]);
    }
  }

}
