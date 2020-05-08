//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
//Used in Adjacency Matrix

#ifndef EDGE_H
#define EDGE_H
#include "MNode.h"

class Edge{
    private:
        double weight;
        MNode * first;
        MNode * second;
        bool e;
        bool visited;
    public:
        Edge();
        Edge(MNode*,MNode*,double);
        int getWeight();
        void setWeight(double);
        MNode *getFirst();
        MNode* getSecond();
        vector<MNode*> getNodes();
        bool isEdge();
        void addPos(int,int,int);
        void addSecPos(int,int,int);
        bool isVisited();
        void setVisited();
        void reset();
};
#endif