//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
#include "search.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main (int argc, char* argv[]) {
   if(argc != 3){
      cout << "Invalid number of command line args. Please try again with ./a.out, src, destination." << endl;
      exit(1);
   }
    //add all files to the vector
   vector<string> fileNames;
   fileNames.push_back("DataSets/SampleGraph/graph.txt");
   fileNames.push_back("DataSets/SampleGraph/weights.txt");
   fileNames.push_back("DataSets/SampleGraph/positions.txt");
  
   Search algo;
   algo.setSource(stoi(argv[1]));
   algo.setDest(stoi(argv[2]));
  
   
   for(int i = 0; i < fileNames.size(); i){ //chooses current file to load, loop 16 times
      vector<string> filesToLoad;
      //push the 3 files in order graph, weight, position into a vector to load
      for(int b = 0; b < 3; b++){
         filesToLoad.push_back(fileNames[i++]); 
      }
      algo.load(filesToLoad); //loads all 3 files into adjlist and adjmatrix
      //dynamically chooses which of the 5 algorithms to perform on the file
      for(int j =0; j < 6; j++){ 
         algo.select(j); 
         algo.execute(); 
         algo.stats();
         algo.save();
         algo.display();
         
      } 
      
   }
   return 0;
}//end main
