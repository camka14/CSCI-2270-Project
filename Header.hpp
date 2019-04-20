#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;

struct Word
{
	string word;
	float TF = 0;
	float IDF = 0;
	int countTF = 0;
	int countIDF = 0;
};

struct Sent
{
	vector<string> sentence;
	float score = 0;
	Sent *next = 0;
};

class Stack
{
public:
	Stack();
	~Stack();
	bool isEmpty();
	void push(Sent *sentence);
	void pop();
	Sent* peek();
private:
	Sent* stackHead; // pointer to the top of the stack
};

//This class is done
class Heap
{
public:
    Heap(int queueSize);
    ~Heap();
    void enqueue(std::string _groupName, int _groupSize, int _cookingTime);
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

void getIDF(string refCorpus, Word *word);
void getTF(Word *word);
Sent* makeNewSent();