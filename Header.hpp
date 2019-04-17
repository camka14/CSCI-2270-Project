#include <string>
#include <iostream>

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
	string sent;
	float score;
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
	Operand* stackHead; // pointer to the top of the stac
};

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

    Sent* commonQueue;
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
    int getNumCollisions();
    int getNumItems();
    int getTotalNumWords();

  private:
    /* member functions */
    unsigned int getHash(std::string word);
    wordItem* searchTable(std::string word);

    /* instance variables */
    wordItem** hashTable;
    int hashTableSize;
    int numItems;
    int numCollisions;
};