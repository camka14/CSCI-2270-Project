#include "heaps.hpp"
#include <limits.h>
using namespace std;

/*
Swaps two integer values
*/
void swap(float *a, float *b)
{
  float temp = *a;
  *a = *b;
  *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
Heap::Heap(int cap)
{
  currentSize = 0;
  heapSize = cap;
  heap = new float[heapSize];
}

Heap::~Heap()
{

}

/*
Finds the parent of a node, given its index.
*/
int Heap::parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int Heap::leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int Heap::rightChild(int index)
{
  return ((2*index) + 2);
}

/*
Returns the smallest element from the heap.
*/
float Heap::peekValue()
{
  return heap[0];
}

// SILVER TODO : Complete this function
/*
To heapify a subtree with the root at given index
*/
void Heap::repairDownward(int index)
{
  int l = leftChild(index);
  int r = rightChild(index);
  int largest = index;
  int temp;

  //TODO
  if(l < currentSize && heap[l]<heap[largest])
    largest = l;
  if(r < currentSize && heap[r]<heap[largest])
    largest = r;
  if(largest !=index){
    swap(heap[index],heap[largest]);
    repairDownward(largest);
  }
}

void Heap::repairUpward(int index)
{
  int p = parent(index);
  if(p >= 0 && heap[p] > heap[index]){
    swap(heap[index],heap[p]);
    repairUpward(p);
  }else if(p >= 0 && heap[p] == heap[index] && heap[p] > heap[index]){
    swap(heap[index],heap[p]);
    repairUpward(p);
  }
}

/*
Inserts an element into the heap by maintaining the heap property.
*/
void Heap::addToHeap(float value)
{
  if(currentSize == heapSize)
  {
    cout<<"Maximum heap size reached. Cannot insert anymore"<<endl;
    return;
  }

  currentSize = currentSize + 1;
  int index = currentSize - 1;
  heap[index] = value;

  while (index != 0 && heap[parent(index)] > heap[index])
    {
       swap(&heap[index], &heap[parent(index)]);
       index = parent(index);
    }
}

/*
Prints the elements in the heap
*/
void Heap::printHeap()
{
  int iter = 0;
  while(iter < currentSize)
  {
    cout<<heap[iter]<<" ";
    iter = iter + 1;
  }
  cout<<endl;
}

// SILVER TODO : Complete this function
// Method to remove minimum element (or root) from min heap
float Heap::removeFromHeap()
{
  if (currentSize <= 0)
      return INT_MAX;

  if (currentSize == 1)
  {
      currentSize--;
      return heap[0];
  }

  float minimum = heap[0];
    //TODO
  heap[0] = heap[currentSize-1];
  heap[currentSize] = 0;
  repairDownward(0);
  currentSize--;

  return minimum;

}

float Heap::extractMin()
{
  if (currentSize <= 0)
      return heapSize;

  if (currentSize == 1)
  {
      currentSize--;
      return heap[0];
  }

  float minimum = heap[0];
    //TODO
  heap[0] = heap[currentSize-1];
  heap[currentSize] = 0;
  repairDownward(0);
  currentSize--;

  return minimum;
}

void Heap::deleteKey(int key)
{
  // there are many ways of doing it, one of them can be :
  // replace the key to be deleted with INT_MIN (a very small number), traverse it up to the root and then remove it!
  int del;
  for(int i=0; i<currentSize; i++){
    if(heap[i] == key)
      del = i;
  }
  heap[del] = INT_MIN;
  int pr = parent(del);
  int i = del;
  while(i != 0){
    swap(heap[pr],heap[i]);
    i = parent(i);
    pr = parent(i);
  }
  extractMin();
}

bool Heap::isFull()
{
  if(currentSize == heapSize)
    return true;
  return false;
}

bool Heap::isEmpty()
{
  if(currentSize == 0)
    return true;
  return false;
}

float Heap::heapSort(float arr[], int size)
{
  int i = 0;
  for(int i=0; i<size; i++)
  {
    addToHeap(arr[i]);
  }
  for(int i=0; i<size; i++){
    arr[i] = peekValue();
    removeFromHeap();
  }
}