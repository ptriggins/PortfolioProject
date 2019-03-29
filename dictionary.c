#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct NODE{

  char word[20];
  struct NODE *left, *right;

}NODE;

NODE* node_create(char word[20]){

  NODE* newNode = (NODE*) malloc(sizeof(NODE));
  strcpy(newNode->word, word);
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;

}

NODE* tree_create(char** words, int start, int end){

  if (start > end) return NULL;

  int mid = (start + end) / 2;
  NODE* root = node_create(words[mid]);

  root->left = tree_create(words, start, mid - 1);
  root->right = tree_create(words, mid + 1, end);

  return root;

}

NODE* dictionary_create(char* dictionaryFile, int numWords){

  FILE* wordFile = fopen(dictionaryFile, "r");

  char** words = (char**) malloc(numWords * sizeof(char*));
  for (int i = 0; i < numWords; i++){
    words[i] = (char*) malloc(20 * sizeof(char));
  }

  for (int i = 0; i < numWords; i++){
    fscanf(wordFile, "%s", words[i]);
  }

  NODE* dictionary = tree_create(words, 0, numWords - 1);
  free(words);
  return dictionary;

}

int dictionary_search(char* word, NODE* dictionary){

  if (dictionary == NULL)
    return 0;
  else if (strcmp(word, dictionary->word) == 0)
    return 1;
  else if (strcmp(word, dictionary->word) < 0)
    return dictionary_search(word, dictionary->left);
  else
    return dictionary_search(word, dictionary->right);

}
