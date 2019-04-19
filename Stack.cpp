#include "Header.hpp"

Stack::Stack()
{
	stackHead = nullptr;
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
	if(stackHead == nullptr){
		cout << "true" << endl;
		return true;
	}
	else{
		cout << "false" << endl;
		return false;
	}
}

void Stack::push(Sent *sentence)
{
	sentence->next = stackHead;
	stackHead = sentence;
}

void Stack::pop()
{
	if(!isEmpty()){
		Sent *temp = stackHead;
		stackHead = stackHead->next;
		delete temp;
	}else{
		cout << "Stack empty, cannot pop an item." << endl;
	}
}

Sent* Stack::peek()
{
	if(!isEmpty()){
		for(int i=0; i<stackHead->sentence.size(); i++)
		{
			cout << stackHead->sentence[i] << " ";
		}
		cout << endl << endl;
		return stackHead;
	}else{
		cout << "Stack empty, cannot peek." << endl;
		return NULL;
	}
}
