#include <regex>
#include <iostream>
using namespace std;

int main()
{
	regex reg("[a-zA-Z]");
	char s = 's';
	cout << regex_match(&s, reg);

}