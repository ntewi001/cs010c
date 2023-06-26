#include <iostream>
#include <string>
#include "IntList.h"

using namespace std;

int main(){
    IntList newList;
    newList.push_front(3);
    cout << newList;
    newList.pop_front();
    cout << newList;
    return 0;
}