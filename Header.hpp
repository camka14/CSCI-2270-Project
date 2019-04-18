#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

struct Word
{
	string word;
	float TF;
	float IDF;
	int countTF;
	int countIDF;
};

struct Sent
{
	vector<string> sentence;
	float score;
	Sent *next;
};

class Stack
{
public:
	Stack();
	~Stack();
	bool isEmpty();
	void push(Sent sentence);
	void pop();
	Sent* peek();
	Sent* getStackHead() { return stackHead; } // no need to implement this
private:
	Sent* stackHead; // pointer to the top of the stac
};

//This class is done
class Heap
{
public:
    Heap(int queueSize);
    ~Heap();
    void enqueue (string sentence, float score);
    void dequeue();
    Sent peek();
    bool isFull();
    bool isEmpty();
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);
    void swap(Sent *a, Sent *b);


private:
    void repairUpward(int nodeIndex);
    void repairDownward(int nodeIndex);

    Sent* HeapArray;
    int currentHeapSize;
    int maxHeapSize;
};

class Hash
{
public:
    Hash(int hashTableSize);
    ~Hash();
    void addWord(std::string word);
    bool isInTable(std::string word);
    void incrementCount(std::string word);
    void printTopN(int n);
    int getNumCollisions();
    int getNumItems();
    int getTotalNumWords();

private:
    /* member functions */
    unsigned int getHash(std::string word);
    Word* searchTable(std::string word);

    /* instance variables */
    Word** hashTable;
    int hashTableSize;
    int numItems;
    int numCollisions;
};