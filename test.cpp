#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


using namespace std;

int main()
{
	ifstream file;
	string str;
	char cstr;
	file.open("test.txt");
	getline(file,str);

	stringstream ss(str);

	ss >> cstr;

	int ASCII = (int)cstr;
	cout << ASCII << endl; ;
}