//Lizzy Hanna, CS 3353, Lab 4, SMU ID 47358250
#include "fileLoader.h"
#include "search.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

void(*fileLoader::nodeAdder)(int,float,float,float);

fileLoader::fileLoader(){
    nodeAdder = Search::addNode;
}

void fileLoader::readCSV(string fileName){
    ifstream posFile;
    posFile.open(fileName);
    if(!posFile){
        cout << "Error opening file." << endl;
        exit(1);
    }
    while(posFile){ //add positions to nodes
        string s;
        string num = "";
        int index,x,y,z,data= 0;
        vector<string> positions;
        if(!getline(posFile, s))
            break;

        for(int i = 0; i < s.size(); i++){
            if(s[i] == ','){
                positions.push_back(num);
                num = "";
                continue;
            }else
                num += s[i];  
            }
        positions.push_back(num); //pushes the last coordinate    
        data = stof(positions[0]);
        x = stof(positions[1]);
        y = stof(positions[2]);
        z = stof(positions[3]);

        nodeAdder(data,x,y,z);
    }
}//end readCSV
   
            
