//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
#include "AdjList.h"
#include "Node.h"

#include <iostream>

using namespace std;


void AdjList::resetNodes(){
    for(int i = 0; i < this->list.size(); i++)
        this->list[i]->reset();
}

Node* AdjList::at(int index){
    if(index > list.size()-1){
        cout << "AdjList::at, index exceeds bounds of adjlist" << endl;
        return nullptr;
    }else
        return list[index]; //returns the Node * at that index
}

void AdjList::push_back(Node * n){
    this->list.push_back(n);
}

int AdjList::size(){
    return list.size();
}

void AdjList::printList(){
    cout << "PRINTING ADJ LIST: " << endl;
        for(int i = 0; i < list.size(); i++){
            cout << endl << "Parent: " << list.at(i)->getData() << ", Position: ";
            for(int j = 0; j < list.at(i)->getPosition().size(); j++){
                cout << list.at(i)->getPosition().at(j) << ", ";
            }
            cout << "...children: ";

            vector<tuple<Node*, double> > t = list.at(i)->getChildrenList();
            for(int m = 0; m < list.at(i)->getNumChildren(); m++ ){
                cout << "(" << get<0>(t[m])->getData() << ", "<< get<1>(t[m]) << ")";
            }
        }
    cout << endl;
}

void AdjList::clear(){
    list.clear();
}

