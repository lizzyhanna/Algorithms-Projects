
//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3
#ifndef SEARCH_H
#define SEARCH_H

#include "Node.h"
#include "Algorithm.h"

#include "tsp.h"
#include <vector>
#include <utility>
#include <fstream>


using namespace std;

class Search: public Algorithm{
private:
    static vector<pair<vector<int>, float>(*)(vector<Node*>)> algorithms;
    static pair<vector<int>, float>(*currAlgoPtr)(vector<Node*>);
    static vector<Node*> cities;

    vector<string> algoNames;
    int selection;
    ofstream outFile;

    int time_bf;
    float distance_bf;
    vector<int> tour_bf;

    int time_dp;
    float distance_dp;
    vector<int> tour_dp;
    
public:
    Search();
    static void addNode(int,float,float,float);
    void execute(); //overridden pure virtual
    void printCities();
	void stats();
//	void save();
	void select(int); //overridden pure virtual
	
};
#endif