#include "BST.hpp"
#include <iostream>

Node* BST::createNode(int data)
{
    Node *newNode = new Node;
    newNode->key = data;
    return newNode;
}

/*
Method Name: addNodeHelper
Purpose: This function will add a node with key as 'data' in the tree rooted at 'currNode'.
Call this function from addNode().
return: currNode
*/
Node* BST::addNodeHelper(Node* currNode, int data)
{
    if(currNode == nullptr){
        return createNode(data);
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key >= data){
        currNode->left = addNodeHelper(currNode->left,data);
    }
    return currNode;
}
/*
Method Name: deleteNodeHelper
Purpose: This function deletes the node with 'value' as it's key from the tree rooted at 'currNode'.
Call this function from deleteNode()
return: currNode
*/
Node* getMinValueNode(Node *currNode)
{
    if(currNode->left == nullptr){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}

Node* BST::deleteNodeHelper(Node *currNode, int value)
{
    Node *sub;
    if(currNode == nullptr)
    {
        return nullptr;
    }
    else if(value < currNode->key)
    {
        currNode->left = deleteNodeHelper(currNode->left, value);
    }
    else if(value > currNode->key)
    {
        currNode->right = deleteNodeHelper(currNode->right, value);
    }
    else
    {
        // No child
        if(currNode->left == nullptr && currNode->right == nullptr)
        {
            delete currNode;
            return nullptr;
        }
        //Only right child
        else if(currNode->left == nullptr)
        {
            sub = currNode->right;
            delete currNode;
            currNode = sub;
        }
        // Only left child
        else if(currNode->right == nullptr)
        {
            sub = currNode->left;
            delete currNode;
            currNode = sub;
        }
        // Both left and right child
        else
        {
            ///Replace with Minimum from right subtree
            sub = getMinValueNode(currNode->right);
            currNode->key = sub->key;
            currNode->right = deleteNodeHelper(currNode->right, sub->key);
        }
    }
    return currNode;
}
/*
Method Name: searchKeyHelper
Purpose: This function will search for a node with "data" as it's key in a tree rooted at 'currNode'.
Call this function from searchKey()
return: Node with "data" as it's key if found, otherwise nullptr
*/
int BST::searchKeyHelper(Node* currNode, int data)
{
    if(currNode == nullptr)
        return 0;
    else if(data > currNode->key)
        searchKeyHelper(currNode->right,data);
    else if(data < currNode->key)
        searchKeyHelper(currNode->left,data);
    else
        return currNode->key;
}

/*
Method Name: printTreeHelper
Purpose: This function will traverse the tree rooted at "currNode" in an inorder fashion and print out the node elements.
Call this function from printTree()
return: none
*/
void BST::printTreeHelper(Node* currNode)
{
    printTreeHelper(currNode->left);
        cout << currNode->key << endl;
    printTreeHelper(currNode->right);
}

/* OPTIONAL : This is just to help you visualize the tree (this function was provided in the recitation exercise)
Method Name: print2DUtilHelper
Purpose: This function will print the tree rooted at "currNode" in a 2D fashion.
Call this function from print2DUtil()
return: none
*/
void BST::print2DUtilHelper(Node *currNode, int space)
{
    // Base case
    if (currNode == nullptr)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtilHelper(currNode->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", currNode->key);

    // Process left child
    print2DUtilHelper(currNode->left, space);
}


// function to insert a node in the tree. This function calls the addNodeHelper()
void BST::addNode(int data)
{
    root = addNodeHelper(root,data);
}

// function to delete a node in the tree. This function calls the deleteNodeHelper()
void BST::deleteNode(int data)
{
    deleteNodeHelper(root,data);
}

// function to search a data in the tree. This function calls the searchKeyHelper()
// returns True if it exists otherwise False
bool BST::searchKey(int value)
{
    if(searchKeyHelper(root,value));
}

// function to print the tree (in an inorder fashion). This function calls the printTreeHelper()
void BST::printTree()
{
    printTreeHelper(root);
}

/*
	constructor
	Purpose: perform all operations necessary to instantiate a class object
	return: none
	*/

// default constructor
BST::BST()
{

}

// parameterized constructor. It will create the root and put the 'data' in the root
BST::BST(int data)
{

}

/*
	destructor
	Purpose: free all resources that the object has acquired
	return: none
	*/

// This calls the destroyNode().
BST::~BST()
{

}

// Prints the tree in a 2D fashion. This function calls print2DUtilHelper().
void BST::print2DUtil(int space)
{
    print2DUtilHelper(root, space);
}

int sumRangeHelp(Node *currNode, int min, int max, int sum, bool foundMin)
{
    bool rightSearch = false;
    bool leftSearch = false;
    if(!currNode){
        return sum;
    }

    if(currNode->key > min && !foundMin){
        leftSearch = true;
        sum = sumRangeHelp(currNode->left,min,max,sum,foundMin);
    }
    else if(currNode->key < min && !foundMin){
        rightSearch = true;
        sum = sumRangeHelp(currNode->right,min,max,sum,foundMin);
    }
    foundMin = true;

    if(currNode->key >= min && currNode->key <= max){
        sum += currNode->key;
    }
    if(currNode->left && !leftSearch)
        sum = sumRangeHelp(currNode->left,min,max,sum,foundMin);
    if(currNode->key < max && !rightSearch)
        sum = sumRangeHelp(currNode->right,min,max,sum,foundMin);
    return sum;
}

int BST::sumRange(int min, int max)
{
    int sum = 0;
    bool foundMin = false;
    Node* temp = root;
    sum = sumRangeHelp(temp,min,max,sum,foundMin);
    return sum;
}