//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3

#include "Node.h"
#include <vector>
#include <iostream>

using namespace std;


Node::Node(){}

Node::Node(const Node& n){ //copy constructor
    this->data = n.data;
    this->position.push_back(n.position[0]);
    this->position.push_back(n.position[1]);
    this->position.push_back(n.position[2]);

}

Node::Node(int data, float x, float y, float z){
    this->data = data;
    this->position.push_back(x);
    this->position.push_back(y);
    this->position.push_back(z);
}

Node::~Node(){}
        
int Node::getData(){
    return this->data;
}
void Node::setData(int d){
    this->data = d;
}

vector<float> Node::getPosition(){
    return this->position;
}

float Node::getX(){
    if(this->position.size() >= 3)
        return this->position[0];
    return -1;
} 
float Node::getY(){
    if(this->position.size() >= 3)
        return this->position[1];
    return -1;
} 
float Node::getZ(){
    if(this->position.size() >= 3)
        return this->position[2];
    return -1;

} 

void Node::print(){
    cout << "(Data: " << this->data << ", [" << this->position[0] << "," << this->position[1] << "," << this->position[2] << "])";
 }