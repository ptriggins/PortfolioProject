#include "word.h"

WORD* word_create(){

  WORD* newMove = (WORD*) malloc(sizeof(WORD));
  newMove->head = NULL;
  newMove->direction = NONE;
  return newMove;

}

void word_cancel(WORD* self){

  CELL* cell = self->head;
  cell_clear_tiles(cell);
  if (self->direction == VERTICAL){
    while(cell->tile != NULL){

      if (cell->played != 1)
        cell_clear_tiles(cell);
      cell = cell->below;

    }
  }
  else if(self->direction == HORIZONTAL){
    while(cell->tile != NULL){

      if (cell->played != 1)
        cell_clear_tiles(cell);
      cell = cell->right;

    }
  }
  self->head->selected = 1;

}

void word_set(WORD* self, HAND* hand, TILEBAG* tilebag){

  CELL* cell = self->head;
  cell_play_tile(cell);
  hand_remove_tile(hand, cell->tile, tilebag);
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

}

int move_check(WORD* word, NODE* dictionary){

  int score = 0, wordScore = 0;
  CELL *head = word->head, *newHead = head;

  while (head != NULL){

    newHead = head;
    if (word->direction == VERTICAL){

      if (head->left->tile != NULL){

        while (newHead->left->tile != NULL){
          newHead = newHead->left;
        }
        wordScore = word_check(newHead, dictionary, HORIZONTAL);
        if (wordScore == 0)
          return 0;

      }
      else if (head->right->tile!= NULL){

        wordScore = word_check(head, dictionary, HORIZONTAL);
        if (wordScore == 0)
          return 0;

      }
      score += wordScore;
      head = head->below;

    }
    if (word->direction == HORIZONTAL){

      if (head->above->tile != NULL){

        while (newHead->above->tile != NULL){
          newHead = newHead->above;
        }
        wordScore = word_check(newHead, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;

      }
      else if (head->below->tile!= NULL){

        wordScore = word_check(head, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;

      }
      score += wordScore;
      head = head->right;

    }
    if (word->direction == NONE){

      if (head->above->tile != NULL){

        printw("1t\n");
        while (newHead->above->tile != NULL){
          newHead = newHead->above;
        }
        wordScore = word_check(newHead, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->below->tile!= NULL){

        printw("2t\n");
        wordScore = word_check(head, dictionary, VERTICAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      newHead = head;
      if (head->left->tile != NULL){


        printf("3t\n");
        while (newHead->left->tile != NULL){
          newHead = newHead->left;
        }
        wordScore = word_check(newHead, dictionary, HORIZONTAL);
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      else if (head->right->tile!= NULL){

        printf("4t\n");
        wordScore = (word_check(head, dictionary, HORIZONTAL));
        if (wordScore == 0)
          return 0;
        score += wordScore;

      }
      break;

    }

  }

  if (word->direction != NONE)
    wordScore = word_check(word->head, dictionary, word->direction);

  if (wordScore == 0)
    return 0;
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
    printw("Valid Word: %s + %d\n", word, score);
    return score;
  }
  printw("Invalid Word: %s\n", word);
  return 0;

}
