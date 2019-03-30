#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#ifndef TILE_H
#define TILE_H

#define TILE_HEIGHT 3
#define TILE_WIDTH 5

typedef struct TILE{

  char letter;
  int score, location, selected, chosen;

}TILE;

TILE* tile_create(char letter, int score);
void tile_draw(WINDOW* win, int y, int x, TILE* self);
void tile_return_to_hand(TILE* self);
void tile_set(TILE* self);
void draw_background(WINDOW* win, int y, int x);
void draw_cursor(WINDOW* win, int y, int x);

#endif
