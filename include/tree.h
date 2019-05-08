#include<bits/stdc++.h> 
#include "order.h"
#include "trader.h"
using namespace std; 


class Node 
{ 
	public:
	pair<int , int> key;
	Order *data; 

	Node *left; 
	Node *right;

	int height; 

	Node operator = (const Node &node) {
		this->key = node.key;
		this->left = node.left;
		this->right = node.right;
		this->data =  node.data;
	}

	Node() {

	}
}; 

int height(Node *n);
Node *newNode(Order *key);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *n);
Node *insert(Node *node , pair<int, int> key , Order *o);
Node *deleteTree(Node *node) ;
Node *deleteNode(Node *node,  pair<int, int> key);
Node *getHighest(Node *node);
Node *getLowest(Node *node);
Node *getLowestFromOtherTrader(Node *node , int trader_id);
Node *getHighestFromOtherTrader(Node *node , int trader_id);
void preOrder(Node *node);
void inOrder(Node *node);