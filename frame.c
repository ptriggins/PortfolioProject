#include "frame.h"

// Creates a viewframe of a given size
void frame_init(FRAME* self, int numRows, int numCols, int availableRows, int availableCols){

  if (numRows <= availableRows){
    self->topRow = 0;
    self->bottomRow = numRows - 1;
  }
  else{
    self->topRow = (numRows - availableRows) / 2;
    self->bottomRow = numRows - self->topRow - 1;
  }

  if (numCols <= availableCols){
    self->leftCol = 0;
    self->rightCol = numCols - 1;
  }
  else{
    self->leftCol = (numCols - availableCols) / 2;
    self->rightCol = numCols - self->leftCol - 2;
  }

  self->centerRow = numRows / 2;
  self->centerCol = numCols / 2;

}

// Allocates memory for a viewframe of a given size
FRAME *frame_create(int numRows, int numCols, int availableRows, int availableCols){

  FRAME *newFrame = (FRAME*) malloc(sizeof(FRAME));
  frame_init(newFrame, numRows, numCols, availableRows, availableCols);
  return newFrame;

}

// Shifts the viewframe in an indicated direction

void frame_move_up(FRAME*self){
  self->topRow--;
  self->bottomRow--;
  self->centerRow--;
}

void frame_move_down(FRAME*self){
  self->topRow++;
  self->bottomRow++;
  self->centerRow++;
}

void frame_move_left(FRAME*self){
  self->leftCol--;
  self->rightCol--;
  self->centerCol--;
}

void frame_move_right(FRAME*self){
  self->leftCol++;
  self->rightCol++;
  self->centerCol++;
}
