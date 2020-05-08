//Lizzy Hanna, CS 3353, SMU ID 47358250
#ifndef SEARCH_H
#define SEARCH_H

#include "Algorithm.h"
#include "AdjList.h"
#include "AdjMatrix.h"

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Search : public Algorithm{
    private:
        vector<string> algoNames;
        static vector<tuple<vector<int>, int, int, double>(*)(AdjList&,int,int)> algorithms;
        static vector<tuple<vector<int>, int, int, double>(*)(AdjMatrix&, int, int)>algorithmsMatrix;
        
        //Variables for both:
        int id;
        int source;
        int dest;

        //Adjacency List-only variables
        AdjList list;
        tuple<vector<int>, int, int, double>(*currAlgoPtr)(AdjList&,int,int); 
        int nodesExplored;
        int distance;
        int cost;
        double myTime;
        vector<int> path;

        //Adjacency Matrix-only variables
        AdjMatrix matrix;
        tuple<vector<int>,int,int,double>(*matrixAlgoPtr)(AdjMatrix&,int,int);
        int nodesExploredMatrix;
        int distanceMatrix;
        int costMatrix;
        double myTimeMatrix;
        vector<int> pathMatrix;

        //Files...I used these to create my data files for the graphs in Search::Save()
        ofstream outFile;
        ofstream outFile1;
        ofstream outFile2;
        ofstream outFile3;
        string fileName;


    public:
        Search();
        ~Search();
        void load(vector<string> files); //had to change parameters in algo base class to vector<string> files
        void execute(); //pure virtual in parent class
        void select(int); //pure virtual in parent class
        void save();
        void display();
        void stats();
        void setSource(int);
        void setDest(int);

      
};
#endif