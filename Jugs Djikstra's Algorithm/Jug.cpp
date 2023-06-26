#include <iostream>
#include "Jug.h"
#include <stack>
#include <queue>
#include <sstream>
#include <climits>
using namespace std;

Jug::Jug(int Ca, int Cb, int N,int cfA,int cfB,int ceA,int ceB, int cpAB,int cpBA) {
    capacityA = Ca;
    capacityB = Cb;
    goalCapacity = N;
    costFillA = cfA;
    costFillB = cfB;
    costEmptyA = ceA;
    costEmptyB = ceB;
    costPourAB = cpAB;
    costPourBA = cpBA;
    if ((capacityA < 0 ) || (capacityB < 0) || (costFillA < 0) || (costFillB < 0) || (costEmptyA < 0) || (costEmptyB < 0) || (costPourAB < 0) || (costPourBA < 0)) { //Checks for negative values
        valid = false;
        return;
    }
    if (capacityA > capacityB) { //Checks if cA <= cB condition is invalid 
        valid = false;
        return;
    }
    if (goalCapacity >= capacityB) { //Checks if N <= cB condition is invalid
        valid = false;
        return;
    }
    if (capacityB > 1000) { //Checks if cB <= 1000 condition is invalid
        valid = false;
        return;
    }

    vector<int> unfinishedNodes;
    findInGraph(0, 0, unfinishedNodes);

    while(unfinishedNodes.size() > 0) {
      // Get an unfinished node
      int id = unfinishedNodes.back();
      unfinishedNodes.pop_back();

      
      // This state has a current A and B value
      int A = graph[id].A;
      int B = graph[id].B;
      // State after we fill up the A jug
      int fillA = findInGraph(capacityA, B, unfinishedNodes);

      // After filling the B jug
      int fillB = findInGraph(A, capacityB, unfinishedNodes);

      // After emptying the A jug
      int emptyA = findInGraph(0, B, unfinishedNodes);

      // After emptying the B jug
      int emptyB = findInGraph(A, 0, unfinishedNodes);

      // After pouring A into B
      int roomInB = capacityB - B;
      int poursize = min(A, roomInB);
      int pourAToB = findInGraph(A-poursize, B+poursize, unfinishedNodes);

      // After pouring B into A
      int roomInA = capacityA - A;
      poursize = min(B, roomInA);
      int pourBToA = findInGraph(A+poursize, B-poursize, unfinishedNodes);

      // Now we can set the six outedges for this vertex
      graph[id].newStateAfterAction[0] = fillA;
      graph[id].newStateAfterAction[1] = fillB;
      graph[id].newStateAfterAction[2] = emptyA;
      graph[id].newStateAfterAction[3] = emptyB;
      graph[id].newStateAfterAction[4] = pourAToB;
      graph[id].newStateAfterAction[5] = pourBToA;

      // The graph may now has some new unfinished vertices in it.
    }
} 

int Jug::findInGraph(int A, int B, vector<int>& unfinishedVertices) { 
    for (unsigned int i = 0; i < graph.size(); ++i) { //Loops through graph to find A:B combination
        if ((graph[i].A == A) && (graph[i].B == B)) { //Returns index of A:B combination
            return i;
        }
    }

    //New combination and adds to graph
    int id = graph.size();
    unfinishedVertices.push_back(id);
    graph.push_back(Vertex(A, B, id) );
    return id;
}

void Jug::showState(int i) const {
    cout << '\t' << i;
    if (i != -1) { //Prints out capacity of bucket A and B at index (helper function for printGraph)
        cout << '(' << graph[i].A << ',' << graph[i].B << ')';
    }
}


void Jug::printGraph() const {
    cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA" << endl;
    for (const auto& v : graph) { //Loops through graph and displays in readable form
        //Displays change in capacity A and B after each action
        cout << v.id << "\t(" << v.A << ',' << v.B << ")";
        showState(v.newStateAfterAction[0]);
        showState(v.newStateAfterAction[1]);
        showState(v.newStateAfterAction[2]);
        showState(v.newStateAfterAction[3]);
        showState(v.newStateAfterAction[4]);
        showState(v.newStateAfterAction[5]);
        cout << endl;
    }
}

void Jug::dijkstraPath(Vertex &start){
    queue<Vertex*> unfinishedQ;
    for(unsigned int i = 0; i < graph.size(); ++i){
        graph.at(i).distance = INT_MAX;
        graph.at(i).predV = nullptr;
    }

    start.distance = 0;
    unfinishedQ.push(&start);
    int otherPath;
    Vertex* otherVertices;
    Vertex* curr;
    int edgeWeight;
    int newState;
    while (!unfinishedQ.empty()) { //if empty, start at curr and pop it off the queue
        curr = unfinishedQ.front();
        unfinishedQ.pop();

        for (unsigned int i = 0; i < curr->newStateAfterAction.size(); i++) { //Loops over all possible actions
            newState = curr->newStateAfterAction[i];
            if (newState != -1) { //find edge weight
                otherVertices = &graph.at(newState);
                edgeWeight = getWeight(i); 
                otherPath = curr->distance + edgeWeight;

                if (otherPath < otherVertices->distance) { //change othervertices if path is shorter
                    otherVertices->distance = otherPath;
                    otherVertices->predV = curr;
                    unfinishedQ.push(otherVertices);
                }
            }
        }
    }
}

int Jug::getWeight(int index) const {
    if (index == 0) {
        return costFillA;
    }
    if (index == 1) {
        return costFillB;
    }
    if (index == 2) {
        return costEmptyA;
    }
    if (index == 3) {
        return costEmptyB;
    }
    if (index == 4) {
        return costPourAB;
    }
    return costPourBA;
}

