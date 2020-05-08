//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "Edge.h"
#include "Node.h"

#include <vector>

class AdjMatrix{
    private:
        Edge * * * matrix; //matrix of Edge *
        int size;
    public:
        AdjMatrix();
        AdjMatrix(int);
        ~AdjMatrix();
        void addEdge(MNode * a, MNode * b, double weight);
        Edge * at(int, int);
        void resize(int size);
        int getSize();
        void clear();
        void print();
};
#endif