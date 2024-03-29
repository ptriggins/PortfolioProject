#include "cell.h"


// Gives a cell predefined attributes based on a given type
void cell_init(CELL* self, char type[3]){

  self->selected = 0, self->played = 0;
  strcpy(self->type, type);

  if (strcmp(type, "") == 0){
    self->letterScore = 1;
    self->wordScore = 1;
    self->color = YELLOW;
  }
  else if (strcmp(type, "ST") == 0){
    self->letterScore = 1;
    self->wordScore = 2;
    self->color = MAGENTA;
    self->selected = 1;
  }
  else if (strcmp(type, "DL") == 0){
    self->letterScore = 2;
    self->wordScore = 1;
    self->color = CYAN;
  }
  else if (strcmp(type, "TL") == 0){
    self->letterScore = 3;
    self->wordScore = 1;
    self->color = BLUE;
  }
  else if (strcmp(type, "DW") == 0){
    self->letterScore = 1;
    self->wordScore = 2;
    self->color = MAGENTA;
  }
  else if (strcmp(type, "TW") == 0){
    self->letterScore = 1;
    self->wordScore = 3;
    self->color = RED;
  }
  else if (strcmp(type, "DM") == 0){
    self->letterScore = 0;
    self->wordScore = 0;
    self->color = 8;
  }

  self->temp = NULL, self->tile = NULL;
  self->above = NULL, self->below = NULL, self->left = NULL, self->right = NULL;

}

// Allocates memory for a given cell
CELL* cell_create(char type[3]){

  CELL* newCell = (CELL*) malloc(sizeof(CELL));
  cell_init(newCell, type);
  return newCell;

}

// Determines a cell's type based on distance from the start cell
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


// Draws a cell to the screen
void cell_draw(WINDOW* win, int y, int x, CELL* self){

  if (self->tile != NULL)
    self->tile->selected = self->selected;

  if (self->temp != NULL)
    tile_draw(win, y, x, self->temp);
  else if(self->tile != NULL)
    tile_draw(win, y, x, self->tile);
  else{

    wattron(win, A_BOLD);
    wattron(win, COLOR_PAIR(self->color));

    draw_background(win, y, x);
    if (self->selected == 1){
      draw_cursor(win, y, x);
    }
    mvwprintw(win, y, x, "%s", self->type);

  }

}

void cell_place_tile(CELL* self){
  self->tile = self->temp;
  self->temp = NULL;
}

void cell_play_tile(CELL* self){
  self->tile->chosen = 0;
  self->played = 1;
}

void cell_switch_selection(CELL* oldCell, CELL* newCell){
  oldCell->selected = 0;
  newCell->selected = 1;
}

void cell_switch_tile(CELL* oldCell, CELL* newCell){
  newCell->temp = oldCell->temp;
  oldCell->temp = NULL;
}

void cell_clear_tile(CELL* self, TILE* tile){

  if(tile != NULL){
    if (tile == self->temp){
      tile_deselect(self->temp);
      self->temp = NULL;
    }
    else if (tile == self->tile && tile){
      tile_deselect(self->tile);
      self->tile = NULL;
    }
  }
  self->selected = 0;

}
