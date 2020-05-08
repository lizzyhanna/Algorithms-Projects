//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 4
#include "search.h"
#include "Node.h"
#include "Tabu.h"
#include "GA.h"
#include "math.h"
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <chrono>
using namespace std;

vector<Node *> Search::cities; //list of nodes (aka cities)

//constructor
Search::Search()
{
    this->selection = -1;
    this->algoNames.push_back("Tabu List");
    this->algoNames.push_back("Genetic Algorithm: Technique 1");
    this->algoNames.push_back("Genetic Algorithm: Technique 2");
    this->algoNames.push_back("Genetic Algorithm: Technique 3");
    this->algoNames.push_back("Genetic Algorithm: Technique 4");
    this->algoNames.push_back("Genetic Algorithm: Technique 5");
    this->algoNames.push_back("Genetic Algorithm: Technique 6");
    this->algoNames.push_back("Genetic Algorithm: Technique 7");
}

void Search::addNode(int data, float x, float y, float z)
{
    Node *n = new Node(data, x, y, z); //create a new node with data and coordinates
    cities.push_back(n);
}

void Search::select(int i)
{
    this->selection = i;
}

void Search::execute()
{
    if (this->selection > -1)
    {
        pair<vector<int>, float> p;
        float targetD = this->targetD; 
        int timer = 600; //default 10 min

        if (this->selection == 0)
        { //save off tabu stats
            Tabu *tabuSearch;
            int size = 150;
            int technique = 1;
            tabuSearch = new Tabu(size, technique, targetD, timer);
            //Tabu::Tabu(int size, int technique, float targetD)
            chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
            pair<vector<int>, float> p(tabuSearch->tabuSearch(this->cities));
            chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
            this->tabu_time = chrono::duration_cast<chrono::microseconds>(t4 - t3).count();
            this->tabu_tour = get<0>(p);
            this->tabu_distance = get<1>(p);
            delete tabuSearch;
        }
        else
        { //save off GA stats
            GA *geneticAlgo;
            int popSize = 50;
            int mutationRate = 10;

            //GA(popSize, timer, mutationRate, mutationTechnique, selectionTechnique, crossoverTechnique, targetD);
            switch (this->selection)
            {
            case 1:
                geneticAlgo = new GA(popSize, timer, mutationRate, 1, 1, 1, targetD); //technique 1
                break;
            case 2:
                geneticAlgo = new GA(popSize, timer, mutationRate, 2, 1, 1, targetD); //technique 2
                break;
            case 3:
                geneticAlgo = new GA(popSize, timer, mutationRate, 2, 2, 1, targetD); //technique 3
                break;
            case 4:
                geneticAlgo = new GA(popSize, timer, mutationRate, 2, 2, 2, targetD); //techniqe 4
                break;
            case 5:
                geneticAlgo = new GA(popSize, timer, mutationRate, 1, 2, 1, targetD); //technnique 5
                break;
            case 6:
                geneticAlgo = new GA(popSize, timer, mutationRate, 1, 1, 2, targetD); //technique 6
                break;
            case 7:
                geneticAlgo = new GA(popSize, timer, mutationRate, 1, 2, 2, targetD); //technique 7
                break;
            default:
                geneticAlgo = new GA(popSize, timer, mutationRate, 1, 1, 1, targetD);
                break;
            }

            chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
            pair<vector<int>, float> p1(geneticAlgo->gaSearch(this->cities));
            chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
            this->GA_time = chrono::duration_cast<chrono::microseconds>(t4 - t3).count();
            this->GA_tour = get<0>(p1);
            this->GA_distance = get<1>(p1);
            delete geneticAlgo;
        } //end genetic algo else
    }
}

void Search::stats()
{
    cout << "Algorithm: " << algoNames[selection] << endl;
    if (selection < 1)
    { // Tabu
        cout << "Time: " << this->tabu_time << endl;
        cout << "Distance found: " << this->tabu_distance << endl;
        cout << "Tour: ";
        for (int i = 0; i < this->tabu_tour.size(); i++)
        {
            cout << this->tabu_tour[i] << ",";
        }
        cout << endl;
    }
    else
    { // GA
        cout << "Time: " << this->GA_time << endl;
        cout << "Distance found: " << this->GA_distance << endl;
        cout << "Tour: ";
        for (int i = 0; i < this->GA_tour.size(); i++)
        {
            cout << this->GA_tour[i] << ",";
        }
        cout << endl;
    }
}

void Search::save()
{
    this->outFile.open("recordData.txt", std::ofstream::app);
    if (!this->outFile)
    {
        cout << "Search::save, unable to open output file." << endl;
        exit(1);
    }
    else
    {

        outFile << "Algorithm: " << algoNames[selection] << endl;
        if (selection < 1)
        { // Tabu
            outFile << "Time: " << this->tabu_time << endl;
            outFile << "Distance found: " << this->tabu_distance << endl;
            outFile << "Tour: ";
            for (int i = 0; i < this->tabu_tour.size(); i++)
            {
                outFile << this->tabu_tour[i] << ",";
            }
            outFile << endl;
        }
        else
        { // GA
            outFile << "Time: " << this->GA_time << endl;
            outFile << "Distance found: " << this->GA_distance << endl;
            outFile << "Tour: ";
            for (int i = 0; i < this->GA_tour.size(); i++)
            {
                outFile << this->GA_tour[i] << ",";
            }
            outFile << endl;
        }
    }
    this->outFile.close();
} //end save