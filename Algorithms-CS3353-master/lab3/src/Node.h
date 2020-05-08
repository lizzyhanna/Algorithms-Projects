//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3

#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;

class Node{
    private:
        int data;
        vector<float> position;

    public:
        Node();
        Node(int data, float x, float y, float z);
        Node(const Node&);
        ~Node();
        
        int getData();
        void setData(int);

        vector<float> getPosition();
        float getX(); //get x coordinate
        float getY(); //get y coordinate
        float getZ(); //get z coordinate

        void print();

};
#endif