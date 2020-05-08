//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 4
#ifndef GA_H
#define GA_H
#include "Node.h"
#include <vector>
#include <utility>

using namespace std;

class GA{
    private:
         vector<int> bestEver;
         vector<int> currentBest;
         vector<int> lastBest;
         vector<float> distances;
         float bestDistance;
         int popSize;
         int timer;
         int mutationRate;
         int mutationTechnique; //which technique will we use
         int selectionTechnique;
         int crossoverTechnique;
         float targetD; //in known data set sizes, this is the best length
         float currentDistance;
        
    public:
         GA();
         GA(int popSize, int timer, int mutationRate, int mutationTechnique, int selectionTechnique, int crossoverTechnique, float targetD);
         pair<vector<int>, float> gaSearch(vector<Node*>);
         void shuffle(vector<int> &);
         void intenseShuffle(vector<int>&);
         void myswap(vector<int> &, int, int);
         vector<vector<float>> createADJMatrix(vector<Node*>);
         float calcDistance(int, int, vector<Node*>);
         float calcDistance(vector<int>, vector<vector<float>>);
         void normalizeFitness(vector<int> & );
         vector<int> calculateFitness(vector<vector<int> > &, vector<vector<float> > &);
         void nextGeneration(vector<vector<int> > &, vector<int> &);
         void mutate(vector<int> & );
         int roulette(vector<vector<int> > population, vector<int> & fitness);
         int roulette(vector<vector<int> > population, vector<int> fitness, vector<int> & otherParent);
         vector<int> crossover(vector<int>& a, vector<int>& b);
         vector<int> crossover(vector<int>);
         vector<int> crossoverLCS(vector<int>& a, vector<int> & gcs);
         vector<int> lcs(vector<int> & a, vector<int> & b);
};

#endif