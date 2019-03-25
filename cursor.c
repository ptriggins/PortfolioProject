#include "cursor.h"

void cursor_init(CURSOR* self, int screenRows, int screenCols){

  self->row = screenRows / 2;
  self->col = screenCols / 2;
  self->location = 0;

}

CURSOR* cursor_create(int screenRows, int screenCols, int location){

  CURSOR* newCursor = (CURSOR*) malloc(sizeof(CURSOR));
  cursor_init(newCursor, screenRows, screenCols);
  return newCursor;

}
