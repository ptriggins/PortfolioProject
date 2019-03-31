#include "word.h"

WORD* word_create(){

  WORD* newMove = (WORD*) malloc(sizeof(WORD));
  newMove->head = NULL;
  newMove->direction = NONE;
  return newMove;

}

void word_cancel(WORD* self){

  CELL* cell = self->head;
  if (cell == NULL)
    return;

  if (self->direction == VERTICAL){
    while(cell->tile != NULL){

      if (cell->played != 1)
        cell_clear_tile(cell, cell->tile);
      cell = cell->below;

    }
  }
  else if(self->direction == HORIZONTAL){
    while(cell->tile != NULL){

      if (cell->played != 1)
        cell_clear_tile(cell, cell->tile);
      cell = cell->right;

    }
  }
  else if (self->direction == NONE){
    cell_clear_tile(cell, cell->tile);
  }

}

void word_set(WORD* self, HAND* hand, TILEBAG* tilebag){

  CELL* cell = self->head;
  if (self->direction == VERTICAL){
    while(cell->tile != NULL){

      if (cell->played != 1){
        cell_play_tile(cell);
        hand_remove_tile(hand, cell->tile, tilebag);
      }
      cell = cell->below;

    }
  }
  else if(self->direction == HORIZONTAL){
    while(cell->tile != NULL){

      if (cell->played != 1){
        cell_play_tile(cell);
        hand_remove_tile(hand, cell->tile, tilebag);
      }
      cell = cell->right;

    }
  }
  else if (self->direction == NONE){
    cell_play_tile(cell);
    hand_remove_tile(hand, cell->tile, tilebag);
  }

}

int move_check(WORD* word, NODE* dictionary, int first){

  int score = 0, wordScore = 0, adjacent = first;

  CELL *head = word->head, *newHead = head;
  while (head->tile != NULL){

    newHead = head;
    if (word->direction == VERTICAL){

      if (head->left->tile != NULL && head->played == 0){

        adjacent = 1;
        while (newHead->left->tile != NULL){
          newHead = newHead->left;
        }
        wordScore = word_check(newHead, dictionary, HORIZONTAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->right->tile != NULL && head->played == 0){

        adjacent = 1;
        wordScore = word_check(head, dictionary, HORIZONTAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->played == 1)
        adjacent = 1;
      head = head->below;

    }
    if (word->direction == HORIZONTAL){

      if (head->above->tile != NULL && head->played == 0){

        adjacent = 1;
        while (newHead->above->tile != NULL){
          newHead = newHead->above;
        }
        wordScore = word_check(newHead, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->below->tile!= NULL && head->played == 0){

        adjacent = 1;
        wordScore = word_check(head, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->played == 1)
        adjacent = 1;
      head = head->right;

    }
    if (word->direction == NONE){

      if (head->above->tile != NULL){

        adjacent = 1;
        while (newHead->above->tile != NULL){
          newHead = newHead->above;
        }
        wordScore = word_check(newHead, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->below->tile!= NULL){

        adjacent = 1;
        wordScore = word_check(head, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      newHead = head;
      if (head->left->tile != NULL){

        adjacent = 1;
        while (newHead->left->tile != NULL){
          newHead = newHead->left;
        }
        wordScore = word_check(newHead, dictionary, HORIZONTAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->right->tile!= NULL){

        adjacent = 1;
        wordScore = (word_check(head, dictionary, HORIZONTAL));
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      break;

    }

  }

  head = word->head;
  if (word->direction == VERTICAL){
    while(head->above->tile != NULL){
      adjacent = 1;
      head = head->above;
    }
    wordScore = word_check(head, dictionary, VERTICAL);
  }
  else if (word->direction == HORIZONTAL){
    while (head->left->tile != NULL){
      adjacent = 1;
      head = head->left;
    }
    wordScore = word_check(head, dictionary, HORIZONTAL);
  }

  if (wordScore == 0)
    return 0;
  if (adjacent == 0){
    mvprintw(0, 0, "Invalid Move: Not Adjacent to Played Words");
    return 0;
  }
  return score + wordScore;

}

int word_check(CELL* head, NODE* dictionary, int direction){

  int i = 0;
  int score = 0, x = 1;
  char word[20];
  CELL* cell = head;

  if (direction == VERTICAL){

    while(cell->tile != NULL){

      word[i] = cell->tile->letter;
      if (cell->played == 0){
        score += cell->tile->score * cell->letterScore;
        x *= cell->wordScore;
      }
      else
        score += cell->tile->score;

      cell = cell->below;
      i++;

    }

  }
  else if(direction == HORIZONTAL){

    while(cell->tile != NULL){

      word[i] = cell->tile->letter;
      if (cell->played == 0){
        score += cell->tile->score * cell->letterScore;
        x *= cell->wordScore;
      }
      else
        score += cell->tile->score;

      cell = cell->right;
      i++;
    }

  }
  else{
    word[0] = cell->tile->letter;
    i++;
  }

  word[i] = '\0';
  score *= x;

  if (dictionary_search(word, dictionary) == 1){
    mvprintw(0, 0, "Valid Word: %s  (%d)\n", word, score);
    return score;
  }
  mvprintw(0, 0, "Invalid Word: (%s)\n", word);
  return 0;

}
