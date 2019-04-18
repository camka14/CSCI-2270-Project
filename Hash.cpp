#include <iostream>
#include <string>

#include "Header.hpp"

using namespace std;

Hash(int hashTableSize){

}
~Hash();
void addWord(string word) {
	if(!searchTable(word))
	{
		int index = getHash(word);
		if(!hashTable[index])
			hashTable[index] = 
	}
}
bool isInTable(string word);
void incrementCount(string word);
void printTopN(int n);
int getNumCollisions();
int getNumItems();
int getTotalNumWords();
wordItem* createNode(string word, wordItem* next);


/* member functions */
unsigned int getHash(string word){
	int wordValue = word;
}
wordItem* searchTable(string word);