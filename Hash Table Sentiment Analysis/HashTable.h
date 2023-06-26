#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

 private:
	list<WordEntry> *hashTable;
	int size;

 public:
	~HashTable();
	HashTable(int);
	bool contains(const string &);
	double getAverage(const string &);
	void put(const string &, int);
 
 private:
	int computeHash(const string &);
	// rule of 3
	HashTable(const HashTable &copy); // copy constructor
	HashTable & operator=(const HashTable &copy); // copy asssingment 
};

#endif