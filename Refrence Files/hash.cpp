// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

// TODO Complete this function
//function to search
node* HashTable::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //TODO: Search the list at that specific index and return the node if found
    node *temp = table[index];
    while(temp)
    {
        if(temp->key == key)
            return temp;
        else
            temp = temp->next;
    }
    return nullptr;
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key)
{
    if(!searchItem(key))
    {
        int index = hashFunction(key);
        if(!table[index])
            table[index] = createNode(key,nullptr);
        else{
            node *temp = table[index];
            while(temp->next)
                temp = temp->next;
            temp->next = createNode(key,nullptr);
            cout << temp->key <<" "<< temp->next->key << endl;
        }
     }
    else{
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }

}

//TODO Complete this function
// function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";

        node *temp = table[i];
        while(temp)
        {
            cout << " " << temp->key << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

 }
