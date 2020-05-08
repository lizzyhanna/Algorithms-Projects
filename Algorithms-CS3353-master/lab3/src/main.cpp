//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3
#include "fileLoader.h"
#include "search.h"

#include <string>
#include <iostream>

//File loader-> csv loader
//grabline->gets the whole line so you only look for commas
//command object-> command design pattern

using namespace std;

int main(int argc, char *argv[]){

    if(argc < 2){
        cout << "main: Incorrect number of arguments." << endl;
        cout << "Arguments should be fileName, then an int (either 0 for brute force, 1 for dynamic, or 2 for both).";
        exit(1);
    }fileLoader file;
    

    file.readCSV(argv[1]);
    int choice = stoi(argv[2]);
    Search algo;

    //0 for Brute Force, 1 for Dynamic, or 2 to run both.
    if(choice==2){
        for(int i = 0; i < 2; i++){
            algo.select(i);
            algo.execute();
            algo.stats();
        }
    }else if(choice == 0 | choice == 1){ //executes only one algorithm, bf=0, dp=1
        algo.select(choice);
        algo.execute();
        algo.stats();
    }else{
        cout << "Invalid selection." << endl;
        exit(1);
    }
    return 0;
}