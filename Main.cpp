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

	regex compare("[\\S]+[.|!|?|\\n]");
	mainText.open(argv[1]);
	refText.open(argv[2]);

	strStream << refText.rdbuf();

	refCorpus = strStream.str();

	while(getline(mainText,word,' '))
	{
		if(regex_match(word,compare)){
			cout << word << endl;
			sentEnd = true;
		}
		word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
		// wordHash.addWord(word);
		sentence.push_back(word);
		if(sentEnd){
			sentStack.push(sentence);
			sentEnd = false;
			sentence.clear();
		}
	}

	while(!sentStack.isEmpty())
	{
		Sent *sentItem = sentStack.peek();
		sentStack.pop();

		for(int i=0; i<sentItem->sentence.size(); i++)
		{
			// wordItem = wordHash.getWord(sentItem->sentence[i]);

			if(wordItem->TF == 0){
				getTF(wordItem);
				getIDF(refCorpus, wordItem);
			}
			sentItem->score += wordItem->TF+wordItem->IDF;
		}
		// sentHeap.enqueue(sentItem);
	}


	
	mainText.close();
}