//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
#ifndef ADJLIST_H
#define ADJLIST_H

#include <vector>

#include "Node.h"

using namespace std;

class AdjList{
    private:
        vector<Node*> list;
    public:
        void resetNodes();
        Node* at(int index);
        void push_back(Node*);
        int size();
        void printList();
        void clear();
       
};
#endif