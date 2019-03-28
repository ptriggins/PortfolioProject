#include "cell.h"

void cell_init(CELL* self, char type[3]){

  self->selected = 0;
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

  self->tempTile = NULL, self->tile = NULL;

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

void cell_draw(WINDOW* win, int y, int x, CELL* self){

  if (self->tempTile != NULL)
    tile_draw(win, y, x, self->tempTile);
  else if(self->tile != NULL)
    tile_draw(win, y, x, self->tile);
  else{

    wattron(win, A_BOLD);
    wattron(win, COLOR_PAIR(self->color));

    mvwprintw(win, y, x, "     ");
    mvwprintw(win, y + 1, x, "     ");
    mvwprintw(win, y + 2, x, "     ");

    if (self->selected == 1){
      mvwaddch(win, y, x, ACS_ULCORNER);
      mvwaddch(win, y, x + 4, ACS_URCORNER);
      mvwaddch(win, y + 2, x, ACS_LLCORNER);
      mvwaddch(win, y + 2, x + 4, ACS_LRCORNER);
    }

    mvwprintw(win, y, x, "%s", self->type);

  }

}

void cell_play_tile(CELL* self){

  self->tile = self->tempTile;
  self->tempTile = NULL;
  self->tile->selected = 0;

}
