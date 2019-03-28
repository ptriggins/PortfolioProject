#include "frame.h"

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
    self->leftRow = 0;
    self->rightRow = numCols - 1;
  }
  else{
    self->leftRow = (numCols - availableCols) / 2;
    self->rightRow = numCols - self->leftRow - 2;
  }

  self->centerRow = self->topRow + (self->bottomRow - self->topRow) / 2;
  self->centerCol = self->leftCol + (self->leftCol - self->rightCol) / 2;

}

FRAME* frame_create(int numRows, int numCols, int availableRows, int availableCols){

  FRAME* newFrame = (FRAME*) malloc(sizeof(FRAME));
  frame_init(newFrame, numRows, numCols, availableRows, availableCols);
  return newFrame;

}

void frame_move_up(FRAME*self){
  self->topRow--;
  self->bottomRow--;
  self->centerRow = self->topRow + (self->bottomRow - self->topRow) / 2;
  self->centerCol = self->leftCol + (self->leftCol - self->rightCol) / 2;
}

void frame_move_down(FRAME*self){
  self->topRow++;
  self->bottomRow++;
  self->centerRow = self->topRow + (self->bottomRow - self->topRow) / 2;
  self->centerCol = self->leftCol + (self->leftCol - self->rightCol) / 2;
}

void frame_move_left(FRAME*self){
  self->leftCol--;
  self->rightCol--;
  self->centerRow = self->topRow + (self->bottomRow - self->topRow) / 2;
  self->centerCol = self->leftCol + (self->leftCol - self->rightCol) / 2;
}

void frame_move_right(FRAME*self){
  self->leftCol++;
  self->rightCol++;
  self->centerRow = self->topRow + (self->bottomRow - self->topRow) / 2;
  self->centerCol = self->leftCol + (self->leftCol - self->rightCol) / 2;
}
