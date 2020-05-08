//Lizzy Hanna, CS 3353, SMU ID 47358250
#include <iostream>
#include <vector>
#include <string>

#include "Sort.h"

using namespace std;

int main (void) {
    string numFiles[16] = {"random10.txt", "random1000.txt", "random10000.txt", "random100000.txt", "rso10.txt", "rso1000.txt", "rso10000.txt", "rso100000.txt", "30random10.txt", "30random1000.txt", "30random10000.txt", "30random100000.txt", "unique10.txt", "unique1000.txt", "unique10000.txt", "unique100000.txt"};
    vector<string> fileNames;
    for(int i = 0; i < 16; i++){
        fileNames.push_back(numFiles[i]);
    }

    Sort algo;
    for(int i = 0; i < fileNames.size(); i++){ //chooses current file to load, loop 16 times
        algo.load(fileNames[i]); 
        for(int j =0; j < 3; j++){ //chooses which algorithm to perform on the file
            algo.select(j); 
            algo.execute(); 
            algo.save();
            algo.stats();
            //I'm not using display because I don't want 100,000 elements on the screen.
           // algo.display(); //displays unsorted vector to screen. 

        } 
    }
    return 0;
}//end main
