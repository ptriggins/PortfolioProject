#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "word.h"
#include "dictionary.h"

// Checks the validy of a tile placement given a cell
void check_valid_tile_placement(WORD* word, CELL* current){

  CELL* cell = word->head;
  current->tile = current->temp;

  // Checks if a tile has already been played on the current cell
  if (current->played == 1){
    printw("Invalid Tile Placement                ");
    return;
  }

  // Checks if the tile is the first one to be played this turn
  if (word->head == NULL){
    word->head = current;
    current->temp = NULL;
    return;
  }
  // Determines a words direction if the tile placement is adjacent to a previous tile
  else if (word->direction == NONE){

    cell = word->head->above;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->head = cell;
          word->direction = VERTICAL;
          current->temp = NULL;
          return;
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
          return;
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
          return;
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
          return;
        }
        else
          cell = cell->right;

      }
      else
        break;
    }

  }
  // If more than two tiles have been played, checks that the tile is in the next available row of a given direction
  else if (word->direction == VERTICAL){

    cell = word->head->above;
    while (cell != NULL){
      if (cell->tile != NULL){

        if (cell == current){
          word->head = cell;
          current->temp = NULL;
          return;
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
          return;
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
          return;
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
          return;
        }
        else
          cell = cell->right;

      }
      else
        break;
    }

  }
  // If all else fails, the tile placement must have been invalid
  current->tile = NULL;
  mvprintw(0, 0, "Invalid Tile Placement             ");

}

int check_permutation(WORD* move, HAND* hand, NODE* dictionary, TILEBAG* tilebag){

  CELL *cell = move->head, *start = move->head;
  int score = 0;

  if (start->left->tile == NULL && start->right->tile == NULL && start->right->right->tile == NULL){

    int i = 0;
    char word[hand->numTiles + 2];
    word[0] = start->tile->letter;
    word[1] = '\0';

    cell = start->right;
    move->direction = HORIZONTAL;

    while(cell->right->tile == NULL && cell->right->letterScore != 0 && i < hand->numTiles){

      cell->tile = hand->tiles[i];
      word[i + 1] = hand->tiles[i]->letter;
      word[i + 2] = '\0';

      if (dictionary_search(word, dictionary) == 1){
        move->head = start->right;
        score = move_check(move, dictionary, 0);
        if (score > 0)
          return score;
      }
      cell = cell->right;
      i++;

    }
    while(cell != move->head){
      cell->tile = NULL;
      cell = cell->left;
    }

  }
  if (start->left->tile == NULL && start->right->tile == NULL && start->left->left->tile == NULL){

    int i = 0;
    char word[hand->numTiles + 2], newWord[hand->numTiles+2];
    word[0] = start->tile->letter;
    word[1] = '\0';

    cell = start->left;
    move->direction = HORIZONTAL;

    while (cell->left->tile == NULL && cell->left->letterScore != 0 && i < hand->numTiles){

      cell->tile = hand->tiles[i];
      newWord[0] = cell->tile->letter;
      strcat(newWord, word);

      if (dictionary_search(newWord, dictionary) == 1){
        move->head = cell;
        score = move_check(move, dictionary, 0);
        if (score > 0)
          return score;
      }
      cell = cell->left;
      i++;

    }
    while (cell != start){
      cell->tile = NULL;
      cell = cell->right;
    }

  }

  return 0;

}

int get_next_move(WORD* word, HAND* hand, NODE* dictionary, TILEBAG* tilebag){

  int score = check_permutation(word, hand, dictionary, tilebag);
  if (score == 0){
    if (word->head->above->played == 1)
      word->head = word->head->above;
    else if (word->head->right->played == 1)
      word->head = word->head->right;
    else
      return 0;
    return get_next_move(word, hand, dictionary, tilebag);
  }
  else
    return score;
  return 0;

}
