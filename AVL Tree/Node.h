#pragma once

#include <iostream>
using namespace std;

class Node{
 public:
    friend class AVLTree;
    Node(const string &_data) : left(nullptr), right(nullptr), parent(nullptr), data(_data)
    {

    }
 private:
    Node* left;
    Node* right;
    Node* parent;
    string data;

};