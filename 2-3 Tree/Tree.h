#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( ) : root(nullptr) 
  {
  }
  ~Tree( );
  Tree(const Tree &copy) : root(copy.root)
  {
  }
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void preOrder(Node *) const;
  void postOrder(Node *) const;
  void inOrder(Node *) const;
  void insert(const string &key, Node* curr);
  void TreeSplit(Node* curr, const string &key);
  void remove(const string &, Node *);
  bool search(const string &key, const Node* curr) const;
  Node* searchNode(const string &key, Node* curr) ;
  void destructor(Node*);
};

#endif