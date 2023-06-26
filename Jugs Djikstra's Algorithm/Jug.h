#pragma once
#include <iostream>
#include <vector>
using namespace std;


struct Vertex {
    int A;
    int B;
    int id;
    int distance;
    Vertex* predV;
    vector<int> newStateAfterAction; //Adjacency list 

    Vertex(int A, int B, int id)
      : A(A),
        B(B),
        id(id),
        newStateAfterAction(6, -1) {}
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        // ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
        void dijkstraPath(Vertex &);
        int getWeight(int )const;
    private:
        int findInGraph(int , int , vector<int>& );
        void showState(int ) const;
        void printGraph() const;

        //anything else you need
        int capacityA;
        int capacityB;
        int goalCapacity;
        int costFillA;
        int costFillB;
        int costEmptyA;
        int costEmptyB;
        int costPourAB;
        int costPourBA;
        string solution;
        bool valid = true;
        vector<Vertex> graph;
};

