//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
//Adjacency List Node
#ifndef NODE_H
#define NODE_H
#include <vector>
#include <tuple>

using namespace std;

class Node{
    private:
        int data;
        bool visited;
        vector<int> position;
        vector<std::tuple<Node*, double> > children; 

    public:
        Node();
        Node(int);
        Node(int data, int x, int y, int z);
        ~Node();
        
        int getData();
        void setData(int);

        bool isVisited();
        void setVisited(); 

        void addChild(Node*, int);
        int getNumChildren();
        Node * getChild(int index);

        void reset();

        vector<int> getPosition();
        void setPosition(int, int, int);
        int getX(); //get x coordinate
        int getY(); //get y coordinate
        int getZ(); //get z coordinate

        void addWeight(int,double);
        double getChildWeight(int);
        vector<tuple<Node*, double> > getChildrenList();
};
#endif