/*
Rokas Leskevicius
COP3530
Array implementation
Double Ended Queue [template]
*/

#ifndef TDEQUE_H
#define TDEQUE_H

#include <iostream>
#include <stdexcept>		//exceptions
#include <sstream>			//stream for toStr()

using namespace std;

template <class T>
class Deque {
private:
	T *queue;					//template array named queue that will hold the elements
	int sz;						//sz represents the current size of our queue
	int max_size;				//represents max size of the queue
	int front;					//represents where the front of our queue is
	int back;					//represents where the back of our queue is

	void grow();				//increases the maximum elements that queue can hold by 2
	void shrink();				//decreases the maximum elements that queue can hold by 2
public:
	Deque();					//constructor
	~Deque();					//destructor
	
	void push_front(T item);	//Adds an element to the front of the queue
	void push_back(T item);		//Adds an element to the back of the queue
	T pop_front();				//pops and returns an element from the front of the queue
	T pop_back();				//pops and returns an element from the end of the queue
	
	bool empty();				//returns true if the queue is empty, otherwise false
	
	int size();					//returns the current size of the queue
	
	void print_queue();			//prints the elements of the queue with some extra information
	string toStr();				//returns a string will all the elements, with new line in between
};

#endif

template <class T>
Deque<T>::Deque() {
	queue = new T[8];			//initially the queue holds up to 8 items
	sz = 0;						//sz stands for size, initially set to 0
	max_size = 8;				//max size is 8 items
	front = 0;					
	back = 0;
}

template <class T>
Deque<T>::~Deque() {
	delete[] queue;				//deallocate memory
}

template <class T>
void Deque<T>::push_front(T item) {
	if (sz == max_size) grow();     //if queue maxed out, double the capacity
	if (sz == 0) {					//initially queue is empty so we should not move the front
		queue[front] = item;	
		sz++;						//increment size
		return;
	} else if (front == 0) front = max_size;	//wrap around
	queue[--front] = item;			//add to queue
	sz++;							//increment size
}

template <class T>
void Deque<T>::push_back(T item) {
 	if (sz == max_size) grow();		//if queue maxed out, double the capacity
 	if (sz == 0) {					//initially queue is empty so we should not move the back
		queue[back] = item;
		sz++;
		return;
	} else if (back == max_size - 1) back = -1;	//if at the end of queue, wrap around to the front
	queue[++back] = item;			//add to queue
	sz++;							//increment the size						
}

template <class T>
T Deque<T>::pop_front() {
	if (sz == max_size / 4 && max_size != 8) { shrink(); }	//if queue is size max_size/4, shrink the queue
	if (sz == 0) throw out_of_range("Deque<>::pop_front(): Deque is empty.");	//Throw out of range exception if queue is empty		
	T item = queue[front];			//store content of front to variable item
	if (front == max_size - 1) front = 0;	//if we are at the end of our queue, set the front to beginning
	else front++; 					//otherwise just increment front
	sz--;
	return item;					//return the desired item
}

template <class T>
T Deque<T>::pop_back() {	
	if (sz == max_size / 4 && max_size != 8) { shrink(); }	//if queue is size max_size/4, shrink the queue
	if (sz == 0) throw out_of_range("Deque<>::pop_back(): Deque is empty.");	//Throw out of range exception if queue is empty
	T item = queue[back];			//store content of back to variable item
	if (back == 0) back = max_size - 1;				//if we are at the beginning of our queue, set the queue to the back
	else back--; 				//otherwise just decrememnt back
	sz--;
	return item;					//return desired item
}

template <class T>
bool Deque<T>::empty() {
	if (sz == 0)  return true; 		//if the size (sz) of our queue is 0, return true
	else 		  return false;		//otherwise it is not empty
}

template <class T>
int Deque<T>::size() { return sz; }	//return the size (sz) of the queue

template <class T>
void Deque<T>::grow() {
	try {
		T *temp = new T[max_size*2];	//create an array that is twice the size
		for (int i = 0; i < max_size; i++) {	//copy the contents to the temporary array
			if (front == max_size) {			//wrap around condition
				front = 0;
			}
			temp[i] = queue[front++];
		}
		front = 0;						//set front to 0
		back = max_size - 1;			//set the back to the last existing element
		queue = temp;					//point queue to the new array
		max_size *= 2;					//set max size to twice the size		
	} catch (bad_alloc &e) {
		cout << "Caught an exception: " << e.what() << endl;
	}

}

template <class T>
void Deque<T>::shrink() {
	T *temp = new T[max_size/2];	//create an array that is twice smaller in size
	for (int i = 0; i < max_size/4; i++) {	//copy the contents to the temporary array
		if (front == max_size) front = 0;	//wrap around condition 
		temp[i] = queue[front++];
	}
	front = 0;						//set front to 0
	back = ((max_size/4) -1);		//set the back to the last existing element
	queue = temp;					//point queue to the new array
	max_size /= 2;					//set max size to twice smaller
}

template <class T>
string Deque<T>::toStr() {			//This method will return a string of elements from front to back in format of "e1\ne2\ne3..."		
	ostringstream oss;				//create ostringstream
	int tempFront = front;			//make a copy of front to use for traversal	
	for (int i = 0; i < sz; i++) {		
		if (tempFront == max_size) tempFront = 0;	//if we are at the end of the queue and still have more elements, wrap around to the front
		oss << queue[tempFront] << '\n';	//load elements to the stream (Operator << MUST be implemented for the type used)			
		tempFront++;						
	}
	return oss.str();				//return the string version of the stream				
}