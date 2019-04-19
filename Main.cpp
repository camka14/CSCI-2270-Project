#include "Header.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream mainText;
	ifstream refText;
	string refCorpus;
	string word;
	Stack sentStack;
	// Hash wordHash;
	// Heap sentHeap;
	stringstream strStream;
	stringstream fixed;
	vector<string> sentence;
	Word *wordItem;
	bool sentEnd = false;

	regex compare("[\\S]+[.|!|?|\\t]");
	mainText.open(argv[1]);
	refText.open(argv[2]);

	strStream << refText.rdbuf();

	refCorpus = strStream.str();

	Sent *newSent = new Sent;

	while(getline(mainText,word,' '))
	{
		if(regex_match(word,compare)){
			sentEnd = true;
		}
		word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
		// wordHash.addWord(word);
		newSent->sentence.push_back(word);
		if(sentEnd){
			cout << endl << endl;
			sentStack.push(newSent);
			sentEnd = false;
			newSent = new Sent;
		}
	}

	while(!sentStack.isEmpty())
	{
		Sent *sentItem = sentStack.peek();
		sentStack.pop();

		if(sentStack.isEmpty())
			cout << endl << endl <<"true"<< endl<< endl;

		for(int i=0; i<sentItem->sentence.size(); i++)
		{
			// cout << sentItem->sentence[i] << " ";
			// wordItem = wordHash.getWord(sentItem->sentence[i]);
			if(wordItem->TF == 0){
				getTF(wordItem);
				getIDF(refCorpus, wordItem);
			}
			sentItem->score += wordItem->TF+wordItem->IDF;
		}
		// cout << endl << endl;
		// sentHeap.enqueue(sentItem);
	}


	
	mainText.close();
}