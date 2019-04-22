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
	totalCountRF = 0;
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
		incrementCount(word);
	}
}
bool Hash::isInTable(string word) {
	int index = getHash(word);

	Word *temp = hashTable[index];
	while(temp) {
		if(temp->word == word)
			return true;
		else 
			temp = temp->next;
	}
	return false;
}
void Hash::incrementCount(string word) {
	Word* item = searchTable(word);
	item->countTF++;
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

unsigned int Hash::getHash(string word)
{
	unsigned int hashValue = 5381;
	int length = word.length();
	for (int i=0;i<length;i++)
	{
		hashValue=((hashValue<<5)+hashValue) + word[i];
	}
	hashValue %= hashTableSize;
	return hashValue;
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
	word->TF = (float)log(1+word->countTF);
}

void Hash::getIDF(Word *word)
{
	word->IDF = (float)log(totalCountRF/(1+word->countIDF));
}

void Hash::getIDFCount(string refrence)
{
	char letter;
	string word;

	regex wordChar("[a-zA-Z]");
	regex nonWordChar("[\\s|.|;|?|!]");
	ifstream refText;
	refText.open(refrence);

	while(refText.get(letter))
	{
		string letterS = "";
		letterS+= letter;
		if(regex_match(letterS,wordChar)){
			word += letterS;
		}
		else if(regex_match(letterS,nonWordChar))
		{
			if(word != ""){
				if(isInTable(word)){
					Word *wordItem = searchTable(word);
					wordItem->countIDF++;
					totalCountRF++;
				}
				word = "";
			}
		}
	}
}

Word* Hash::getWord(string word) {
	return searchTable(word);
}
