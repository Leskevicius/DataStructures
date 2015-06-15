/*
dynamic stack implemented using arrays
it grows when size is maxed and shrinks when size is below n/2

by Rokas Leskevicius

**requires types to have << operator overloaded for toStr() method**

*/
//#ifndef __STACK_H
//#define __STACK_H

#include <iostream>
#include <sstream>			//for toStr() method

using namespace std;

template <class T>
class stack {
private:
	int MAX_SIZE;
	int size;

	T* data;

	void grow();
	void shrink();
public:
	stack();
	~stack();

	T top();
	T pop();
	void push(T item);
	string toStr();
	bool empty();
};

//#endif

template <class T>
stack<T>::stack() {
	MAX_SIZE = 64;				//intial size of the stack
	data = new T[MAX_SIZE];	//create the array
	size = 0;					//and set the size to 0
}	

template <class T>
stack<T>::~stack() { delete data; }

template <class T>
T stack<T>::top() { return data[size - 1]; }

template <class T>
T stack<T>::pop() {
	if (size >= 64 && size <= MAX_SIZE / 2) shrink();
	return data[--size];
}

template <class T>
void stack<T>::push(T item) {
	if (size >= MAX_SIZE) grow();
	data[size++] = item;
}

template <class T>
string stack<T>::toStr() {
	stringstream ss;
	for (int i = 0; i < size; i++) {
		ss << data[i] << '\n';
	}
	return ss.str();
}

template <class T>
bool stack<T>::empty() {
	if (size <= 0)	return true;
	else			return false;
}

template <class T>
void stack<T>::grow() {
	MAX_SIZE *= 2;
	int* temp = new T[MAX_SIZE];
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}
	delete data;
	data = temp;
}

template <class T>
void stack<T>::shrink() {
	MAX_SIZE /= 2;
	int* temp = new T[MAX_SIZE];
	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}
	delete data;
	data = temp;
}

int main() {
	stack<int> s = stack<int>();
	for (int i = 0; i < 100; i++) {
		s.push(i);
		cout << s.top() << endl;
	}
	while (!s.empty()) {
		cout << s.pop() << endl;
	}
	return 0;
}