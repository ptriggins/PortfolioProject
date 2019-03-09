#include "board.h"

///////////////////////////////////////////////////////////////////////////////

// Sets the board size and initializes its tiles
void initBoard(BOARD* self, int rows, int cols){

  self->rows = rows;
  self->cols = cols;

  int topY = -rows / 2;
  int topX = -cols / 2;

  // Initializes each tile on the scrabble board
  for(int i = topY; i < topY + rows; i++){
    for(int j = topX; j < topX + cols; j++){

      // Calculates the actual coordinates of the tile on the board
      int x = i + rows / 2;
      int y = j + rows / 2;

      // Initializes the starting tile
      if(i == 0 && j == 0)
        self->tiles[x][y] = createTile("ST", y * 3, x * 3);
      // Initializes triple word tiles
      else if(i % 7 == 0 && j % 7 == 0)
        self->tiles[x][y] = createTile("TW", y * 3, x * 3);
      // Initializes double word tiles
      else if(abs(i) > 2 && abs(j) > 2 && abs(i) == abs(j))
        self->tiles[x][y] = createTile("DW", y * 3, x * 3);
      // Initializes tripple letter tiles
      else if(abs(i) % 4 == 2 && abs(j) % 4 == 2)
        self->tiles[x][y] = createTile("TL", y * 3, x * 3);
      // Initializes double letter tiles
      else if((abs(i) % 7 == 0 && abs(j) % 4 == 0) || (abs(i) % 4 == 0 && abs(j) % 7 == 0))
        self->tiles[x][y] = createTile("DL", y * 3, x * 3);
      else if((abs(i) == 1 && abs(j) % 4 == 1) || (abs(j) == 1 && abs(i) % 4 == 1))
        self->tiles[x][y] = createTile("DL", y * 3, x * 3);
      else
        self->tiles[x][y] = createTile("  ", y * 3, x * 3);

    }
  }

}

///////////////////////////////////////////////////////////////////////////////

// Allocates memory for a game board of a given size
BOARD* createBoard(int rows, int cols){

  BOARD* newBoard = (BOARD*) malloc(sizeof(BOARD));
  initBoard(newBoard, rows, cols);
  return newBoard;

}

///////////////////////////////////////////////////////////////////////////////

void drawBoard(BOARD* self){

  for(int i = 0; i < self->rows; i++){
    for(int j = 0; j < self->cols; j++){
      drawTile(self->tiles[i][j]);
    }
  }
  //drawTile(self->tiles[8][8]);

}
