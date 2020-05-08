//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
//Node for adjacency list usage

#include "Node.h"

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;


Node::Node(){}//default constructor

Node::Node(int data){
    this->data = data;
    this->visited = false;
}
Node::Node(int data, int x, int y, int z){
    this->data = data;
    this->visited = false;

    //coordinates
    this->position.push_back(x);
    this->position.push_back(y);
    this->position.push_back(z);
}

Node::~Node(){}
int Node::getData(){
    return this->data;
}
void Node::setData(int data){
    this->data = data;
}
bool Node::isVisited(){
    return this->visited;
}
void Node::setVisited(){
    this->visited = true;
} 
void Node::addChild(Node* child, int w){
    this->children.push_back(make_tuple(child, w));
}

int Node::getNumChildren(){
    return this->children.size();
}

Node * Node::getChild(int index){
    if(index < children.size()){
        return get<0>(children.at(index));
    }else{
        cout << "Node::getChild, index surpasses bounds of children list." << endl;
        return nullptr;
    }
}

void Node::reset(){
    this->visited = false;
}

vector<int> Node::getPosition(){
    return this->position;
}

void Node::setPosition(int x, int y, int z){
        this->position.push_back(x);
        this->position.push_back(y);
        this->position.push_back(z);
}

int Node::getX(){
    if(position.size() == 3)
        return position.at(0);
    else{
        cout << "Node::getx, no x position";
        return -1;
    }
}

int Node::getY(){
    if(position.size() == 3)
        return position.at(1);
    else{
        cout << "Node::getY, no y position";
        return -1;
    }
}

int Node::getZ(){
    if(position.size() == 3)
        return position.at(2);
    else{
        cout << "Node::getZ, no z position";
        return -1;
    } 
}

 void Node::addWeight(int child, double weight){
     for(int i =0; i < this->children.size(); i++){
         if(get<0>(this->children[i])->getData() == child){
            this->children[i] = make_tuple(get<0>(children[i]), weight);
         }
     }
 }

 double Node::getChildWeight(int child){
     for(int i =0; i < this->children.size(); i++){
         if(get<0>(this->children[i])->getData() == child)
            return get<1>(this->children[i]);
     }
 }

 vector<tuple<Node*, double> > Node::getChildrenList(){
     return this->children;
 }