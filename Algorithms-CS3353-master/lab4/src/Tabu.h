//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 4
#ifndef TABU_H
#define TABU_H
#include "Node.h"

#include <vector>
#include <utility>
#include <deque>

using namespace std;

class Tabu{
    private:
        vector<int> bestEver;
        float bestDistance;
        deque <vector<int> > tabuList;
        int listSize;
        int hoodSize;
        int neighborhoodTechnique;
        int timer;
        float targetD;

    public:
        Tabu();
        Tabu(int,int,float, int);
        pair<vector<int>, float> tabuSearch(vector<Node*>);
        vector<vector<int> > getNeighborhood(vector<int>);
        void myshuffle(vector<int> &);
        void myswap(vector<int> &, int, int);
        vector<int> myswapValue(vector<int>, int, int);
        vector<vector<int> > spotExchange(vector<int> & );
        float calcDistance(int, int, vector<Node*>);
        float calcDistance(vector<int>, vector<vector<float> >);
        vector<vector<float> > createADJMatrix(vector<Node*> );
        void makeTabu(vector<int>);
        vector<double> normalizeDistance(vector<float>&);
        int roulette(vector<float> &);
        void restart(vector<int> & );

};

#endif