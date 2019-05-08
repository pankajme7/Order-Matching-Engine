#include<bits/stdc++.h> 
#include "../include/tree.h"
using namespace std; 

Node *deleteTree(Node *node) {
	if(node) {
		deleteTree(node->left);
		deleteTree(node->right);
		order_book.erase(node->data->id);
		delete node->data;
		delete node;	
		return NULL;
	}

	return NULL;
}



void preOrder(Node *node) {
	if(node) {
		cout <<"(" <<node->key.first << "," << node->key.second <<")";
		preOrder(node->left);
		preOrder(node->right);
	}
}

void inOrder(Node *node) {
	if(node) {
		inOrder(node->left);
		cout <<"(" <<node->key.first << "," << node->key.second <<")";
		inOrder(node->right);
	}
}



int height(Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 





Node* newNode(Order *ord) 
{ 
	Node* node = new Node();
	node->key = make_pair(ord->price , ord->id); 
	node->data = ord; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1;

	return(node); 
} 


Node *rightRotate(Node *y) 
{ 
	Node *x = y->left; 
	Node *T2 = x->right; 	
	x->right = y; 
	y->left = T2; 	 
	y->height = max(height(y->left), height(y->right)) + 1; 
	x->height = max(height(x->left), height(x->right)) + 1; 


	return x; 
} 

 
Node *leftRotate(Node *x) 
{ 
	Node *y = x->right; 
	Node *T2 = y->left; 	
	y->left = x; 
	x->right = T2; 	
	x->height = max(height(x->left),height(x->right)) + 1; 
	y->height = max(height(y->left), height(y->right)) + 1; 

	return y; 
} 

 
int getBalance(Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 
 
Node* insert(Node* node,  pair<int,int> key , Order *data ) 
{ 
	
	if (node == NULL) 
		return(newNode(data)); 

	if (key < node->key) 
		node->left = insert(node->left, key , data); 
	else if (key > node->key) 
		node->right = insert(node->right, key, data); 

	
	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node); 

	if (balance > 1 && key < node->key) 
		return rightRotate(node); 
	if (balance < -1 && key > node->key) 
		return leftRotate(node); 
	if (balance > 1 && key > node->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
    } 
	if (balance < -1 && key < node->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	return node; 
} 

Node *minValueNode(Node *node) {
	Node *temp;
	temp = node;
	while(temp->left!= NULL){
		temp=temp->left;
	}
	return temp;	
}

Node* deleteNode(Node* root, pair<int , int> key )
{
	if (root == NULL)
	return root;


	if (key < root->key ) 
		root->left = deleteNode(root->left, key);

	else if( key > root->key )
		root->right = deleteNode(root->right, key);


	else 
	{	
		if( (root->left == NULL) || (root->right == NULL) )
		{
			order_book.erase(root->key.second);
			Node *temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;				
			}
			else {
				*root = *temp;
			}
			
			delete temp->data;
			delete temp;
		}
		else
		{						
			Node* temp = minValueNode(root->right);			
			root->key = temp->key;
			root->data = temp->data;
			root->right = deleteNode(root->right, root->key);
		}
	}


	if (root == NULL)
	return root;

	root->height = 1 + max(height(root->left),height(root->right));
	int balance = getBalance(root);

	if (balance > 1 &&	getBalance(root->left) >= 0)
	return rightRotate(root);

	if (balance > 1 &&	getBalance(root->left) < 0) { 
	root->left = leftRotate(root->left);
	return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0) 
	return leftRotate(root); 

	
	if (balance < -1 && getBalance(root->right) > 0)
	{
	root->right = rightRotate(root->right);
	return leftRotate(root);
	}


	return root;

}


Node *getHighest(Node *node) {
	Node *current = node;
	while(current->right != NULL) 
		current = current->right;
	return current;  
}

Node *getLowest(Node *node) {
	Node *current = node;
	while(current->left != NULL) 
		current = current->left;
	return current;
}

Node *getLowestFromOtherTrader(Node *node , int trader_id) {
	if (node != NULL) {
		Node *v ;
		v = NULL;
		v = getLowestFromOtherTrader(node->left,trader_id);
		if(v!=NULL)	return v;
		
		if(node->data->trader_id != trader_id) return node;
		v = getLowestFromOtherTrader(node->right, trader_id);
		
		return v;
		
	}

	return NULL;
}

Node *getHighestFromOtherTrader(Node *node , int trader_id)  {
	if(node != NULL) {
		Node *v;
		v = NULL;
		v = getHighestFromOtherTrader(node->right , trader_id);
		if(v!=NULL) return v;
		if(node->data->trader_id != trader_id) return node;
		v = getHighestFromOtherTrader(node->left , trader_id);
		return v;
	}

	return NULL;
}