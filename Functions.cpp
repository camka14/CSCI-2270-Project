#include "Header.hpp"

void getIDFCount(string refCorpus)
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

void getIDF(string word)
{
	Word *wordItem = searchTable(word);
	wordItem.IDF = log(totalCount/wordItem.countIDF);
}

void getTF(Word *word)
{
	word.TF = log(1+word.countTF);
}