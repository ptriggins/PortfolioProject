#include<iostream>
#include<string>
using namespace std;

template <typename itemType>
class List{

  public:
    List();
    void Grow();
    void AddItem(itemType item);
    int GetSize();
    itemType* GetArray();
    void QuickSort(int iLeft, int iRight);
    void Print();

  private:
    int size, capacity;
    itemType *items;

};
