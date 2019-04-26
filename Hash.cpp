#include <iostream>
#include <string>
#include <regex>
#include <cmath>

#include "Header.hpp"

using namespace std;
//****This .cpp file contains all functions for setting up the hash table of word structs *****

// creates the inital Hash table with a certain initialezed size 
// the hash table is an array of pointers; therefore, each one is set to null
Hash::Hash(int hashTableSize){
	this->hashTableSize = hashTableSize;
	hashTable = new Word*[hashTableSize];
	for(int i = 0; i < hashTableSize; i++) {
		hashTable[i] = nullptr;
	}
	totalCountRF = 0;
}

//destructor
Hash::~Hash(){

}

// Adds a word struct into the hashtable
// if it already exists, increment text frequency (TF) value
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

// Function to check whether or not the function exists in the table
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

// function to find the pointer to the word struct and increment the TF count
void Hash::incrementCount(string word) {
	Word* item = searchTable(word);
	item->countTF++;
}

// function to add up all of the words within the hash table/text file
int Hash::getTotalNumWords() {
	int count = 0;
	Word* temp1 = hashTable[0];

	while(temp1) {
		count++;
		temp1 = temp1->next;
	}

	return count;
}

// creates a new node with the word passed in
Word* Hash::createNode(string word, Word* next){
	Word* node = new Word;
	node->word = word;
	node->next = next;
	return node;
}

// Gets the hash value to index the word struct into hash table
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

// function to search through hash table and return the pointer to the word struct
// that contains "word"
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

// function to calculate text frequency (TF) value for word
void Hash::getTF(Word *word)
{
	word->TF = (float)log(1+word->countTF);
}

// function to get inverse document frequency value for the word (IDF)
void Hash::getIDF(Word *word)
{
	word->IDF = (float)log(totalCountRF/(1+word->countIDF));
}

// function to get inverse document frequency count for each word
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

// finds and return pointer to the word struct 
// of "word"
Word* Hash::getWord(string word) {
	return searchTable(word);
}
