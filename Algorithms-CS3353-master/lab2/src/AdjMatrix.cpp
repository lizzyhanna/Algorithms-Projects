//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
#include "AdjMatrix.h"
#include "Node.h"
#include <iostream>

AdjMatrix::AdjMatrix(){
    this->size = 0;
}

AdjMatrix::AdjMatrix(int size){
    this->size = size;
    this->matrix = new Edge**[size]; //create matrix

    //create rows in matrix
    for(int i = 0; i < this->size; ++i){
        matrix[i] = new Edge*[size];
    }

    //initialize with empty edges
    for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
            matrix[i][j] = new Edge();
        }
    }
}
AdjMatrix::~AdjMatrix(){
    //delete everything
    for(int i = 0; i < this->size; ++i){
        delete[] matrix[i];
    }
    delete matrix; 
}
void AdjMatrix::addEdge(MNode * a, MNode * b, double weight){
    Edge * e = new Edge(a, b, weight);
    int index1 = a->getData()-1;
    int index2 = b->getData()-1;
    this->matrix[index1][index2] = e;
}

Edge * AdjMatrix::at(int index1, int index2){
    return this->matrix[index1][index2];
}

void AdjMatrix::resize(int size){
    for(int i = 0; i < this->size; ++i){
        delete matrix[i];
    }
    //delete matrix; //this was giving me a seg fault

    this->size = size;
    this->matrix = new Edge**[size]; //create matrix

    //create rows in matrix
    for(int i = 0; i < this->size; ++i){
        matrix[i] = new Edge*[size];
    }

    //initialize with empty edges
    for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
            matrix[i][j] = new Edge();
        }
    }
    
    //copy contents?

}

int AdjMatrix::getSize(){
    return this->size;
}

void AdjMatrix::clear(){
    for(int i = 0; i < this->size; ++i){
        delete[] matrix[i];
    }
    delete matrix;
}

void AdjMatrix::print(){
   
    for(int i =0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
           if(this->matrix[i][j]->isEdge()){
                cout << "(First: "<<this->matrix[i][j]->getFirst()->getData() << ", ";
                cout << "Second: " << this->matrix[i][j]->getSecond()->getData() << ", ";
                cout << "Weight = " << this->matrix[i][j]->getWeight() << ")" << endl;
           }
        }
    }
}