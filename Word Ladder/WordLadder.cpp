#include <iostream>
#include <fstream>
#include <vector>
#include "WordLadder.h"

using namespace std;

WordLadder(const string &fileName){
    ifstraam inFS

    inFS.open(fileName);

    if(!inFS.is_open()){
        cout << "Error opening " << fileName << ".txt" << endl;
        return;
    }

    string currWord; 
    while(inFS >> currWord){
        if(currWord.size() > 5){
            cout << "Error: More than 5 letters" << endl;
            return;
        }
        dict.push_back(currWord);
    }


}
