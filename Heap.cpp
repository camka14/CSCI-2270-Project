#include <iostream>
#include <string>

#include "Header.hpp"

using namespace std;

Heap::Heap(int queueSize) {
	// creates Heap with an array of pointers
	// each pointer, points to an index
	this->maxQueueSize = queueSize;
	Sent **heap = new Sent*[queueSize];
	this->HeapArray = heap;
}

Heap::~Heap() {

} 

void Heap::swap(Sent *a, Sent *b)
{
  Sent temp = *a;
  *a = *b;
  *b = temp;
}

void Heap::enqueue (Sent *sentence) {
	if(isEmpty()) {
		HeapArray[currentQueueSize] = sentence;
	}
	else if(isFull()) {
		doubleArr();
		HeapArray[currentQueueSize] = sentence;
		repairUpward(currentQueueSize);
		currentQueueSize++;
	}
	else{
		HeapArray[currentQueueSize] = sentence;
		repairUpward(currentQueueSize);
		currentQueueSize++;
	}
}
void Heap::dequeue() {
	if(isEmpty()) {
    	cout << "Heap empty, cannot dequeue" << endl;
    }

    int size = currentQueueSize - 1;
    HeapArray[0] = HeapArray[size];
    currentQueueSize = size;

    repairDownward(0);
}
Sent* Heap::peek() {
	return HeapArray[0];
}
bool Heap::isFull() {
	if(currentQueueSize == maxQueueSize)
		return true;
	return false;
}
bool Heap::isEmpty() {
	if(currentQueueSize == 0)
		return true;
	return false;
}

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

//private:
void Heap::repairUpward(int nodeIndex) {
  int p = parent(nodeIndex);
  if(p >= 0 && HeapArray[p]->score < HeapArray[nodeIndex]->score){
    swap(HeapArray[nodeIndex],HeapArray[p]);
    repairUpward(p);
  }
  else if(p >= 0 && HeapArray[p]->score == HeapArray[nodeIndex]->score && HeapArray[p]->score < HeapArray[nodeIndex]->score){
    swap(HeapArray[nodeIndex],HeapArray[p]);
    repairUpward(p);
  }
}
void Heap::repairDownward(int nodeIndex) {
	int l = leftChild(nodeIndex);
 	int r = rightChild(nodeIndex);
 	int largest = nodeIndex;
 	int temp;

 	//TODO

 	if(l < currentQueueSize && HeapArray[l]->score>HeapArray[largest]->score)
   		largest = l;
 	if(r < currentQueueSize && HeapArray[r]->score>HeapArray[largest]->score)
   		largest = r;
 	if(largest !=nodeIndex){
   		swap(HeapArray[nodeIndex],HeapArray[largest]);
    	repairDownward(largest);
  }
}

void Heap::doubleArr()
{
	Sent **nArr = new Sent*[2*currentQueueSize];

	for (int i=0; i <currentQueueSize; i++) {
		nArr[i] = *(HeapArray+i);
	}

	maxQueueSize = 2*currentQueueSize;

	delete[] HeapArray;
	HeapArray = nArr;
}