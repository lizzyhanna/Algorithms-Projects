//Lizzy Hanna, CS 3353, SMU ID 47358250
#ifndef SEARCHALGOS_H
#define SEARCHALGOS_H

#include "Node.h"
#include "AdjList.h"
#include "AdjMatrix.h"
#include <vector>
#include <queue>
#include <stack>
#include <tuple> 
using namespace std;

class SearchAlgos{
    private:
        double totalCost;
        double totalDistance;
        vector<int> path;

    public:
        SearchAlgos();
        vector<int> getPath();
        int getNodesExplored();
        void addNodeExplored();
        void reset();
        double getTotalDistance();
        double getTotalCost();

        //return type of searches is:
        //tuple<vector<int> path, int nodesExplored, int Distance, int Cost>
        
        //Adjacency List Searches:
        static tuple<vector<int>, int, int, double> BFSIterative(AdjList&, int, int);
        static tuple<vector<int>, int, int, double> DFSIterative(AdjList&, int, int);
        static tuple<vector<int>, int, int, double> BFSRecursive(AdjList&, int, int);
        static tuple<vector<int>, int, int, double> DFSRecursive(AdjList&, int, int);
        static tuple<vector<int>, int, int, double> DFSR(AdjList &, int, int, int, int, stack<vector<int> >); //helper function
        static tuple<vector<int>, int, int, double> BFSR(AdjList&, int, int, int, int, queue <vector<int> >); //helper function
        static tuple<vector<int>, int, int, double> Dijkstra(AdjList&, int, int);
        static tuple<vector<int>, int, int, double> aStar(AdjList&, int, int);

        //Adjacency Matrix Searches:
        static tuple<vector<int>, int, int, double> BFSIMatrix(AdjMatrix&, int, int);
        static tuple<vector<int>, int, int, double> BFSRMatrix(AdjMatrix&, int, int);
        static tuple<vector<int>, int, int, double> BFSRHelp(AdjMatrix&, int, int, int, int, queue<vector<int> >); //helper function
        static tuple<vector<int>, int, int, double> DFSIMatrix(AdjMatrix&, int, int);
        static tuple<vector<int>, int, int, double> DFSRMatrix(AdjMatrix&, int, int);
        static tuple<vector<int>, int, int, double> DFSRHelp(AdjMatrix&, int, int, int, int, stack<vector<int> >); //helper function
        static tuple<vector<int>, int, int, double> DjikstraMatrix(AdjMatrix&, int, int);
        static tuple<vector<int>, int, int, double> AStarMatrix(AdjMatrix&, int, int);
 

};

#endif