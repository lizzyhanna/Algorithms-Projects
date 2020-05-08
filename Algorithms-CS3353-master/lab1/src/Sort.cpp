//Lizzy Hanna, CS 3353, SMU ID 47358250
#include <fstream>
#include <vector>
#include <chrono>
#include <iostream>

#include "SortAlgo.h"
#include "Sort.h"

using namespace std;

        vector<string> Sort::algoNames;
        std::vector<double(*)(std::vector<int>*, int)> Sort::algorithms;

        //constructor
        Sort::Sort(){
            //initialize algorithms vector
            this->algorithms.push_back(SortAlgo::bubble);
            this->algorithms.push_back(SortAlgo::insertion);
            this->algorithms.push_back(SortAlgo::merge);

            //initialize list of algorithm names to use in Sort::save() print-out later
            this->algoNames.push_back("Bubble Sort");
            this->algoNames.push_back("Insertion Sort");
            this->algoNames.push_back("Merge Sort");

            //initialize other variables
            this->currAlgoPtr = algorithms[0]; //sets default selected algo to Bubble
            this->dataSize = 0; 
            this->id = 0; //id is the id of the current algo, aka 0 for Bubble
            this->fileName = "";
            this->myTime = 0;

        }//end constructor



        Sort::~Sort(){}


       
        void Sort::select(int idNum){
            this->currAlgoPtr = algorithms.at(idNum);  
            this->id = idNum;
        }//end select



        void Sort::execute(){
            //create new sorted vector
            vector<int> sorted;
            for(int m = 0; m < unsorted.size(); m++){
                sorted.push_back(unsorted.at(m));
            }
    
            //run selected algorithm on data set and get time
            myTime = this->currAlgoPtr(&sorted, dataSize); 
           
        }//end execute




        void Sort::load(string name){
            this->fileName = name;
            ifstream myFile;
            string Fname = "dataSets/" + name; //appends file name to file path
            myFile.open(Fname);
            int x, n = 0;

            if(!myFile){
                cout << "unable to open file" << endl;
                exit(1);
            }else{
                while(myFile >> x){  
                    this->unsorted.push_back(x); 
                    n++;
                }
                this->dataSize = n;
            }

            myFile.close();

        }//end load




        void Sort::save(){
            //writes to same file every time
            this->outFile.open("savedData.txt", std::ofstream::app);
            if(!this->outFile){
                cout << "unable to open output file." << endl;
                exit(1);
            }else{
                //statistics
                this->outFile << "Operation performed: " << algoNames[id] << endl;
                this->outFile << "Execution time: " << myTime << " seconds." << endl;
                this->outFile << "Data set size: " << dataSize << " values" << endl;
                this->outFile << "Input file path: dataSets/" << fileName << endl;

                //formatting
                this->outFile << endl << endl;
                this->outFile << "===============================";
                this->outFile << endl << endl;
              
            }
            this->outFile.close();

        }//end save




        void Sort::display(){
            //displays unsorted vector to screen
            for(int i = 0; i < unsorted.size(); i++){
                cout << unsorted.at(i) << endl;
            }
        }


        void Sort::stats(){
            cout << "Operation Performed: " << this->algoNames[this->id] << endl;
            cout << "Execution time: " << this->myTime << " microseconds." << endl;
            cout << "Number of elements: " << this->dataSize << " values." <<endl;
            cout << "File name: " << this->fileName << endl;
            cout << "========================" << endl << endl;
        }