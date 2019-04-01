#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "word.h"
#include "dictionary.h"

void check_valid_tile_placement(WORD* word, CELL* current){

  CELL* cell = word->head;
  current->tile = current->temp;

  if (current->played == 1){
    printw("Invalid Tile Placement");
    return;
  }

  if (word->head == NULL){
    word->head = current;
    current->temp = NULL;
    return;
  }
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
  mvprintw(4, 0, "%c", word->head->tile->letter);
  current->tile = NULL;
  printw("Invalid Tile Placement");

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
  /*
  if (start->below->tile == NULL && start->below->below->tile == NULL && start->above->tile == NULL){

    int i = 0;
    char word[hand->numTiles + 2];
    word[0] = start->tile->letter;
    word[1] = '\0';

    cell = start->below;
    move->direction = VERTICAL;

    while(cell->below->tile == NULL && cell->below->letterScore != 0 && i < hand->numTiles){

      cell->tile = hand->tiles[i];
      word[i + 1] = hand->tiles[i]->letter;
      word[i + 2] = '\0';

      if (dictionary_search(word, dictionary) == 1){
        move->head = start->below;
        score = move_check(move, dictionary, 0);
        if (score > 0)
          return score;

      }
      cell = cell->below;
      i++;

    }
    while(cell != start){
      cell->tile = NULL;
      cell = cell->above;
    }

  }
  if (start->above->tile == NULL && start->below->tile == NULL && start->above->above->tile == NULL ){

    int i = 0;
    char word[hand->numTiles + 2], newWord[hand->numTiles+2];
    word[0] = start->tile->letter;
    word[1] = '\0';

    cell = cell->above;
    move->direction = VERTICAL;

    while(cell->above->tile == NULL && cell->above->letterScore != 0 && i < hand->numTiles){

      cell->tile = hand->tiles[i];
      newWord[0] = cell->tile->letter;
      strcat(newWord, word);

      if (dictionary_search(newWord, dictionary) == 1){
        move->head = cell;
        score = move_check(move, dictionary, 0);
        if (score > 0)
          return score;
      }
      cell = cell->above;
      i++;

    }
    while(cell != start){
      cell->tile = NULL;
      cell = cell->below;
    }

  }
  */
  return 0;

}

int hand_permute(WORD* move, HAND* hand, int size, int n, NODE* dictionary, TILEBAG* tilebag){

    TILE* temp;
    int score = 0;
    if (size == 1){

        score += check_permutation(move, hand, dictionary, tilebag);
        if (score > 0){
          return score;
        }

    }
    for (int i = 1; i < size; i++){

        score += hand_permute(move, hand, size-1, n, dictionary, tilebag);
        if (score > 0){
          return score;
        }

        if (size % 2 == 1){
          temp = hand->tiles[0];
          hand->tiles[0] = hand->tiles[size - 1];
          hand->tiles[size - 1] = temp;
        }

        else{
          temp = hand->tiles[i];
          hand->tiles[i] = hand->tiles[size - 1];
          hand->tiles[size - 1] = temp;
        }

    }
    return 0;

}


int get_next_move(WORD* word, HAND* hand, NODE* dictionary, TILEBAG* tilebag){

  int score = check_permutation(word, hand, dictionary, tilebag);
  if (score == 0){
    if (word->head->above->played == 1){
      word->head = word->head->above;
    }
    else if (word->head->left->played == 1){
      word->head = word->head->left;
    }
    else
      return 0;
    return get_next_move(word, hand, dictionary, tilebag);
  }
  else
    return score;
  return 0;

}
