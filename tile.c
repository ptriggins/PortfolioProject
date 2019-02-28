#include "tile.h"

// Tile "constructor"
void initTile(tile* self, int height, int width, int topY, int topX){
  self->height = height, self->width = width;
  self->topY = topY, self->topX = topX;
  self->window = newwin(self->height, self->width, self->topY, self->topX);
}

// Allocates memory for a tile & calls tile constructor, returns resulting tile
tile* createTile(int height, int width, int topY, int topX){
  tile* newTile = (tile*) malloc(sizeof(tile));
  initTile(newTile, height, width, topY, topX);
  return newTile;
}

// Creates a window for the tile and draws it
WINDOW* drawTile(tile* self){

  WINDOW* win;
  win = newwin(self->height, self->width, self->topY, self->topX);
  box(win, 0, 0);
  wrefresh(win);
  return win;

}
