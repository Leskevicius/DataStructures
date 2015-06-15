/*
Linked List
by Rokas Leskevicius


**type used must have <<, == overloaded**

*/
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <iostream>
#include <string>
#include <sstream>			//for toStr() method

using namespace std;

template <class T>
class node {
private:
	T data;				//data to be contained in the node
	node<T>* next;		//link to the next node
public:
	node(T data);
	void insert(T);		//insert an element into linked list
	void remove(T);		//remove an element from the linked list

	T getData();
	node<T>* getNext();
};

template <class T>
class linkedList {
private:
	node<T>* head;				//the head of the linked list (first node)
public:
	linkedList();
	void insert(T);		//insert an element into linked list
	void remove(T);		//remove an element from linked list
	string toStr();			//returns a string with all its elements
};							//seperated by new lines

#endif


//***********************node methods***********************//

template <class T>
node<T>::node(T data) {		//creates a node with data specified
	this->data = data;		//and sets its next link to null
	next = NULL;
}

template <class T>
void node<T>::insert(T data) {
	if (!next) next = new node(data);	//if next link points to null, add the node here
	else next->insert(data);			//otherwise recursively go to the end of the linked list
}

template <class T>
void node<T>::remove(T data) {
	if (next) {						//if next links to a node
		if (next->data == data) {	//and next's data equals data requested
			if (next->next) {			//and if next's next pointer also points to node
				node* temp = next->next;	//same the next's next
				delete next;				//delete the data requested
				next = temp;				//and connect the linked list together
			} else {
				delete next;			//otherwise simply delete the data requested
				next = NULL;			//and set the link next to NULL
			}
		} else {					//otherwise data are not equal
			next->remove(data);		//and proceed with next node
		}
	}
}

template <class T>
T node<T>::getData() {
	return data;
}

template <class T>
node<T>* node<T>::getNext() {
	return next;
}


//************************ll methods************************//

template <class T>
linkedList<T>::linkedList() {
	head = NULL;
}

template <class T>
void linkedList<T>::insert(T data) {
	if (head) head->insert(data);	//if the head is used, use nodes insert method to insert recursively			
	else head = new node<T>(data);		//otherwise the head is null, so make the item to be added the head of linked list			
}

template <class T>
void linkedList<T>::remove(T data) {	
	if (!head) cout << "linkedList is empty." << endl;	//if head == null, list is empty
	else if (head->getData() == data) {  //otherwise see if head's data is equal to data requested
		if (!head->getNext()) {			//if head's next link is null
			delete head;			//delete the head and set it to null
			head = NULL;			
		} else {					//if head's next link is not null
			node<T> *temp = head->getNext();	//save the pointer of head's next
			delete head;				//delete head and make next the head
			head = temp;
		}
	} else head->remove(data);		//otherwise search the linked list recursively
}

template <class T>
string linkedList<T>::toStr() {
	stringstream ss;				//use string stream to go through
	node<T>* temp = head;				//the whole linked list and populate
	while (temp) {					//the stream with its elements seperated by
		ss << temp->getData() << '\n';	//new lines
		temp = temp->getNext();
	}
	string s(ss.str());
	return s;						//finally return the string of streams content
}