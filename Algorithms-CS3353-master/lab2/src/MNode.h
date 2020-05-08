//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
//Node specifically made for Adjacency MAtrix use
#ifndef MNODE_H
#define MNODE_H
#include <vector>


using namespace std;

class MNode{
    private:
        int data;
        bool visited;
        vector<int> position;
       
    public:
        MNode();
        MNode(int);
        MNode(int data, int x, int y, int z);
        ~MNode();
        
        int getData();
        void setData(int);

        bool isVisited();
        void setVisited(); 

        void reset();

        vector<int> getPosition();
        void setPosition(int, int, int);
        int getX(); //get x coordinate
        int getY(); //get y coordinate
        int getZ(); //get z coordinate

};
#endif