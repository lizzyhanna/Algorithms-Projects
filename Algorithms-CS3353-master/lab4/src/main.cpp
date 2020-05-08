//Lizzy Hanna, CS 3353, SMU ID 47358250 , Lab 4
#include "fileLoader.h"
#include "search.h"
#include <string>
#include <iostream>
#include <fstream>

//two args: file, Algo Selection
//three args: file, Algo Selection, known distance
int main(int argc, char *argv[]){
    // int noKnown = 1;
    // cout << "hi";
    if(argc < 2){ //remove arc > 3 if you will be using known distance
        cout << "main: Incorrect number of arguments." << endl;
        cout << "Arguments should be fileName, then an int (either 0 for Tabu Search, 1-7 for GA, or 8 for all configurations of both)";
        exit(1);
    }
    
    int choice = stoi(argv[2]);
    
    fileLoader file;
    file.readCSV(argv[1]);

    
    Search algo;

    //FOR KNOWN DISTANCES.....
    //algo.targetD = stoi(argv[3]); //known distance of a graph set can be used as a third argument
    algo.targetD = -1; // no target distance


    if(choice==8){ //execute both algos
        for(int i = 0; i < 8; i++){
            algo.select(i);
            algo.execute();
            algo.stats();
            algo.save();
        }
    }else if(choice > -1 && choice < 8){ //executes only one algorithm
        algo.select(choice);
        algo.execute();
        algo.stats();
        algo.save();
    }else{
        cout << "Invalid selection." << endl;
        exit(1);
    }
    return 0;
}