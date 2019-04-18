#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
// Add #includes
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
	float score = 0;
	Sent *next;
};

class Stack
{

	Stack();
	~Stack();
	bool isEmpty();
	void push(float num);
	void pop();
	Sent* peek();
	Sent* getStackHead() { return stackHead; } // no need to implement this
private:
	Sent* stackHead; // pointer to the top of the stac
};

class Heap
{
	public:
    Heap(int queueSize);
    ~Heap();
    void enqueue (std::string _groupName, int _groupSize, int _cookingTime);
    void dequeue();
    Sent peek();
    bool isFull();
    bool isEmpty();

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