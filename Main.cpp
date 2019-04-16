#include "Header.hpp"
// #include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream file;
	Stack sentStack;
	Hash wordHash;
	Heap sentHeap;
	string stringLine;
	int count=0;

	file.open(argv[1]);

	string word;
	string sentence;

	char* tok = strtok
}