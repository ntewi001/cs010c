#include "IntList.h"
#include <iostream>

ostream & operator<<(ostream &out,const IntList &rhs){
    if(!rhs.empty()){
        IntNode *curr = rhs.dummyHead->next;
        //iterate through the list until it reaches the dummy tail node
        while(curr != rhs.dummyTail){
            if(curr->next != rhs.dummyTail){
                out << curr->data << " ";
            }
            else{
                out << curr->data;
            }
            curr = curr->next;
        }
    }
    else{
    }
    return out;
}

IntList::~IntList(){
    //edge case if not empty
    if(!empty()){
        IntNode *curr = dummyHead;
        // while the dummyH
        while(curr != dummyTail){
            dummyHead->next = curr->next;
            curr->next->prev = dummyHead;
            delete curr;
            curr = curr->next;
        }
        delete dummyTail;
    }
    
}

void IntList::printReverse() const{
    if(!empty()){
        IntNode *curr = dummyTail->prev;
        // keeps iterating till the dummyTail's prev pointer is dummyHead
        while(curr != dummyHead){
            // edge case to not print newline or space at the end
            if(curr->prev != dummyHead){
                cout << curr->data << " ";
            }
            else{
                cout << curr->data;
            }
            curr = curr->prev;
        }

    }
    else{
    }
}


void IntList::push_front(int value){
    IntNode *victim = new IntNode(value);
    if(!empty()){
        //set the node after head's prev to the inserted node
        dummyHead->next->prev = victim;
        // make inserted node's next original head's next 
        victim->next = dummyHead->next;
        dummyHead->next = victim;
        victim->prev = dummyHead;
    }
    else{
        // if empty list then make it a node between head and tail 
        dummyHead->next = victim;
        dummyTail->prev = victim;
        victim->next = dummyTail;
        victim->prev = dummyHead;
    }
}

void IntList::pop_front(){
    //edge case if list is not empty
    if(!empty()){
        IntNode *sucNode = dummyHead->next->next;
        IntNode *victim = dummyHead->next;
        //unlink by setting head's next to the succesion node 
        dummyHead->next = sucNode;
        sucNode->prev = dummyHead;
        //delete victim and set pointer to null to avoid dangling pointer
        delete victim;
        victim = nullptr;
    }
    else{
        throw runtime_error("oops");
    }
}
void IntList::push_back(int value){
    IntNode *victim = new IntNode(value);
    //edge case if not empty
    if(!empty()){
        IntNode *predNode = dummyTail->prev;
        //set predecessor node's next to the node we are trying to insert
        predNode->next = victim;
        victim->prev = predNode;
        //make the victim node the last node
        dummyTail->prev = victim;
        victim->next = dummyTail; 
    }
    else{
        dummyHead->next = victim;
        dummyTail->prev = victim;
        victim->next = dummyTail;
        victim->prev = dummyHead;
    }
}
void IntList::pop_back(){
    if(!empty()){
        IntNode *predNode = dummyTail->prev;
        //unlink the node before tail
        dummyTail->prev = predNode->prev;
        predNode->prev->next = dummyTail;
        //delete the node and set the pointer to null to avoid dangling
        delete predNode;
        predNode = nullptr;

    }
    else{
        throw runtime_error("oops");
    }
}
