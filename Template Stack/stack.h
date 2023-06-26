#pragma once

#include <iostream>
#include <string>
#include "stack.h"
#include <stdexcept>

using namespace std;

const int MAX_SIZE = 20;

template<typename T>
class stack{

 public:
    stack(){
        size = 0; // intialize stack size to 0
    }
    //add an element to the top of the stack
    void push(const T &val){
        //increment stack size 
        ++size;
        // if size is less than or equal to max size of stack
        if(size <= MAX_SIZE){
            data[size - 1] = val; //add new element to the top of the stack
        }
        //edge case if stack is full
        else{
            throw overflow_error("Called push on full stack.");
        }
    }
    //remove top element of the stack
    void pop(){
        // if stack is not empty then decrement stack size
        if(!empty()){
            --size;
        }
        // edge case if empty
        else{
            throw out_of_range("Called pop on empty stack.");
        }
    }
    //remove two items from the stack
    void pop_two(){
        // if stack size is greater than or equal to 2 then decrement by 2
        if(size >= 2){
            size -= 2;
        }
        //edge case if size is 1 then throw 
        else if(size == 1){
            throw out_of_range("Called pop_two on a stack of size 1.");
        }
        //edge case if stack is empty
        else{
            throw out_of_range("Called pop_two on a stack of size 1.");
        }
    }
    //return the top of the stack
    T top() const{
        //if stack is not empty return the top element
        if(!empty()){
            return data[size - 1];
        }
        //edge case if empty
        else{
            throw underflow_error("Called top on empty stack.");
        }
    }
    //check if stack is empty
    bool empty() const{return size == 0;}

 private:
    int size;
    T data[MAX_SIZE]; 

};