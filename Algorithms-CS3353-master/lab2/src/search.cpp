//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
#include "Algorithm.h"
#include "Node.h"
#include "MNode.h"
#include "search.h"
#include "AdjList.h"
#include "AdjMatrix.h"
#include "SearchAlgos.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

//static variable
vector<tuple<vector<int>, int, int, double>(*)(AdjList&, int,int)> Search::algorithms;
vector<tuple<vector<int>, int, int, double>(*)(AdjMatrix&, int, int)> Search::algorithmsMatrix;

//constructor
Search::Search(){
    this->algoNames.push_back("BFS Iterative");
    this->algoNames.push_back("BFS Recursive");
    this->algoNames.push_back("DFS Iterative");
    this->algoNames.push_back("DFS Recursive");
    this->algoNames.push_back("Dijkstra");
    this->algoNames.push_back("A*");

    //All the algos for AdjList
    this->algorithms.push_back(SearchAlgos::BFSIterative);
    this->algorithms.push_back(SearchAlgos::BFSRecursive);
    this->algorithms.push_back(SearchAlgos::DFSIterative);
    this->algorithms.push_back(SearchAlgos::DFSRecursive);
    this->algorithms.push_back(SearchAlgos::Dijkstra);
    this->algorithms.push_back(SearchAlgos::aStar);

    //All the algos for AdjMatrix
    this->algorithmsMatrix.push_back(SearchAlgos::BFSIMatrix);
    this->algorithmsMatrix.push_back(SearchAlgos::BFSRMatrix);
    this->algorithmsMatrix.push_back(SearchAlgos::DFSIMatrix);
    this->algorithmsMatrix.push_back(SearchAlgos::DFSRMatrix);
    this->algorithmsMatrix.push_back(SearchAlgos::DjikstraMatrix);
    this->algorithmsMatrix.push_back(SearchAlgos::AStarMatrix);
}//end constructor

//destructor
Search::~Search(){}


void Search::execute(){
     //tuple<vector<int> path, int nodesExplored, int Distance, int Cost>
    //runs List
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    tuple<vector<int>, int, int, int> tList = this->currAlgoPtr(this->list, this->source, this->dest); //executes algo
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    this->myTime = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    this->path = get<0>(tList);
    this->nodesExplored = get<1>(tList);
    this->distance = get<2>(tList);
    this->cost = get<3>(tList);
   
   
    //runs Matrix
    chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
    //tuple<vector<int>, int, int, int> tMatrix = this->algorithmsMatrix[0](this->matrix, this->source, this->dest);
    tuple<vector<int>, int, int, int> tMatrix = this->matrixAlgoPtr(this->matrix, this->source, this->dest);
    chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
    this->myTimeMatrix = chrono::duration_cast<chrono::microseconds>(t4-t3).count();
    this->pathMatrix = get<0>(tMatrix);
    this->nodesExploredMatrix = get<1>(tMatrix);
    this->distanceMatrix = get<2>(tMatrix);
    this->costMatrix = get<3>(tMatrix);
} //end execute()



void Search::select(int s){
    this->id = s;
    this->currAlgoPtr = algorithms[s];
    this->matrixAlgoPtr = algorithmsMatrix[s];
}//end select()



void Search::save(){
    //I used this to save my statistics to files

    this->outFile.open("timings.txt", std::ofstream::app);
      if(!this->outFile){
            cout << "Search::save, unable to open output file." << endl;
            exit(1);
        }else{
            //statistics
            //this->outFile << "Operation performed: " << algoNames[id] << endl;
            this->outFile << this->myTimeMatrix << endl;
        }
        this->outFile.close();


    this->outFile1.open("nodesInPath.txt", std::ofstream::app);
     if(!this->outFile1){
            cout << "Search::save, unable to open output file." << endl;
            exit(1);
        }else{
            //statistics
            //this->outFile << "Operation performed: " << algoNames[id] << endl;
            this->outFile1 << this->pathMatrix.size() << endl;     
        }
        this->outFile1.close();

    this->outFile2.open("nodesExplored.txt", std::ofstream::app);
     if(!this->outFile2){
            cout << "Search::save, unable to open output file." << endl;
            exit(1);
        }else{
            //statistics
            //this->outFile << "Operation performed: " << algoNames[id] << endl;
            this->outFile2 << this->nodesExploredMatrix << endl;
        }
        this->outFile2.close();
    
    this->outFile3.open("distance.txt", std::ofstream::app);
    if(!this->outFile3){
            cout << "Search::save, unable to open output file." << endl;
            exit(1);
        }else{
            //statistics
            //this->outFile << "Operation performed: " << algoNames[id] << endl;
            this->outFile3 << this->distanceMatrix << endl;
        }
        this->outFile3.close();

    
}//end save()


void Search::display(){
    //I used this to calculate averages of 100 runs

    ifstream file1;
    file1.open("timings.txt");
    //get average time
    string s;
    int num =0;
    while(file1){
        if(!getline(file1, s))
                break;
        num += stoi(s);
    }
    //cout << "Average timing was " << (num/100) << " seconds." << endl;
    file1.close();

    ifstream file2;
    file2.open("distance.txt");
    num =0;
    while(file2){
        if(!getline(file2, s))
                break;
        num += stoi(s);
    }
    //cout << "Average distance was " << (num/100) << endl;
    file2.close();

    ifstream file3;
    file3.open("nodesExplored.txt");
     num = 0;
    while(file3){
        if(!getline(file3, s))
                break;
        num += stoi(s);
    }
   // cout << "Average nodes Explored was " << (num/100) << endl;
    file3.close();



    ifstream file4;
    file4.open("nodesInPath.txt");
     num = 0;
    while(file4){
        if(!getline(file4, s))
                break;
        num += stoi(s);
    }
  //cout << "Average nodes in the path is " << (num/100) << endl;
    file4.close();
    

}//end display()



void Search::stats(){
    cout << "Algorithm: " << algoNames[id] << endl;
    cout << "Graph Type: Adjacency List" << endl;
    cout << "Number of Nodes in returned path: " << this->path.size() << endl;
    cout << "Total Cost of Path: " << this->cost << " (will be 0 for BFS and DFS)" << endl;
    cout << "Number of Nodes explored in path: " << this->nodesExplored << endl;
    cout << "Execution Time to Find Path: " << this->myTime << " microseconds." << endl;
    cout << "Returned Path: " << endl;
    for(int i = 0; i < this->path.size(); i++){
        cout << this->path[i] << "->";
    }
    cout << endl << endl;

    cout << "Algorithm: " << algoNames[id] << endl;
    cout << "Graph Type: Adjacency Matrix" << endl;
    cout << "Number of Nodes in returned path: " << this->pathMatrix.size() << endl;
    cout << "Total Cost of Path: " << this->costMatrix << " (will be 0 for BFS and DFS)" <<endl;
    cout << "Number of Nodes explored in path: " << this->nodesExploredMatrix << endl;
    cout << "Execution Time to Find Path: " << this->myTimeMatrix << " microseconds." << endl;
    cout << "Returned Path: " << endl;
    for(int i = 0; i < this->pathMatrix.size(); i++){
        cout << this->pathMatrix[i] << "->";
    }
    cout << endl << endl;
}//end stats()



void Search::setSource(int s){
    this->source = s;
}

void Search::setDest(int d){
    this->dest = d;
}

void Search::load(vector<string> files){
    //clear old graphs
    //this->list.clear();
    // this->matrix.clear();

    cout << "Search::load" << endl;
    for(int i = 0; i < files.size(); i++){
        cout << files[i] << ", ";
    }
    cout << endl;

    //CREATE ADJLIST
    if(files.size() == 3)
        this->fileName = files[0];
    else{
        cout << "Search::load, Error: incorrect number of files in vector" << endl;
        exit(1);
    }

    ifstream myFile;
    ifstream posFile;
    ifstream wFile;
    string Fname = files[0]; 
    myFile.open(files[0]);
    wFile.open(files[1]);
    posFile.open(files[2]);
    int size = 0;

    //if any files don't open, exit
    if(!myFile){
        cout << "Search::load, unable to open graph file" << endl;
        exit(1);
    }else if(!posFile){
        cout << "Search::load, unable to open positions file" << endl;
        exit(1);
    }else if(!wFile){
        cout << "Search::load, unable to open weights file" << endl;
        exit(1);

    //ADJLIST
    }else{
        //ADD ALL PARENTS
        while(myFile){   //add data to nodes in AdjList
            string s;
            if(!getline(myFile, s))
                break;
            string num = "";
            for(int i = 0; i < s.size(); i++){
                if(s[i] == ',')
                    break;
                else
                    num += s[i];  
            }
            Node * n = new Node(stoi(num)); //need a toInt(num) function here
            list.push_back(n); //add node to adjList
            size++; //use this to create matrix of size*size later
        }

        matrix.resize(size);

        //GO BACK AND ADD ALL CHILDREN
        myFile.clear();
        myFile.seekg(ios::beg);

        while(myFile){
            string s;
            string num = "";
            vector<string> nodes;
            if(!getline(myFile, s))
                break;
            for(int i = 0; i < s.size(); i++){
                if(s[i] == ','){
                    nodes.push_back(num);
                    num = "";
                    continue;
                }else{
                    num += s[i];
                }
            }
            nodes.push_back(num); //gets last child
            if(nodes.size() != 0){
                int parentIndex = stoi(nodes[0]) -1;
                for(int i = 1; i < nodes.size(); i++){
                    list.at(parentIndex)->addChild(list.at(stoi(nodes[i])-1), 0); //weight is set to 0 for now
                }
            }
        }

         while(wFile){ //go back and add the children and their weights
            string s;
            string num = "";
            int w, parentIndex, child;
            vector<string> weightInfo; //first index is parent, second is child, third is weight
            if(!getline(wFile, s))
                break;
            
            for(int i = 0; i < s.size(); i++){
                if(s[i] == ','){
                    weightInfo.push_back(num);
                    num = "";
                    continue;
                }else
                    num += s[i];
            }
            weightInfo.push_back(num);
            if(weightInfo.size() == 3){
                parentIndex = stoi(weightInfo[0]) - 1;
                child = stoi(weightInfo[1]);
                double w = stod(weightInfo[2]);
                list.at(parentIndex)->addWeight(child, w);
                MNode * p = new MNode(parentIndex+1);
                MNode * c = new MNode(child);
                matrix.addEdge(p, c, w);      
            }
            
        }
        while(posFile){ //add positions to nodes
            string s;
            string num = "";
            int index,x,y,z = 0;
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
            
                index = stoi(positions[0]) - 1;
                x = stoi(positions[1]);
                y = stoi(positions[2]);
                z = stoi(positions[3]);
            
            //add positions to the node in the list
            (*(list.at(index))).setPosition(x,y,z);

            //add positions to the edges in the matrix
            for(int i =0; i < matrix.getSize(); i++){

                if (matrix.at(i,index)->isEdge())
                    matrix.at(i,index)->addPos(x,y,z);

                if(matrix.at(index, i)->isEdge())
                    matrix.at(index, i)->addSecPos(x,y,z);
            }


          
        } //end positions while loop
    }//end the else statement from beginning

    //close files
    myFile.close();
    posFile.close();
    wFile.close();
}//end Load()