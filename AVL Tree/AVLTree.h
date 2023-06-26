#pragma once
#include <iostream>
#include "Node.h"

using namespace std;


class AVLTree{
 public:
    AVLTree() : root(nullptr)
    {
    }
    
    void insert(const string &);
    void printBalanceFactors();
    void visualizeTree(const string &);

 private:
    Node* root;
    void rotate(Node *);
    void rotateLeft(Node *);
    void rotateRight(Node *);
    void replaceChild(Node* , Node* , Node* );
    void setChild(Node *, const string &, Node* );
    int getBalance(Node* curr){return (height(curr->left) - height(curr->right));}
    void insert(const string &key, Node* curr);
    void printBalanceFactors(Node *);
    int height(Node *);
    void visualizeTree(ofstream &, Node *);




};