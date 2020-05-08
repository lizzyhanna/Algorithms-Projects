//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
//This is a node designed specifically to be utilized in the Adjacency Matrix
#include "MNode.h"

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;


MNode::MNode(){}//default constructor

MNode::MNode(int data){
    this->data = data;
    this->visited = false;
}
MNode::MNode(int data, int x, int y, int z){
    this->data = data;
    this->visited = false;

    //coordinates
    this->position.push_back(x);
    this->position.push_back(y);
    this->position.push_back(z);
}

MNode::~MNode(){}
int MNode::getData(){
    return this->data;
}
void MNode::setData(int data){
    this->data = data;
}
bool MNode::isVisited(){
    return this->visited;
}
void MNode::setVisited(){
    this->visited = true;
} 

void MNode::reset(){
    this->visited = false;
}

vector<int> MNode::getPosition(){
    return this->position;
}

void MNode::setPosition(int x, int y, int z){
        this->position.push_back(x);
        this->position.push_back(y);
        this->position.push_back(z);
}

int MNode::getX(){
    if(position.size() == 3)
        return position.at(0);
    else{
        cout << "MNode::getx, no x position" << endl;
        return -1;
    }
}

int MNode::getY(){
    if(position.size() == 3)
        return position.at(1);
    else{
        cout << "MNode::getY, no y position" << endl;
        return -1;
    }
}

int MNode::getZ(){
    if(position.size() == 3)
        return position.at(2);
    else{
        cout << "MNode::getZ, no z position" << endl;
        return -1;
    } 
}


