#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include "List.h"
using namespace std;

template <typename itemType>
void Compare(itemType *array1, itemType *array2, int size1, int size2){

  int i = 0, j = 0;
  while(i < size1 && j < size2){

    if(array1[i] == array2[j]){
      cout << array1[i] << endl;
      i++, j++;
    }
    else if(array1[i] < array2[j])
      i++;
    else
      j++;

    if(i > 0){
      while(array1[i] == array1[i - 1]){
        i++;
        if(i == size1)
          break;
      }
    }

    if(j > 0){
      while(array2[j] == array2[j - 1] && j > 0 && j > size2 - 1){
        j++;
        if(j == size2)
          break;
      }
    }

  }

}
template void Compare<int>(int *array1, int *array2, int size1, int size2);
template void Compare<string>(string *array1, string *array2, int size1, int Size2);

int main(int argc, char* argv[]){

  string type = argv[1];
  ifstream inFile1(argv[2]), inFile2(argv[3]);
  int nextInt;
  string nextString;

  if(type == "i"){
    List<int> input1, input2;

    while(inFile1 >> nextInt){
      input1.AddItem(nextInt);
    }
    while(inFile2 >> nextInt){
      input2.AddItem(nextInt);
    }
    input1.QuickSort(0, input1.GetSize() - 1);
    input2.QuickSort(0, input2.GetSize() - 1);

    Compare(input1.GetArray(), input2.GetArray(), input1.GetSize(), input2.GetSize());

  }
  if(type == "s"){
    List<string> input1, input2;

    while(inFile1 >> nextString){
      input1.AddItem(nextString);
    }
    while(inFile2 >> nextString){
      input2.AddItem(nextString);
    }

    input1.QuickSort(0, input1.GetSize() - 1);
    input2.QuickSort(0, input2.GetSize() - 1);

    Compare(input1.GetArray(), input2.GetArray(), input1.GetSize(), input2.GetSize());

  }

}
