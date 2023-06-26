#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {
  
  friend class Tree;

public: 
  Node(const string &_small) : small(_small), large(""), countData(1),
                               left(nullptr), right(nullptr), parent(nullptr)
                          
  { 
  }


private:
  string small;
  string large;
  int countData;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

};

#endif