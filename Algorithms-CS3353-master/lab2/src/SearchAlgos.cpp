//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 2
#include "SearchAlgos.h"
#include "Node.h"
#include "MNode.h"
#include "AdjList.h"
#include "AdjMatrix.h"

#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <set>


using namespace std;

SearchAlgos::SearchAlgos(){
}//end constructor




//ADJACENCY LIST FUNCTIONS:


//==========================================================
//Helper Functions:
//Checks to see if a node currently exists in the path
bool isNotVisited(int num, vector<int> p){
    for(int i = 0; i<p.size(); i++){
        if(p[i] == num){
            return false;
        }
    }
    return true;
}
//Calculates the total distance in the path
int calcDistance(vector<int> p, AdjList & g){
    int d = 0;
    for(int i = 1; i < p.size(); i++){
        //d = |(x1-x)| + |(y2-y)| + |(z2-z)| this is my distance formula between 2 nodes
        d += abs(g.at(p[i-1]-1)->getX() - g.at(p[i]-1)->getX())+ abs(g.at(p[i-1]-1)->getY() - g.at(p[i]-1)->getY()) + abs(g.at(p[i-1]-1)->getZ() - g.at(p[i]-1)->getZ());
    }
    return d;
}//end calcdistance


//==========================================================

//BFS Iterative for AdjList
tuple<vector<int>, int, int, double> SearchAlgos::BFSIterative(AdjList& g, int source, int dest){
    queue<vector<int> > q;
    vector<int> p;
    int nodesExplored = 0;
    p.push_back(source);
    q.push(p);
    while(!q.empty()){
        p.clear();
        p = q.front();
        q.pop();
        int last = p[p.size()-1];
        g.at(last-1)->setVisited();
        if(last == dest){
            int distance = calcDistance(p, g);
            for(int i = 0; i < g.size(); i++){
                if(g.at(i)->isVisited())
                    nodesExplored++;
            }
            for(int i = 0; i < g.size(); i++){
                g.at(i)->reset();
            }
            return make_tuple(p, nodesExplored, distance, 0);
        }

        for(int i =0; i < g.at(last-1)->getNumChildren(); i++){
            if(isNotVisited(g.at(last-1)->getChild(i)->getData(), p)){
                vector<int> newp(p);
                newp.push_back(g.at(last-1)->getChild(i)->getData());
                q.push(newp);
            }
        }
    }
        p.empty(); //no path to node found
        return make_tuple(p,0,0,0); //return empty vector
}//end BFSIterative



//==========================================================


//DFS Iterative for AdjList
tuple<vector<int>, int, int, double> SearchAlgos::DFSIterative(AdjList& g, int source, int dest){
    stack<vector<int> > s;
    vector<int> p;
    int nodesExplored =0;
    int cost = 0;
    p.push_back(source);
    s.push(p);
    while(!s.empty()){
        nodesExplored++;
        p.clear();
        p = s.top();
        s.pop();
        int last = p[p.size()-1];
        if(last == dest){
            int distance = calcDistance(p, g);
            return make_tuple(p, nodesExplored, distance, 0);
        }
        
        for(int i =0; i < g.at(last-1)->getNumChildren(); i++){
            if(isNotVisited(g.at(last-1)->getChild(i)->getData(), p)){
                vector<int> newp(p);
                newp.push_back(g.at(last-1)->getChild(i)->getData());
                s.push(newp);
            }
        }   
    }
    p.clear();
    return make_tuple(p, 0,0,0); //no path found
}//end DFSIterative



//==========================================================


//BFS Recursive helper function for AdjList
tuple<vector<int>, int, int, double> SearchAlgos::BFSR(AdjList& g, int source, int dest, int last, int nodesExplored, queue<vector<int> > q){
    vector<int> p;    
    p.clear();
    if(q.empty())
        return make_tuple(p,0,0,0); //no path to node found
    
    p = q.front();
    q.pop();
    last = p[p.size()-1];
    nodesExplored++;
    if(last == dest){
        int distance = calcDistance(p, g);
        return make_tuple(p, nodesExplored, distance, 0); //path to node found
    }

    //push children onto queue
    for(int i =0; i < g.at(last-1)->getNumChildren(); i++){
        if(isNotVisited(g.at(last-1)->getChild(i)->getData(), p)){
            vector<int> newp(p);
            newp.push_back(g.at(last-1)->getChild(i)->getData());
            q.push(newp);
        }
    }

    return BFSR(g, source, dest, last, nodesExplored, q);
}//end BFSR


//BFS Recursive for AdjList
tuple<vector<int>, int, int, double> SearchAlgos::BFSRecursive(AdjList& g, int source, int dest){
    queue<vector<int> > q;
    vector<int> p;
    p.push_back(source);
    q.push(p);
    return BFSR(g, source, dest, source, 0, q);
}//end BFSRecursive
        


//==========================================================


//DFS Recursive Helper function for AdjList
tuple<vector<int>, int, int, double> SearchAlgos::DFSR(AdjList& g, int source, int dest, int last, int nodesExplored, stack <vector<int> > s){
    vector<int> p;    
    p.clear();
    if(s.empty())
        return make_tuple(p, 0, 0, 0); //no path to node found
    
    p = s.top();
    s.pop();
    last = p[p.size()-1];
    nodesExplored++;
    if(last == dest){
        int distance = calcDistance(p, g);
        return make_tuple(p, nodesExplored, distance, 0); //path to node found
    }

    //push children onto stack
    for(int i =0; i < g.at(last-1)->getNumChildren(); i++){
        if(isNotVisited(g.at(last-1)->getChild(i)->getData(), p)){
            vector<int> newp(p);
            newp.push_back(g.at(last-1)->getChild(i)->getData());
            s.push(newp);
        }
    }

    return DFSR(g, source, dest, last, nodesExplored, s);
   
}//end DFSR


//DFS Recursive for AdjList
tuple<vector<int>, int, int, double> SearchAlgos::DFSRecursive(AdjList& g, int source, int dest){
    stack<vector<int> > s;
    vector<int> p;
    p.push_back(source);
    s.push(p);
    return DFSR(g, source, dest, source, 0, s);
    
}//end DFSRecursive



//==========================================================

//Djikstra for AdjList
tuple<vector<int>, int, int, double> SearchAlgos::Dijkstra(AdjList& g, int source, int dest){
    typedef pair<int, Node*> p; //<weight, Node*>
    vector<pair<Node*, int> > allNodes; //<Node, weight>
    set<int> visited;
    priority_queue<p, vector<p>, greater<p> > pq;
    pq.push(make_pair(0, g.at(source-1)));

    for(int i = 0; i < g.size(); i++){ //add all nodes with infinite weights
        if(i == source-1){ //skip the source since we already pushed it
            allNodes.push_back(make_pair(g.at(i), 0));
            continue;
        }
        allNodes.push_back(make_pair(g.at(i), INT_MAX));
        pq.push(make_pair(INT_MAX, g.at(i))); //make initial weight = infinity
    }

    while(!pq.empty()){
        int parentWeight = get<0>(pq.top());
        Node * last = get<1>(pq.top());

        //add to visited set if not already in it
        set<int>::iterator it = visited.find(last->getData());
        if(it == visited.end()) 
            visited.insert(last->getData());

        //if we reached destination
        if(last->getData() == dest){
            vector<int> path; //I need to backtrack to find the path
            int distance = 0; //then calculate the distance from the path
             //returns path, nodesExplored, distance, weight
            return make_tuple(path, visited.size(), distance, parentWeight);
        }

        pq.pop();
        for(int i = 0; i < last->getNumChildren(); i++){ //for all children of current node
            int newWeight = parentWeight + last->getChildWeight(i); //calculate distance from parent to child
            if(newWeight < allNodes[last->getChild(i)->getData()-1].second ){ //if the distance is less, update the distance
                allNodes[last->getChild(i)->getData()-1].second = newWeight;
                pq.push(make_pair(newWeight, last->getChild(i)));
            }
        }
        
    }  
    //we did not find destination
    vector<int> path;
    return make_tuple(path, visited.size(), 0,0);  
}//end Djikstra for AdjList


//==========================================================

//helper function for AdjList A*
int calcNDistance(Node * a, Node * b){
    //d = |(x1-x)| + |(y2-y)| + |(z2-z)| this is my distance formula between 2 nodes
    return abs(a->getX() - b->getX()) + abs(a->getY() - b->getY()) + abs(a->getZ() - b->getZ());
}//end calcdistance

//this struct is used in my priority queue in a* to keep track of distance, weight, heuristic, etc.
struct S
{
    int cost;
    int weight;
    int distance;
    Node * p;

    S(int n1, int n2, int n3, Node* p) : cost(n1), weight(n2), distance(n3), p(p){}

    bool operator<(const struct S& other) const{
        return cost < other.cost;
    }
    
};

tuple<vector<int>, int, int, double> SearchAlgos::aStar(AdjList& g, int source, int dest){
    vector<pair<Node*, int> > allNodes; //this will keep track of each node and its heuristic value
    set<int> visited; //set of all visited nodes
    priority_queue<S> pq;
    S x = S(0,0,0,g.at(source-1));
    pq.push(x);

    for(int i = 0; i < g.size(); i++){ //add all nodes with infinite distance + weight
        if(i == source-1){ //skip the source since we already pushed it
            allNodes.push_back(make_pair(g.at(i), 0));
            continue;
        }
        allNodes.push_back(make_pair(g.at(i), INT_MAX));
        S v = S(INT_MAX, INT_MAX, INT_MAX, g.at(i));
        pq.push(v); //make initial distance = infinity
    }

    while(!pq.empty()){
        int ptotal = pq.top().cost; //heuristic value
        int pweight = pq.top().weight;
        int pdistance = pq.top().distance;
        Node * last = pq.top().p;
        pq.pop();

        //add to visited set if not already in it
        set<int>::iterator it = visited.find(last->getData());
        if(it == visited.end()) 
            visited.insert(last->getData());

        //if we reached destination
        if(last->getData() == dest){
            vector<int> path; //I need to backtrack to find the path
             //returns path, nodesExplored, distance, cost
            return make_tuple(path, visited.size(), pdistance , pweight);
        }


        for(int i = 0; i < last->getNumChildren(); i++){ //for all children of current node
            int newDistance = pdistance + calcNDistance(last, last->getChild(i)); //calculate distance from parent to child
            int newWeight = pweight + last->getChildWeight(i);
            int newTotal = ptotal + (newDistance * (newWeight+1)); //heuristic
            if(newTotal < allNodes[last->getChild(i)->getData() - 1].second ){ //if the weight is less, update the distance
                allNodes[last->getChild(i)->getData() - 1].second = newTotal;
                S w = S(newTotal, newWeight, newDistance, g.at(last->getChild(i)->getData() - 1));
                pq.push(w);
            }
        }
        
    }  
    //we did not find destination
    vector<int> path;
    return make_tuple(path, visited.size(), 0,0);  
}

//==========================================================











//ADJACENCY MATRIX FUNCTIONS:



// int calcDistanceMatrix(AdjMatrix& g, vector<int> p){
//     int d = 0;
//     for(int i = 1; i < p.size(); i++){
//         //d = |(x1-x)| + |(y2-y)| + |(z2-z)| this is my distance formula between 2 nodes
//         for(int j = 0; j < g.getSize(); j++){
//             if(g.at(p[i], j)->isEdge == true){
//                 d += abs(g.at(p[i])->getFirst()->getX() - )
//             }
//         }
//         d += abs(g.at(p[i-1]-1)->getX() - g.at(p[i]-1)->getX())+ abs(g.at(p[i-1]-1)->getY() - g.at(p[i]-1)->getY()) + abs(g.at(p[i-1]-1)->getZ() - g.at(p[i]-1)->getZ());
//     }
//     return d;
// }
//==========================================================
//BFS Iterative for AdjMatrix
tuple<vector<int>, int, int, double> SearchAlgos::BFSIMatrix(AdjMatrix&g, int source, int dest){
    queue<vector<int> > q;
    vector<int> p;
    int nodesExplored = 0;
    int distance = 0;
    p.push_back(source);
    q.push(p);
    while(!q.empty()){
        p.clear();
        p = q.front();
        q.pop();
        int last = p[p.size()-1];
        
        if(last == dest){
           // int distance = calcDistanceMatrix(p, g);
            //nodes Explored
            //reset g visited
            return make_tuple(p, nodesExplored, distance, 0);
        }
     for(int i =0; i < 1; i++){
        for(int j = 0; j < g.getSize(); j++){
            if(g.at(last-1, j)->isEdge() == true){
                if(isNotVisited(g.at(last-1, j)->getSecond()->getData(), p)){
                    vector<int> newp(p);
                    newp.push_back(g.at(last-1,j)->getSecond()->getData());
                    q.push(newp);
                }
            }
        }
     }
    }//end while loop

    p.clear();
    return make_tuple(p, 0,0,0); //no path found
}//end BFSIMatrix


//==========================================================


//BFS Recusrive Helper function for AdjMatrix
tuple<vector<int>, int, int, double> SearchAlgos::BFSRHelp(AdjMatrix& g, int source, int dest, int last, int nodesExplored, queue<vector<int> > q){
    vector<int> p;    
    p.clear();
    if(q.empty())
        return make_tuple(p,0,0,0); //no path to node found
    
    p = q.front();
    q.pop();
    last = p[p.size()-1];
    nodesExplored++;
    if(last == dest){
        //int distance = calcDistance(p, g);
        int distance = 0;
        return make_tuple(p, nodesExplored, distance, 0); //path to node found
    }

    //push children onto queue
   for(int i =0; i < 1; i++){
        for(int j = 0; j < g.getSize(); j++){
            if(g.at(last-1, j)->isEdge() == true){
                if(isNotVisited(g.at(last-1, j)->getSecond()->getData(), p)){
                    vector<int> newp(p);
                    newp.push_back(g.at(last-1,j)->getSecond()->getData());
                    q.push(newp);
                }
            }
        }
     }

    return BFSRHelp(g, source, dest, last, nodesExplored, q);
}



//BFS Recursive for AdjMatrix
tuple<vector<int>, int, int, double> SearchAlgos::BFSRMatrix(AdjMatrix& g, int source, int dest){
    queue<vector<int> > q;
    vector<int> p;
    p.push_back(source);
    q.push(p);
    return BFSRHelp(g, source, dest, source, 0, q);
}//end BFSRMatrix


//==========================================================


//DFS Iterative for AdjMatrix
tuple<vector<int>, int, int, double> SearchAlgos::DFSIMatrix(AdjMatrix& g, int source, int dest){
    stack<vector<int> > s;
    vector<int> p;
    int nodesExplored = 0;
    int distance = 0;
    p.push_back(source);
    s.push(p);
    while(!s.empty()){
        p.clear();
        p = s.top();
        s.pop();
        int last = p[p.size()-1];
        
        if(last == dest){
           // int distance = calcDistanceMatrix(p, g);
            //nodes Explored
            //reset g visited
            return make_tuple(p, nodesExplored, distance, 0);
        }

        for(int i =0; i < 1; i++){ //only go through one row
            for(int j = 0; j < g.getSize(); j++){ //got thru every edge on that row
                if(g.at(last-1, j)->isEdge() == true){
                     if(isNotVisited(j+1, p)){
                            vector<int> newp(p);
                            newp.push_back(g.at(last-1,j)->getSecond()->getData());
                            s.push(newp);
                    }
                }
             }
        }
    }//end while loop
    p.clear();
    return make_tuple(p, 0,0,0); //no path found
}//end DFSIMatrix

//==========================================================

//DFS Recusrive for AdjMatrix
tuple<vector<int>, int, int, double> SearchAlgos::DFSRMatrix(AdjMatrix& g, int source, int dest){
    stack<vector<int> > s;
    vector<int> p;
    p.push_back(source);
    s.push(p);
    return DFSRHelp(g, source, dest, source, 0, s);

}//end DFSRMatrix


//DFS Recursive Helper function for ADJMatrix
tuple<vector<int>, int, int, double> SearchAlgos::DFSRHelp(AdjMatrix&g, int source, int dest, int last, int nodesExplored, stack<vector<int> > s){
    vector<int> p;    
    p.clear();
    if(s.empty())
        return make_tuple(p,0,0,0); //no path to node found
    
    p = s.top();
    s.pop();
    last = p[p.size()-1];
    nodesExplored++;
    if(last == dest){
        //int distance = calcDistance(p, g);
        int distance = 0;
        return make_tuple(p, nodesExplored, distance, 0); //path to node found
    }

    //push children onto stack
   for(int i =0; i < 1; i++){
        for(int j = 0; j < g.getSize(); j++){
            if(g.at(last-1, j)->isEdge() == true){
                if(isNotVisited(g.at(last-1, j)->getSecond()->getData(), p)){
                    vector<int> newp(p);
                    newp.push_back(g.at(last-1,j)->getSecond()->getData());
                    s.push(newp);
                }
            }
        }
     }

    return DFSRHelp(g, source, dest, last, nodesExplored, s);
 }//end DFSRHelp
//==========================================================


//helper function for Matrix Dijkstra
int calcMNDistance(MNode * a, MNode * b){
    //d = |(x1-x)| + |(y2-y)| + |(z2-z)| this is my distance formula between 2 nodes
    return abs(a->getX() - b->getX())+ abs(a->getY() - b->getY()) + abs(a->getZ() - b->getZ());
}//end calcdistance

// //Djikstra for AdjMatrix
tuple<vector<int>, int, int, double> SearchAlgos::DjikstraMatrix(AdjMatrix& g, int source, int dest){
    typedef pair<int, int> p;  //<weight, Node number>
    vector<pair<int, int> > allNodes; //<Node number, weight>
    set<int> visited;
    priority_queue<p, vector<p>, greater<p> > pq; 

    pq.push(make_pair(0, source));
    for(int i = 0; i < g.getSize(); i++){ //add all nodes with infinite distance
        if(i == source-1){ //skip the source since we already pushed it
            allNodes.push_back(make_pair(source, 0));
            continue;
        }
        allNodes.push_back(make_pair(i+1, INT_MAX));
        pq.push(make_pair(INT_MAX, i+1)); //make initial weight = infinity
    }

    while(!pq.empty()){
        int parentWeight = get<0>(pq.top());
        int last = get<1>(pq.top());

        //add to visited set if not already in it
        set<int>::iterator it = visited.find(last);
        if(it == visited.end()) 
            visited.insert(last);

        //if we reached destination
        if(last == dest){
            vector<int> path; //I need to backtrack to find the path
             //returns path, nodesExplored, distance, weight
             int distance = 0;
            return make_tuple(path, visited.size(), distance, parentWeight);
        }

        pq.pop();

        for(int i = 0; i < g.getSize(); i++){ //for all children of current node
            if(g.at(last-1, i)->isEdge() == true){
                int newWeight = parentWeight + g.at(last-1, i)->getWeight(); //calculate distance from parent to child
                if(newWeight < allNodes[g.at(last-1, i)->getSecond()->getData() -1 ].second){ //if the distance is less, update the distance
                    allNodes[g.at(last-1, i)->getSecond()->getData() -1].second = newWeight;
                    pq.push(make_pair(newWeight, g.at(last-1, i)->getSecond()->getData()));
                }
            }
        } 
    }  
    //we did not find destination
    vector<int> path;
    return make_tuple(path, visited.size(), 0,0);  
}//end DjikstraMatrix


//==========================================================
//helper struct for A*
//this struct is used in my priority queue in a* to keep track of distance, weight, heuristic, etc.
struct T
{
    int cost;
    int weight;
    int distance;
    int p;

    T(int n1, int n2, int n3, int p) : cost(n1), weight(n2), distance(n3), p(p)
    {
    }

    bool operator<(const struct T& other) const
    {
        //Your priority logic goes here
        return cost < other.cost;
    }
    
};

// //A* for AdjMatrix
tuple<vector<int>, int, int, double> SearchAlgos::AStarMatrix(AdjMatrix& g, int source, int dest) {
    vector<pair<int, int> > allNodes; //this will keep track of each node and its heuristic value
    set<int> visited; //set of all visited nodes
    priority_queue<T> pq;
    T x = T(0,0,0,source);
    pq.push(x);

    for(int i = 0; i < g.getSize(); i++){ //add all nodes with infinite distance + weight
        if(i == source-1){ //skip the source since we already pushed it
            allNodes.push_back(make_pair(source, 0));
            continue;
        }
        allNodes.push_back(make_pair(i+1, INT_MAX));
        T v = T(INT_MAX, INT_MAX, INT_MAX, i+1);
        pq.push(v); //make initial distance = infinity
    }

    while(!pq.empty()){
        int ptotal = pq.top().cost; //heuristic value
        int pweight = pq.top().weight;
        int pdistance = pq.top().distance;
        int last = pq.top().p;
        pq.pop();

        //add to visited set if not already in it
        set<int>::iterator it = visited.find(last);
        if(it == visited.end()) 
            visited.insert(last);

        //if we reached destination
        if(last == dest){
            vector<int> path; //I need to backtrack to find the path
             //returns path, nodesExplored, distance, cost
            return make_tuple(path, visited.size(), pdistance , pweight);
        }


        for(int i = 0; i < g.getSize(); i++){ //for all children of current node
            if(g.at(last-1, i)->isEdge() == true){
                int newDistance = pdistance + calcMNDistance(g.at(last-1, i)->getFirst(), g.at(last-1, i)->getSecond());
                int newWeight = pweight + g.at(last-1, i)->getWeight();
                int newTotal = ptotal + (newDistance * (1 + newWeight)); //heuristic calculation
                if(newTotal < allNodes[g.at(last-1, i)->getSecond()->getData()-1].second){
                    allNodes[g.at(last-1, i)->getSecond()->getData()-1].second = newTotal;
                    T w = T(newTotal, newWeight, newDistance, g.at(last-1, i)->getSecond()->getData());
                    pq.push(w);
                }
            }
        }
        
    }  

//we did not find destination
    vector<int> path;
    return make_tuple(path, visited.size(), 0,0);  
}//end AStarMatrix