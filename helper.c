#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "word.h"

int check_valid_tile_placement(WORD* word, CELL* current){

  CELL* cell = word->head;
  current->tile = current->temp;

  if (word->head == NULL){
    word->head = current;
    current->temp = NULL;
    return 1;
  }
  else if (word->direction == NONE){

    while (cell->tile != NULL){
      if (cell == current){
        word->head = cell;
        word->direction = VERTICAL;
        current->temp = NULL;
        return 1;
      }
      cell = cell->above;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        word->direction = VERTICAL;
        current->temp = NULL;
        return 1;
      }
      cell = cell->below;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        word->head = cell;
        word->direction = HORIZONTAL;
        current->temp = NULL;
        return 1;
      }
      cell = cell->left;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        word->direction = HORIZONTAL;
        current->temp = NULL;
        return 1;
      }
      cell = cell->right;
    }

  }
  else if (word->direction == VERTICAL){

    while (cell->tile != NULL){
      if (cell == current){
        word->head = cell;
        current->temp = NULL;
        return 1;
      }
      cell = cell->above;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        current->temp = NULL;
        return 1;
      }
      cell = cell->below;
    }


  }
  else if (word->direction == HORIZONTAL){

    while (cell->tile != NULL){
      if (cell == current){
        word->head = cell;
        current->temp = NULL;
        return 1;
      }
      cell = cell->left;
    }

    cell = word->head;
    while (cell->tile != NULL){
      if (cell == current){
        current->temp = NULL;
        return 1;
      }
      cell = cell->right;
    }

  }
  current->tile = NULL;
  return 0;

}
