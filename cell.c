#include "cell.h"

// Initializes a cells attributes based on a given type
void cell_init(CELL* self, char type[3]){

  self->selected = 0;
  self->occupied = 0;

  strcpy(self->type, type);

  if (strcmp(type, "") == 0){
    self->letterMultiplier = 0;
    self->wordMultiplier = 0;
    self->color = YELLOW;
  }
  else if (strcmp(type, "ST") == 0){
    self->letterMultiplier = 0;
    self->wordMultiplier = 2;
    self->color = MAGENTA;
    self->selected = 1;
  }
  else if (strcmp(type, "DL") == 0){
    self->letterMultiplier = 2;
    self->wordMultiplier = 0;
    self->color = CYAN;
  }
  else if (strcmp(type, "TL") == 0){
    self->letterMultiplier = 3;
    self->wordMultiplier = 0;
    self->color = BLUE;
  }
  else if (strcmp(type, "DW") == 0){
    self->letterMultiplier = 0;
    self->wordMultiplier = 2;
    self->color = MAGENTA;
  }
  else if (strcmp(type, "TW") == 0){
    self->letterMultiplier = 0;
    self->wordMultiplier = 3;
    self->color = RED;
  }

}

CELL* cell_create(char type[3]){

  CELL* newCell = (CELL*) malloc(sizeof(CELL));
  cell_init(newCell, type);

  return newCell;

}

// Determines the type of a cell bsaed on a given x and y distance from the start cell
void cell_get_type(char type[3], int yDistance, int xDistance){

  if (yDistance == 0 && xDistance == 0)
    strcpy(type, "ST");
  else if (yDistance % 7 == 0 && xDistance % 7 == 0)
    strcpy(type, "TW");
  else if (yDistance > 2 && xDistance > 2 && yDistance == xDistance)
    strcpy(type, "DW");
  else if (yDistance % 4 == 2 && xDistance % 4 == 2)
    strcpy(type, "TL");
  else if ((yDistance % 7 == 0 && xDistance % 4 == 0) || (yDistance % 4 == 0 && xDistance % 7 == 0))
    strcpy(type, "DL");
  else if ((yDistance == 1 && xDistance % 4 == 1) || (xDistance == 1 && yDistance % 4 == 1))
    strcpy(type, "DL");
  else
    strcpy(type, "");

}
