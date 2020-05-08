//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3
#include "search.h"
#include "Node.h"
#include "tsp.h"

#include <vector>
#include <utility>
#include <fstream>

using namespace std;

vector <pair<vector<int>, float>(*)(vector<Node*>)> Search::algorithms; //vector of algos
vector<Node*> Search::cities; //list of nodes (aka cities)
pair<vector<int>, float>(*Search::currAlgoPtr)(vector<Node*>);

//constructor
Search::Search(){
    this->algorithms.push_back(TSP::bruteForce); 
    this->algorithms.push_back(TSP::dynamic); 
    this->selection = -1;
    this->algoNames.push_back("Brute force");
    this->algoNames.push_back("Dynamic Programming");
}

void Search::addNode(int data,float x,float y,float z){
    Node * n = new Node(data, x, y, z); //create a new node with data and coordinates
    cities.push_back(n);
}

void Search::select(int i){
    this->selection = i;
    currAlgoPtr = algorithms[i];
}

void Search::execute(){
    if(selection != -1){
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        pair<vector<int>, float> p(currAlgoPtr(this->cities));
        //pair<vector<int>, float> p(algorithms[selection](this->cities));
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        if(selection == 0){
            this->time_bf = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
            this->tour_bf = get<0>(p);
            this->distance_bf = get<1>(p);
        }else{
            this->time_dp = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
            this->tour_dp = get<0>(p);
            this->distance_dp = get<1>(p);
        }
    }
}

void Search::stats(){
    if(selection != -1){
        cout << "Algorithm: " << this->algoNames[selection] << endl;
    }

    if(selection == 0){
        cout << "Best distance: " << this->distance_bf << endl;
        cout << "Tour: ";
        for(int i = 0; i < this->tour_bf.size(); i++){
            if(i == tour_bf.size()-1){ //end of tour
                cout << tour_bf[i] << endl;
                break;
            }
            cout << tour_bf[i] << ", ";
        }
        cout << "Time: " << this->time_bf << endl;

    }else if (selection == 1){
        cout << "Best distance: " << this->distance_dp << endl;
        cout << "Tour: ";
        for(int i = 0; i < this->tour_dp.size(); i++){
            if(i == tour_dp.size()-1){ //end of tour
                cout << tour_dp[i] << endl;
                break;
            }    
            cout << tour_dp[i] << ", ";
        }
        cout << "Time: " << this->time_dp << endl;

    }   
}

// void Search::save(){
//       this->outFile.open("recordData.txt", std::ofstream::app);
//       if(!this->outFile){
//             cout << "Search::save, unable to open output file." << endl;
//             exit(1);
//         }else{
            
//         outFile << "Test";

//         }
//         this->outFile.close();
// }