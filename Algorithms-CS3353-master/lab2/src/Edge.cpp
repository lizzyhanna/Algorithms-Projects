//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
//Used in Adjacency Matrix
#include "Edge.h"
#include "MNode.h"
#include <iostream>

Edge::Edge(){
    this->first= nullptr;
    this->second = nullptr;
    this->weight = 0;
    this->e = false;
}

Edge::Edge(MNode * a, MNode * b, double weight){
    this->first = a;
    this->second = b;
    this->weight = weight;
    this->e = true;
}

int Edge::getWeight(){
    return this->weight;
}

void Edge::setWeight(double weight){
    this->weight = weight;
}

MNode * Edge::getFirst(){
    return this->first;
}

MNode * Edge::getSecond(){
    return this->second;
}

vector<MNode *> Edge::getNodes(){
    vector<MNode *> n;
    n.push_back(this->first);
    n.push_back(this->second);
    return n;
}

bool Edge::isEdge(){
    return e;
}

void Edge::addPos(int x,int y,int z){
    this->first->setPosition(x,y,z);
}

void Edge::addSecPos(int x, int y, int z){
    this->second->setPosition(x,y,z);
}
bool Edge::isVisited(){
    return this->visited;
}


void Edge::setVisited(){
    this->visited = true;
}
        
        
void Edge::reset(){
    this->visited = false;
}