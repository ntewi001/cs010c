#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

vector<char> createVector();

template<typename T>
unsigned min_index(const vector<T> &, unsigned &);

template<typename T>
void selection_sort(vector <T> &);

template<typename T>
T getElement(const vector<T> &, const int &);

int main(){

    // unsigned int num;
    //test harness for vector of strings selection sort and min_index
    vector<string> stringVals = {"asa","bas","ka","cas"};

    cout << "testing string selection sort" << endl;

    //loop for outputting string values before
    for(unsigned int i = 0; i < stringVals.size(); ++i){
        cout << stringVals.at(i) << " ";
    }
    cout << endl;
    
    selection_sort(stringVals);

    //loop ouputing string values after sorting
    for(unsigned int i = 0; i < stringVals.size(); ++i){
        cout << stringVals.at(i) << " ";
    }
    cout << endl;
     
    //test harness for vector of ints selection sort and min_index
    vector<int> intNums = {1,5,3,0};

    //loop for outputing int values before
    for(unsigned int i = 0; i < intNums.size(); ++i){
        cout << intNums.at(i) << " ";
    }
    cout << endl;
    
    selection_sort(intNums);

    //loop ouputing int values after sorting
    for(unsigned int i = 0; i < intNums.size(); ++i){
        cout << intNums.at(i) << " ";
    }
    cout << endl;

    //test harness for getElement function
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;
        cin >> index;
        try{
            curChar = getElement(vals,index);
        }
        // if error found from out of range, catch and output error message
        catch (const out_of_range& excpt){
            cout << "out_of_range exception occured" << endl;
    }
        cout << "Element located at " << index << ": is " << curChar << endl;
    }

    

    return 0;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned &index){
    unsigned minIndex = index;
    // iterate through the vector starting at index from parameter
    for(unsigned int i = index; i < vals.size(); ++i){
        if(vals.at(i) < vals.at(minIndex)){
            minIndex = i;
        }
    }
    return minIndex;
}

template<typename T>
void selection_sort(vector <T> &vals){
    unsigned int smallestIndex = 0;
    T garbage;
    //iterate until end of the loop
    for(unsigned int i = 0; i < vals.size(); ++i){
        // find the smallest value
        smallestIndex = min_index(vals, i);
        //if victim is smaller than the current value in the index of i
        if(vals.at(smallestIndex) < vals.at(i)){
            //swap smallest value with i
            garbage = vals.at(i);
            vals.at(i) = vals.at(smallestIndex);
            vals.at(smallestIndex) = garbage;
        }
    }

}

template<typename T>
T getElement(const vector<T> &vals,const int &index){
    
    // if the index is out of range throw an exception
    if((index + 1) > static_cast<const int>(vals.size())){
        throw out_of_range("not in range");
    }
    
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    // loop pushing back a list of random values
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}
