/*
Linked List
by Rokas Leskevicius


**type used must have << overloaded**

*/
//#ifndef __LINKEDLIST_H
//#define __LINKEDLIST_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class node {
friend class linkedList;
private:
	int data;
	node* next;
public:
	node(int data);
	void insert(int);
	void remove(int);
};

class linkedList {
private:
	node* head;
public:
	linkedList();
	void insert(int);
	void remove(int);
	string toStr();
};

//#endif

//***********************node methods***********************//
node::node(int data) {
	this->data = data;
	next = NULL;
}

void node::insert(int data) {
	if (!next) next = new node(data);
	else next->insert(data);
}

void node::remove(int data) {
	if (next) {
		if (next->data == data) {
			if (next->next) {
				node* temp = next->next;
				delete next;
				next = temp;
			} else {
				delete next;
				next = NULL;
			}
		} else {
			next->remove(data);
		}
	}
}


//************************ll methods************************//
linkedList::linkedList() {
	head = NULL;
}

void linkedList::insert(int data) {
	if (!head) head->insert(data);
	else head = new node(data);
}

void linkedList::remove(int data) {
	if (!head) cout << "linkedList is empty." << endl;
	else if (head->data == data) {
		if (!head->next) {
			delete head;
			head = NULL;
		} else {
			node *temp = head->next;
			delete head;
			head = temp;
		}
	} else head->remove(data);
}

string linkedList::toStr() {
	stringstream ss;
	node* temp = head;
	while (temp) {
		ss << temp->data << '\n';
		temp = temp->next;
	}
	string s(ss.str());
	return s;
}

int main() {
	linkedList ll = linkedList();
	for (int i = 0; i < 2; i++) {
		ll.insert(i);
	}
	//cout << ll.toStr();


	return 0;
}