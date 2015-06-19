//hash table for strings    5520637
#include <iostream>
#include <list>  //acts like a linked list for chaining
#include <vector>	//acts like an array
#include <algorithm>	//for find()

using namespace std;

class HashTable {
private:
	int hashCode(string s);			//function that translates a string into hash code
	vector< list<string> > ht;		//array like structure to hold lists (chains)
	int n;							//the how many entries to be stored
public:
	HashTable(int n);				//constructor
	void insert(string s);			//insert an entry into a hash table
	void search(string s);			//search for an entry in the hash table
};

HashTable::HashTable(int N) {			
	if (N%2 == 0) n = N+1;			//first two lines are to make sure that size of the table is odd
	else n = N;						//that way its modulo odd number. Ensures better distribution of entries
	for (int i = 0; i < n; i++) {	//in the buckets
		list<string> chain;			// populate the vector with lists ( array with link-lists )
		ht.push_back(chain);
	}
}

int HashTable::hashCode(string s) {	//hash function
	int hash = 0;						
	int length = s.length();			//compute length before 'for' loop to prevent recalculation of s.length()
	for (int i = 0; i < length; i++) {
		hash = (31 * hash + (int)s.at(i)) % n; 	//I used 31 because it is a small prime number, better bucket distribution.
	}
	return hash;
}

void HashTable::insert(string s) {	//insert function
	int index = hashCode(s);		//compute the hash code
	ht[index].push_back(s);			//place appropriately
}

void HashTable::search(string s) {	//search function
	int index = hashCode(s);
	if (ht[index].empty()) {		//if empty, its a miss
		cout << "No" << endl;
		return;
	}
 	list<string>::iterator find = std::find(ht[index].begin(), ht[index].end(), s); //search for string s in the chain
 	if (find != ht[index].end()) { // if not at the end, -> its a hit
 		cout << "Yes" << endl;
 	}
 	else {
 		cout << "No" << endl;		// else its a miss
 	}
}

/*
int main() {						//main function that reads the input as requested
	int n, op;						//n = entries, op is 0-2
	cin >> n;

	HashTable ht = HashTable(n);	

	while (true) {
		cin >> op;
		if (op == 0) break;			//exit if op = 0
		else if (op == 1) {			//add entry if op = 1
			string entry;
			cin >> entry;
			ht.insert(entry);
		} else if (op == 2) {		//search entry if op = 2
			string search;
			cin >> search;
			ht.search(search);
		}
	}
	return 0;
}
*/