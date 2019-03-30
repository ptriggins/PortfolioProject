#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct NODE{

  char word[20];
  struct NODE *left, *right;

}NODE;

NODE* node_create(char word[20]);
NODE* tree_create(char** words, int start, int end);
NODE* dictionary_create(char* dictionaryFile, int numWords);
int dictionary_search(char* word, NODE* dictionary);

#endif
