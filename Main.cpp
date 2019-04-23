#include "Header.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream mainText;
	string word;
	string mainFileName;
	string refFileName = "RefDoc.txt";
	string input;
	string output;
	Stack sentStack;
	Hash wordHash(500);
	Heap sentHeap(20);
	vector<string> sentence;
	Word *wordItem;
	bool sentEnd = false;
	char letter;
	int count = 0;

	cout << "=============================================" << endl;
	cout << "   Please input the text file to summarize   " << endl;
	cout << "=============================================" << endl << endl;
	getline(cin,mainFileName);
	do{
		mainText.open(mainFileName);
		if(!mainText.is_open()){
			cout << "Error opening file: Please input existing file name" << endl;
			getline(cin,mainFileName);
		}
	}while(!mainText.is_open());
	cout << endl;
	cout << "=============================================" << endl;
	cout << "Would you like to use a custom refrence file?" << endl << "Y/N" << endl;
	cout << "=============================================" << endl << endl;
	while(input != "Y" && input != "y" && input != "N" && input != "n")
	{
		getline(cin,input);
		cout << endl;
		if(input == "Y" || input == "y"){
			cout << "=============================================" << endl;
			cout << "  Please input the refrence text file name   " << endl;
			cout << "=============================================" << endl << endl;
			getline(cin,refFileName);
		}else if(input != "N" && input != "n"){
			cout << input << endl;
			cout << "Please input Y or N" << endl;
		}else
			cout << "Using default refrence file" << endl << endl;
	}
	cout << "=============================================" << endl;
	cout << "  How many sentences do you want to output?  " << endl;
	cout << "=============================================" << endl << endl;
	
	getline(cin,output);
	cout << endl;

	cout << "=============================================" << endl;
	cout << "Please Wait:" << endl;
	cout << "Processing Text File..." << endl;

	regex nonWord("[.|!|?]");
	regex wordChar("[a-zA-Z||\\d]");
	regex whiteSpace("[\\s]");

	Sent *newSent = new Sent;

	while(mainText.get(letter))
	{
		string letterS = "";
		letterS+= letter;
		if(regex_match(letterS,nonWord))
		{
			if(word != ""){
				wordHash.addWord(word);
				newSent->sentence.push_back(word);
				word = "";
				count++;
				newSent->num = count;
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

	cout << "Processing refrence file..." << endl;
	cout << "=============================================" << endl;
	cout << endl;

	wordHash.getIDFCount(refFileName);

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
		sentStack.pop();
		sentHeap.enqueue(sentItem);
	}

	cout << "Here are your top " << output << " sentences:" << endl << endl;
	for(int i=0; i<stoi(output); i++)
	{
		Sent *sentItem = sentHeap.peek();
		cout << "Sentence # " << sentItem->num << endl << endl;
		for(int i=0; i<sentItem->sentence.size(); i++)
			cout << sentItem->sentence[i] << " ";
		cout << endl << endl;
		sentHeap.dequeue();
	}

	
	mainText.close();

	cout << "=============================================" << endl;
	cout << "           Press Enter to Close            " << endl;
	cout << "=============================================" << endl << endl;
	getline(cin,input);
}