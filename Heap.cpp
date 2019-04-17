#include <iostream>
#include <string>

#include "Header.hpp"

using namespace std;

Heap::Heap(int queueSize) {
	this->maxQueueSize = queueSize;
	Sent *heap = new Sent[queueSize];
	this->commonQueue = heap;
}

Heap::~Heap() {

} 

void Heap::swap(Sent *a, Sent *b)
{
  Sent temp = *a;
  *a = *b;
  *b = temp;
}

void Heap::enqueue (string sentence, float score) {
	Sent *Node = new Sent;
	commonQueue[currentQueueSize] = Node;

	if(isEmpty()) {
		commonQueue[currentQueueSize] = value; 
	}
	else {
		commonQueue[currentQueueSize] = value;
		repairUpward(currentQueueSize);
		currentQueueSize++;
	}
}
void Heap::dequeue() {
	if(isEmpty()) {
    	cout << "Heap empty, cannot dequeue" << endl;
        return peek();
    }

    int size = currentQueueSize - 1;
    commonQueue[0] = commonQueue[size];
    currentQueueSize = size;

    repairDownward(0);
    return peek();
}
Sent Heap::peek() {
	return commonQueue[0];
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
void Heap::repairUpward(int nodeIndex);
void Heap::repairDownward(int nodeIndex) {
	int l = leftChild(index);
 	int r = rightChild(index);
 	int largest = index;
 	int temp;

 	//TODO
 	if(l < currentQueueSize && commonQueue[l]<commonQueue[largest])
   		largest = l;
 	if(r < currentQueueSize && commonQueue[r]<commonQueue[largest])
   		largest = r;
 	if(largest !=index){
   		swap(commonQueue[index],commonQueue[largest]);
    	repairDownward(largest);
  }
}