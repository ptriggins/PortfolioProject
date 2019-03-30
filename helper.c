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

    cell = word->head->above;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->head = cell;
          word->direction = VERTICAL;
          current->temp = NULL;
          return 1;
        }
        else
          cell = cell->above;

      }
      else
        break;
    }
    cell = word->head->below;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->direction = VERTICAL;
          current->temp = NULL;
          return 1;
        }
        else{
          cell = cell->below;
        }

      }
      else
        break;
    }
    cell = word->head->left;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->head = cell;
          word->direction = HORIZONTAL;
          current->temp = NULL;
          return 1;
        }
        else
          cell = cell->left;

      }
      else
        break;
    }
    cell = word->head->right;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->direction = HORIZONTAL;
          current->temp = NULL;
          return 1;
        }
        else
          cell = cell->right;

      }
      else
        break;
    }

  }
  else if (word->direction == VERTICAL){

    cell = word->head->above;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->head = cell;
          current->temp = NULL;
          return 1;
        }
        else
          cell = cell->above;

      }
      else
        break;
    }
    cell = word->head->below;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          current->temp = NULL;
          return 1;
        }
        else
          cell = cell->below;

      }
      else
        break;
    }

  }
  else if (word->direction == HORIZONTAL){

    cell = word->head->left;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->head = cell;
          current->temp = NULL;
          return 1;
        }
        else
          cell = cell->left;

      }
      else
        break;
    }
    cell = word->head->right;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          current->temp = NULL;
          return 1;
        }
        else
          cell = cell->right;

      }
      else
        break;
    }

  }
  current->tile = NULL;
  return 0;

}
