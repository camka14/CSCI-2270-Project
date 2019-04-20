#include <iostream>
#include <string>

#include "Header.hpp"

using namespace std;

Hash::Hash(int hashTableSize){
	this->hashTableSize = hashTableSize;
	hashTable = new Word*[hashTableSize];
	for(int i = 0; i < hashTableSize; i++) {
		hashTable[i] = nullptr;
	}
}
Hash::~Hash(){

}
void Hash::addWord(string word) {
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
bool Hash::isInTable(string word) {
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
void Hash::incrementCount(string word) {
	bool isFound = isInTable(word);
	Word* item = searchTable(word);
	if (isFound) {
		++(item->count); // Do we need to increment count here?
	}
}
int Hash::getTotalNumWords() {
	int count = 0;
	Word* temp1 = hashTable[0];

	while(temp1) {
		count++;
		temp1 = temp1->next;
	}

	return count;
}

Word* Hash::createNode(string word, Word* next){
	Word* node = new Word;
	node->word = word;
	node->next = next;
	return node;
}


/* member functions */
unsigned int Hash::getHash(string word) {
	unsigned int​ hashValue = ​5381​; 
    int ​length = word.​length​();
    
    for ​(​int​ i=​0​;i<length;i++) {
        hashValue=((hashValue<<​5​)+hashValue) + word[i]; 
    }
    hashValue %= hashTableSize; 
    return ​hashValue; 
}
Word* Hash::searchTable(string word) {
	int index = getHash(word);

	Word* temp = hashTable[index];
	while(temp) {

		if(temp->word == word)
			return temp;
		else 
			temp = temp->next;
	}
	return nullptr;
}

void Hash::getTF(Word *word)
{
	word.TF = log(1+word.countTF);
}

void Hash::getIDF(string word)
{
	Word *wordItem = searchTable(word);
	wordItem.IDF = log(totalCount/wordItem.countIDF);
}

void Hash::getIDFCount(string refCorpus)
{
	char letter;
	stringstream is(refCorpus);
	regex wordChar("[a-zA-Z]");
	regex nonWordChar("[\\s|!|?|.]");

	while(is.get(letter))
	{
		if(regex_match(&letter,wordChar))
			word += wordChar;
		else if(regex_match(&letter,nonWordChar))
		{
			if(word != ""){
				if(isInTable(word)){
					Word *wordItem = searchTable(word);
					wordItem.countIDF++;
					totalCount++;
				}
				word = "";
			}
		}
	}
}