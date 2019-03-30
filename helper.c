#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "word.h"

int check_valid_tile_placement(WORD* word, CELL* current){

  CELL* cell = word->head;
  if (word->head == NULL){
    word->head = current;
    cell_place_tile(current);
    return 1;
  }
  else if (word->direction == NONE){

    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        word->head = cell;
        word->direction = VERTICAL;
        return 1;
      }
      cell = cell->above;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        word->direction = VERTICAL;
        return 1;
      }
      cell = cell->below;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        word->head = cell;
        word->direction = HORIZONTAL;
        return 1;
      }
      cell = cell->left;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        word->direction = HORIZONTAL;
        return 1;
      }
      cell = cell->right;
    }

  }
  else if (word->direction == VERTICAL){

    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        word->head = cell;
        return 1;
      }
      cell = cell->above;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        return 1;
      }
      cell = cell->below;
    }


  }
  else if (word->direction == HORIZONTAL){

    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        word->head = cell;
        return 1;
      }
      cell = cell->left;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        cell_place_tile(current);
        return 1;
      }
      cell = cell->right;
    }

  }
  return 0;

}
