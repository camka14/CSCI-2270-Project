#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;

// word struct to store words of the text file
// and reference document and their TF and IDF values
struct Word
{
	string word;
	float TF = 0;
	float IDF = 0;
	int countTF = 0;
	int countIDF = 0;
    Word* next;
};

// Sent struct to store each sentence (in the form of a vector of words)
// and to store the sentences score (of importance)
struct Sent
{
	vector<string> sentence;
	float score = 0;
	Sent *next = 0;
	int num;
};

// initializing Stack class
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
    void enqueue (Sent *sentence);
    void dequeue();
    Sent* peek();
    bool isFull();
    bool isEmpty();
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);
    void swap(Sent *a, Sent *b);


private:
    void repairUpward(int nodeIndex);
    void repairDownward(int nodeIndex);
    void doubleArr();

    Sent** HeapArray;
    int currentQueueSize;
    int maxQueueSize;
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
    int getTotalNumWords();
    void getIDFCount(string refCorpus);
    void getIDF(Word *word);
    void getTF(Word *word);
    Word* getWord(string word);
    Word* createNode(string word, Word* next);

private:
    /* member functions */
    unsigned int getHash(std::string word);
    Word* searchTable(std::string word);

    /* instance variables */
    Word** hashTable;
    int hashTableSize;
    int totalCountRF;
    int numCollisions;
};