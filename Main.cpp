#include "Header.hpp"

using namespace std;

float getIDF(char refCorpus, string word);
float getTF();

int main(int argc, char const *argv[])
{
	ifstream mainText;
	ifstream refText;
	string refCorpus;
	string word;
	Stack sentStack;
	// Hash wordHash;
	// Heap sentHeap;
	regex compare("[\\S]+[.|!|?|\\n]");
	stringstream strStream;
	stringstream fixed;
	bool sentEnd = false;

	mainText.open(argv[1]);
	refText.open(argv[2]);

	strStream << refText.rdbuf();

	refCorpus = strStream.str();

	Sent *sent = new Sent();

	while(getline(mainText,word,' '))
	{
		if(regex_match(word,compare)){
			cout << word << endl;
			sentEnd = true;
		}
		word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
		// wordHash.addWord(word);
		sent->sentence.push_back(word);
		if(sentEnd){
			// for(int i=0; i<sent->sentence.size(); i++)
			// 	cout << sent->sentence[i] << " ";
			// cout << endl << endl;
			sentEnd = false;
			Sent *sent = new Sent();
		}
	}

	
	mainText.close();
}