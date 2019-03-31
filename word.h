#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "cell.h"
#include "hand.h"
#include "dictionary.h"

#ifndef WORD_H
#define WORD_H

#define NONE 0
#define HORIZONTAL 1
#define VERTICAL 2

typedef struct WORD{

  CELL *head;
  int direction;

}WORD;

WORD* word_create();
void word_cancel(WORD* self);
void word_set(WORD* self, HAND* hand, TILEBAG* tilebag);
int move_check(WORD* word, NODE* dictionary);
int word_check(CELL* head, NODE* dictionary, int direction);

#endif
