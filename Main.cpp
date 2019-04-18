#include "Header.hpp"

using namespace std;

float getIDF(char refCorpus, string word);
float getTF();

int main(int argc, char const *argv[])
{
	ifstream mainText;
	ifstream refText;
	string refCorpus;
	// Stack sentStack;
	// Hash wordHash;
	// Heap sentHeap;
	string word;
	regex compare("[\\S]+[.|!|?]");
	string sentence;
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
			sentEnd = true;
		}
		word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
		sent->sentence.push_back(word);
		if(sentEnd){
			// add to stack
			cout << sentence << endl;
			sentEnd = false;
			delete sent;
			Sent *sent = new Sent();
		}
		cout << word << endl;
	}
	mainText.close();
}