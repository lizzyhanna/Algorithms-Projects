//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3
#ifndef TSP_H
#define TSP_H

#include "Node.h"

#include <string>
#include <iostream>
#include <chrono>
#include <list>
#include <vector>
#include <utility>

using namespace std;

class TSP{
public:
    static float calcDistance(vector<Node*>&);
    static void swap(int, int, vector<Node*> &);
    static pair<vector<int>, float> dynamic(vector<Node*>);
    static pair<vector<int>, float> bruteForce(vector<Node*>);
    static pair<vector<int>, float> solve(vector<vector<float>> distance, float ** memo, int s, int n, int start);
    static bool notIn(int,int);
    static vector<int> combinations(int,int);
    static void combinations_r(int,int,int,int,vector<int>&);
    static vector<vector<float>> createADJMatrix(vector<Node*> cities);  
    static float calcDistance(int first, int second, vector<Node*> v);
};
#endif
