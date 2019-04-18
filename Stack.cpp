#include <iostream>
#include <string>
#include <stack>

#include "Header.hpp"

using namespace std;

Stack() {
	stack<Sent> sentStore;
}
~Stack();
bool isEmpty() {
	if(stackHead == nullptr)
		return true;
	return false;
}
void push(Sent sentence) {

}
void pop();
Sent* peek();