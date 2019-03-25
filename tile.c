#include "tile.h"

void tile_init(TILE* self, char letter){

  self->letter = letter;
  if (letter == 'A')
    self->letterValue = 1;
  else if (letter == 'B')
    self->letterValue = 3;
  else if (letter == 'C')
    self->letterValue = 3;
  else if (letter == 'D')
    self->letterValue = 2;
  else if (letter == 'E')
    self->letterValue = 1;
  else if (letter == 'F')
    self->letterValue = 4;
  else if (letter == 'G')
    self->letterValue = 2;
  else if (letter == 'H')
    self->letterValue = 4;
  else if (letter == 'I')
    self->letterValue = 1;
  else if (letter == 'J')
    self->letterValue = 8;
  else if (letter == 'K')
    self->letterValue = 5;
  else if (letter == 'L')
    self->letterValue = 1;
  else if (letter == 'M')
    self->letterValue = 1;
  else if (letter == 'N')
    self->letterValue = 1;
  else if (letter == 'O')
    self->letterValue = 1;
  else if (letter == 'P')
    self->letterValue = 3;
  else if (letter == 'Q')
    self->letterValue = 10;
  else if (letter == 'R')
    self->letterValue = 1;
  else if (letter == 'S')
    self->letterValue = 1;
  else if (letter == 'T')
    self->letterValue = 1;
  else if (letter == 'U')
    self->letterValue = 1;
  else if (letter == 'V')
    self->letterValue = 4;
  else if (letter == 'W')
    self->letterValue = 4;
  else if (letter == 'X')
    self->letterValue = 8;
  else if (letter == 'Y')
    self->letterValue = 4;
  else if (letter == 'Z')
    self->letterValue = 10;
  else if (letter == '_')
    self->letterValue = 0;

  self->selected = 0;
  self->chosen = 0;
  self->played = 0;

}

TILE* tile_create(char letter){

  TILE* newTile = (TILE*) malloc(sizeof(TILE));
  tile_init(newTile, letter);
  return newTile;

}
