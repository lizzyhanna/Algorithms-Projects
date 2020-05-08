//Lizzy Hanna, CS 3353, SMU ID 47358250
#ifndef SORT_H
#define SORT_H

#include <vector>
#include <fstream>
#include <string>

#include "Algorithm.h"

using namespace std;

class Sort: public Algorithm{ 
    private:
        static std::vector<double(*)(std::vector<int>*, int)> algorithms; //vector of function pointers to different sorting algorithms
        double (*currAlgoPtr)(vector<int>*, int); //currently activated algorithm
        static std::vector<string> algoNames;
        int id; //which algo are we on...0,1,2...could replace with enum later
        std::vector<int> unsorted; //read in from file, doesn't change
        int dataSize; //num elements
        ofstream outFile; //file I create
        string fileName; //file we are reading in
        double myTime; //timing for specific algorithm

    public:
        //constructor
        Sort();
        ~Sort(); //destructor
   //overriden inherited pure virtual functions
        void select(int);
        void execute();
        void load(string);
        void save();
        void display();
        void stats();
};

#endif //SORT_H