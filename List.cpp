#include "List.h"

template <typename itemType>
List<itemType>::List(){

  size = 0;
  capacity = 2;
  items = new itemType[capacity];

}

template <typename itemType>
void List<itemType>::Grow(){

  itemType *temp = new itemType[capacity * 2];
  for(int i = 0; i < capacity; i++){
    temp[i] = items[i];
  }
  capacity *= 2;
  delete[] items;
  items = temp;

}

template <typename itemType>
void List<itemType>::AddItem(itemType item){

  size++;
  if(size > capacity)
    Grow();
  items[size - 1] = item;

}

template <typename itemType>
int List<itemType>::GetSize(){
  return size;
}

template <typename itemType>
itemType* List<itemType>::GetArray(){
  return items;
}

template <typename itemType>
void List<itemType>::QuickSort(int pivot, int rightIndex){

  itemType temp;
  int iLeft = pivot + 1, iRight = rightIndex;

  while(iLeft <= iRight){

    while(items[iLeft] < items[pivot] && iLeft < iRight){
      iLeft++;
    }

    while(items[iRight] > items[pivot] && iRight > pivot){
      iRight--;
    }

    if(iLeft <= iRight){
      temp = items[iRight];
      items[iRight] = items[iLeft];
      items[iLeft] = temp;
      iLeft++, iRight--;
    }

  }

  int middleIndex = iLeft - 1;

  temp = items[middleIndex];
  items[middleIndex] = items[pivot];
  items[pivot] = temp;

  if(middleIndex - pivot >= 2){
    QuickSort(pivot, middleIndex - 1);
  }
  if(rightIndex - middleIndex >= 2){
    QuickSort(middleIndex + 1, rightIndex);
  }

}

template <typename itemType>
void List<itemType>::Print(){

  for(int i = 0; i < size; i++){
    cout << items[i] << " ";
  }
  cout << endl;

}

template class List<int>;
template class List<string>;
