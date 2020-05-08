//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 4
#ifndef SEARCH_H
#define SEARCH_H

#include "Node.h"
#include "Algorithm.h"
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

class Search: public Algorithm{

private:
    static vector<Node*> cities;

    vector<string> algoNames;
    int selection;
    ofstream outFile; //used in save() method

    //GA variables
    float GA_distance;
    vector<int> GA_tour;
    double GA_time;

    //Tabu variables
    float tabu_distance;
    vector<int> tabu_tour;
    double tabu_time;

    
public:
    int targetD;
    Search();           //constructor
    static void addNode(int,float,float,float); //used by fileLoader to add nodes
    void execute();     //overridden pure virtual
    void printCities(); //prints list of nodes
	void stats();       //prints the tour & best distance to screen           
	void select(int);   //overridden pure virtual
    void save();        
	
};
#endif