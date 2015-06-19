/*
Rokas Leskevicius

Binary Search Tree (string key and string value)
*/
#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <sstream>
#include <string>



//***********************Node Class Declaration***********************//



class Node {
private:
	std::string value;		//value
	std::string key;		//key
	Node* right;			//right subtree
	Node* left;				//left subtree
public:
	Node(std::string value, std::string key);		//constructor
	void insert(std::string key, std::string value);	//add new data
	bool find(std::string key, std::string *value);		//search for specific data
	std::string getValue();
	Node* Delete(Node* root, std::string key, bool* success);
	Node* findMin(Node* root);
	void inOrder(Node* root, std::stringstream* ss);
	void deleteTree(Node*& root);
};



//*******************Binary Search Tree Declaration*******************//



class bTree {
private:
	Node* root;					//root node of the Binary Search Tree
public:
	bTree();						//constructor
	~bTree();						//destructor
	void insert(std::string key, std::string value);//add new data
	bool find(std::string key, std::string *value);	//search for specific data
	std::string toStr();
	bool delete_key(std::string key);
	void deleteTree(Node* root);
};

#endif

//*************************Node Class Methods************************//



Node::Node(std::string value, std::string key) {
	this->value = value;//store the data
	this->key = key;  	//store key
	right = NULL;		//set right to empty
	left = NULL;		//set left to empty
}

void Node::insert(std::string key, std::string value) {
	if (this->key == key) {					//no duplicates allowed in this implementation
		std::cout << "ERROR: No duplicates allowed." << std::endl;
	} else if (this->key > key) {			//if data is > new data
		if (left == NULL) {					//if left child is empty
			//std::cout << "inserted: " << key << " to the left of " << this->key << std::endl;
			left = new Node(value, key);	//add the new data here
		} else {							//otherwise
			left->insert(key, value);		//recursively call the left node
		}
	} else if (this->key < key) {			//if data is < new data
		if (right == NULL) {				//if right child is empty
			//std::cout << "inserted: " << key << " to the right of " << this->key << std::endl;
			right = new Node(value, key);	//add the new data here
		} else {							//otherwise
			right->insert(key, value);	//recursively call the right node
		}
	}
}

bool Node::find(std::string key, std::string *value) {	
	//std::cout << "key searched for: " << key << " key found: " << this->key << std::endl;
	if (this->key == key) {	 			//If the data is equal
		*value = this->value;
		return true;					//return true
	} else if (this->key > key) {		//if the key searched for is less than current key
		if (left == NULL) {				//and if the left subtree is empty
			return false;				//return false
		} else {						//otherwise
			return left->find(key, value);	//examine the left subtree in the same manner
		}
	}  else if (this->key < key) {		//otherwise if the key searched for is bigger than currect key
		if (right == NULL) {			//and if the right subtree is empty
			return false;				//return false
		} else {						//otherwise
			return right->find(key, value);	//examine the right subtree in t he same manner
		}
	}
	return false;						//if all fails, return false
}

std::string Node::getValue() {
	return value.append("_").append(key);
}

Node* Node::Delete(Node* root, std::string key, bool* success) {
	if (!root) {
		return NULL;
	}
	if (key < root->key) root->left = Delete(root->left, key, success);
	else if (key > root->key) root->right = Delete(root->right, key, success);
	else if (key == root->key) {
		//case 1 : there is no children to the root
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
			*success = true;
		//case 2 : there is only one child to the root
		} else if (root->left == NULL) {
			Node* temp = root;
			root = temp->right;
			delete temp;
			*success = true;
		} else if (root->right == NULL) {
			Node* temp = root;
			root = temp->left;
			delete temp;
			*success = true;
		//case 2 : There are two childs to the root ( :[ )
		} else {
			Node* temp = findMin(root->right);
			root->key = temp->key;
			root->value = temp->value;	
			root->right = Delete(root->right, root->key, success);
		}
	}
	return root;
}

Node* Node::findMin(Node* root) {
	if (root->left == NULL) return root;
	else return findMin(root->left);
}

void Node::inOrder(Node* root, std::stringstream *ss) {
	if (!root) return;
	inOrder(root->left, ss);
	*ss << root->key << "\n";
	inOrder(root->right, ss); 
}

void Node::deleteTree(Node*& root) {
	if (root) {
		if (root->left) {
			deleteTree(root->left);
		}
		if (root->right) {
			deleteTree(root->right);
		}
		delete root;
		root = NULL;
	}
}



//*************************bTree class methods*************************//



bTree::bTree() {
	root = NULL;	//set root to empty
}

bTree::~bTree() {
	root->deleteTree(root);
}

void bTree::insert(std::string key, std::string value) {
	if (root == NULL)  root = new Node(value, key);  //if the root is empty, add it here
	else  root->insert(key, value); 					//otherwise call the Nodes method for adding
}

bool bTree::find(std::string key, std::string *value) {
	if (root == NULL) { return false; }		//if the root is empty, its a miss
	else  return root->find(key, value); 	//otherwise examine the rest of the tree
}

bool bTree::delete_key(std::string key) {
	if (root == NULL) return false;
	bool success = false;
	root->Delete(root, key, &success);
	if (success) return true;
	else return false;
}

std::string bTree::toStr() {
	if (!root) return "The tree is empty.";
	else {
		std::stringstream ss;
		root->inOrder(root, &ss);
		std::string inOrder(ss.str());
		return inOrder;
	}
}
