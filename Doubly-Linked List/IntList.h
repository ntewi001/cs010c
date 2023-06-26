#pragma once

#include <iostream>
#include <string>

using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList{
 public:
    IntList() 
    : dummyHead(new IntNode(0)), dummyTail(new IntNode(0))
    {
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }
    ~IntList();
    void push_front(int);
    void pop_front();
    void push_back(int);
    void pop_back();
    bool empty() const{return dummyHead->next == dummyTail;}
    friend ostream & operator<<(ostream &,const IntList &);
    void printReverse() const;

 private:
    IntNode* dummyHead;
    IntNode* dummyTail;
    IntList(const IntList &copy);
    IntList & operator=(const IntList &);
};