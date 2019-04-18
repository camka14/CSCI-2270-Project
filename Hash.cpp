#include <iostream>
#include <string>

#include "Header.hpp"

using namespace std;

Hash(int hashTableSize){

}
~Hash();
void addWord(string word) {
	if(!isInTable(word))
	{
		int index = getHash(word);
		if(!hashTable[index])
			hashTable[index] = createNode(word,nullptr);
		else {
			Word *temp = hashTable[index];
			while(temp->next)
				temp = temp->next;
			temp->next = createNode(word,nullptr);
		}
	}
	else {
		cout << "Already exists: " << word << endl;
	}
}
bool isInTable(string word) {
	int index = getHash(word);

	node *temp = hashTable[index];
	while(temp) {
		if(temp->word == word)
			return true;
		else 
			temp = temp->next;
	}
	return nullptr;
}
void incrementCount(string word) {
	bool isFound = isInTable(word);
	Word* item = searchTable(word);
	if (isFound) {
		++(item->count); // Do we need to increment count here?
	}
}
void printTopN(int n);
int getNumCollisions();
int getNumItems();
int getTotalNumWords();

Word* createNode(string word, Word* next){
	Word* node = new Word;
	node->word = word;
	node->next = next;
	return node;
}


/* member functions */
unsigned int getHash(string word) {
	unsigned int​ hashValue = ​5381​; 
    int ​length = word.​length​();
    
    for ​(​int​ i=​0​;i<length;i++) {
        hashValue=((hashValue<<​5​)+hashValue) + word[i]; 
    }
    hashValue %= hashTableSize; 
    return ​hashValue; 
}
Word* searchTable(string word);
