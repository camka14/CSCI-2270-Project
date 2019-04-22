#include "Header.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream mainText;
	string word;
	Stack sentStack;
	Hash wordHash(500);
	Heap sentHeap(20);
	vector<string> sentence;
	Word *wordItem;
	bool sentEnd = false;
	char letter;

	regex nonWord("[.|!|?]");
	regex wordChar("[a-zA-Z]");
	regex whiteSpace("[\\s]");
	mainText.open(argv[1]);

	Sent *newSent = new Sent;

	while(mainText.get(letter))
	{
		string letterS = "";
		letterS += letter;
		if(regex_match(letterS,nonWord))
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
		else if(regex_match(letterS,wordChar))
		{
			word += letterS;
		}
		else if(regex_match(letterS,whiteSpace))
		{
			if(word != ""){
				wordHash.addWord(word);
				newSent->sentence.push_back(word);
				word = "";
			}
		}
	}

	wordHash.getIDFCount(argv[2]);

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

	cout << "here" << endl;

	for(int i=0; i<5; i++)
	{
		Sent *sentItem =sentHeap.peek();
		for(int i=0; i<sentItem->sentence.size(); i++)
			cout << sentItem->sentence[i] << " ";
		cout << sentItem->score << endl << endl;
		sentHeap.dequeue();
	}

	
	mainText.close();
}