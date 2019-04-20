#include "Header.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream mainText;
	ifstream refText;
	string refCorpus;
	string word;
	Stack sentStack;
	Hash wordHash(500);
	Heap sentHeap(20);
	stringstream strStream;
	vector<string> sentence;
	Word *wordItem;
	bool sentEnd = false;
	char letter;

	regex nonWord("[.|!|?]");
	regex wordChar("[a-zA-Z]");
	regex whiteSpace("[\\s]");
	mainText.open(argv[1]);
	refText.open(argv[2]);

	strStream << refText.rdbuf();

	refCorpus = strStream.str();

	Sent *newSent = new Sent;

	while(mainText.get(letter))
	{
		if(regex_match(&letter,nonWord))
		{
			if(word != ""){
				wordHash.addWord(word);
				newSent->sentence.push_back(word);
				word = "";

				sentStack.push(newSent);
				sentEnd = false;
				newSent = new Sent;
			}
			sentEnd = true;
		}
		else if(regex_match(&letter,wordChar))
		{
			word += letter;
		}
		else if(regex_match(&letter,whiteSpace))
		{
			if(word != ""){
				wordHash.addWord(word);
				newSent->sentence.push_back(word);
				word = "";
			}
		}
	}

	wordHash.getIDFCount(refCorpus);

	while(!sentStack.isEmpty())
	{
		Sent *sentItem = sentStack.peek();
		for(int i=0; i<sentItem->sentence.size(); i++)
		{
			wordItem = wordHash.getWord(sentItem->sentence[i]);
			if(wordItem->TF == 0){
				wordHash.getTF(wordItem);
				wordHash.getIDF(wordItem);
			}
			sentItem->score += wordItem->TF*wordItem->IDF;
		}
		sentHeap.enqueue(sentItem);
		sentStack.pop();
	}


	
	mainText.close();
}