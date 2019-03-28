#include "bag.h"

void bag_init(TILEBAG* self){

  self->numTiles = TILES_PER_BAG;

  for (int i = 0; i < self->numTiles; i++){

    if (i < 9)
      self->tiles[i] = tile_create('A');
    else if (i < 11)
      self->tiles[i] = tile_create('B');
    else if (i < 13)
      self->tiles[i] = tile_create('C');
    else if (i < 17)
      self->tiles[i] = tile_create('D');
    else if (i < 29)
      self->tiles[i] = tile_create('E');
    else if (i < 31)
      self->tiles[i] = tile_create('F');
    else if (i < 34)
      self->tiles[i] = tile_create('G');
    else if (i < 36)
      self->tiles[i] = tile_create('H');
    else if (i < 45)
      self->tiles[i] = tile_create('I');
    else if (i < 46)
      self->tiles[i] = tile_create('J');
    else if (i < 47)
      self->tiles[i] = tile_create('K');
    else if (i < 51)
      self->tiles[i] = tile_create('L');
    else if (i < 53)
      self->tiles[i] = tile_create('M');
    else if (i < 59)
      self->tiles[i] = tile_create('N');
    else if (i < 67)
      self->tiles[i] = tile_create('O');
    else if (i < 69)
      self->tiles[i] = tile_create('P');
    else if (i < 70)
      self->tiles[i] = tile_create('Q');
    else if (i < 76)
      self->tiles[i] = tile_create('R');
    else if (i < 80)
      self->tiles[i] = tile_create('S');
    else if (i < 86)
      self->tiles[i] = tile_create('T');
    else if (i < 90)
      self->tiles[i] = tile_create('U');
    else if (i < 92)
      self->tiles[i] = tile_create('V');
    else if (i < 94)
      self->tiles[i] = tile_create('W');
    else if (i < 95)
      self->tiles[i] = tile_create('X');
    else if (i < 97)
      self->tiles[i] = tile_create('Y');
    else if (i < 98)
      self->tiles[i] = tile_create('Z');

  }

}

TILEBAG* bag_create(){

  TILEBAG* newBag = (TILEBAG*) malloc(sizeof(TILEBAG));
  bag_init(newBag);
  return newBag;

}

TILE* bag_draw_tile(TILEBAG* self){

  srand(time(0));
  int tileIndex = rand() % self->numTiles;
  TILE* chosenTile = self->tiles[tileIndex];

  for (int i = tileIndex; i < self->numTiles - 1; i++){
    self->tiles[i] = self->tiles[i + 1];
  }
  self->numTiles--;

  return chosenTile;

}
