#include "Header.hpp"

Stack::Stack()
{
	stackHead = NULL;
}

Stack::~Stack()
{
	while(!isEmpty())
	{
		pop();
	}
}

bool Stack::isEmpty()
{
	if(stackHead == NULL)
		return true;
	else
		return false;
}

void Stack::push(vector<string> sentence)
{
	Sent *temp = new Sent();
	temp->sentence = sentence;
	temp->next = stackHead;
	stackHead = temp;
}

void Stack::pop()
{
	if(!isEmpty()){
		Sent *temp;
		temp = stackHead;
		stackHead = stackHead->next;
		delete temp;
	}else{
		cout << "Stack empty, cannot pop an item." << endl;
	}
}

Sent* Stack::peek()
{
	if(!isEmpty()){
		return stackHead;
	}else{
		cout << "Stack empty, cannot peek." << endl;
		return NULL;
	}
}
