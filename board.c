#include "board.h"

// Initializes a board object with given attributes
void init_board(BOARD* self, int rows, int cols, int y, int x) {

  self->rows = rows;
  self->cols = cols;
  self->y = y;
  self->x = x;
  self->currentTile[0] = rows / 2 + 1;
  self->currentTile[1] = rows / 2 + 1;

  int topY = -rows / 2, topX = -cols / 2;     // Sets loop variables relative to start tile

  // Formulically initiallizes each tile
  for(int i = topY; i < topY + rows; i++){
    for(int j = topX; j < topX + cols; j++){

      // Calculates the actual coordinates of the tile on the board
      int t_x = i + rows / 2, t_y = j + rows / 2;

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

// ALLOCATES MEMORY FOR A BOARD OF A GIVEN SIZE
BOARD* create_board(int rows, int cols, int y, int x) {

  BOARD* newBoard = (BOARD*) malloc(sizeof(BOARD));
  init_board(newBoard, rows, cols, y, x);
  return newBoard;

}

void switch_tile(BOARD* self, int newTile[2]) {

  self->tiles[self->currentTile[0]][self->currentTile[1]]->highlighted = 0;
  self->tiles[newTile[0]][newTile[1]]->highlighted = 0;
  self->currentTile[0] = newTile[0];
  self->currentTile[1] = newTile[1];

}

int handle_board_events(BOARD* self, int event) {

  if(event == 265)
    return 3;
  else if(event == 27) {
    erase_board(self);
    return 2;
  }

  int newTile[2] = {self->currentTile[0], self->currentTile[1]};

  if(event == KEY_UP && self->currentTile[1] > 0) {
    newTile[1]--;
    switch_tile(self, newTile);
  }

  else if(event == KEY_DOWN && self->currentTile[1] < self->rows) {
    newTile[1]++;
    switch_tile(self, newTile);
  }

  else if(event == KEY_LEFT && self->currentTile[0] > 0) {
    newTile[0]++;
    switch_tile(self, newTile);
  }

  else if(event == KEY_RIGHT && self->currentTile[1] < self->cols) {
    newTile[0]--;
    switch_tile(self, newTile);
  }

  draw_board(self);
  return 1;

}

void draw_board(BOARD* self){

  for(int i = 0; i < self->rows; i++){
    for(int j = 0; j < self->cols; j++){
      draw_tile(self->tiles[i][j]);
    }
  }

}

void erase_board(BOARD* self){

  for(int i = 0; i < self->rows; i++){
    for(int j = 0; j < self->cols; j++){
      werase(self->tiles[i][j]->win);
      wrefresh(self->tiles[i][j]->win);
    }
  }

}
