//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3
#include "tsp.h"
#include "Node.h"
#include "math.h"

#include <list>
#include <vector>
#include <chrono>
#include <utility>
#include <limits>
#include <string>
#include <iostream>

using namespace std;

//BRUTE FORCE APPROACH FUNCTIONS:
//Credit the The Coding Train for this approach https://www.youtube.com/watch?v=BAejnwN4Ccw
//swaps two random Nodes
void TSP::swap(int i, int j, vector<Node*> & v){
    Node * temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}//end swap


float TSP::calcDistance(vector<Node*> & v){
    float sum = 0;
    for(int i = 0; i < v.size() -1; i++){
        sum += fabs(v[i]->getX() - v[i+1]->getX()) + fabs(v[i]->getY() - v[i+1]->getY()) + fabs(v[i]->getZ() - v[i+1]->getZ());
    }
    //also get the distance to return back to the starting node
    sum += fabs(v[0]->getX() - v[v.size()-1]->getX()) + fabs(v[0]->getY() - v[v.size()-1]->getY()) + fabs(v[0]->getZ() - v[v.size()-1]->getZ());
    return sum;
}//end calcDistance


//needs to return pair of vector<int> and float
pair<vector<int>, float> TSP::bruteForce(vector<Node*> cities){
    if(cities.size() == 1){ //if there is only one city...edge case
        vector<int> p;
        p.push_back(cities[0]->getData());
        return make_pair(p,calcDistance(cities));
    } 
    float bestDistance = calcDistance(cities);
    vector<Node*> bestPath = cities;
    int largestJ;
    int firstNode = cities[0]->getData();
    while(true){
        int largestI = -1;

        for(int i = 0; i < cities.size()-1; i++){
            if(cities[i]->getData() < cities[i+1]->getData()){
                largestI = i;
            }
        }
        if(largestI == -1)
            break;

        for(int j = 0; j < cities.size(); j++){
            if(cities[j]->getData() > cities[largestI]->getData())
                largestJ = j;
        }
       
        swap(largestI,largestJ,cities);
        
        list<Node*> citylist;
        for(int b = 0; b < cities.size(); b++){
            citylist.push_back(cities[b]);
        }

        list<Node*>::iterator it = citylist.begin();
        advance(it,largestI+1);  
        list<Node*> endArray;
        endArray.splice(endArray.begin(), citylist, it, citylist.end());
        endArray.reverse();
        citylist.splice(citylist.end(), endArray); //concatenates list to the end
        int a = 0;

        //put city list back into cities vector
        for (std::list<Node*>::iterator it = citylist.begin(); it != citylist.end(); ++it){
            cities[a++] = (*it);
        }

        if(cities[0]->getData() != firstNode){
            vector<int> tour;
            for(int i = 0; i < bestPath.size(); i++){
                tour.push_back(bestPath[i]->getData());
            }
            tour.push_back(bestPath[0]->getData()); //complete the tour by returning to first node
            pair<vector<int>, float> p;
            p = make_pair(tour, bestDistance);
            return p;
        }

        int d = calcDistance(cities);
        if(d < bestDistance){ //found a better distance
            bestDistance = d;
            bestPath = cities;
        }

    }//while loop   
    
}//end bruteForce



//DYNAMIC PROGRAMMING APPROACH FUNCTIONS:
//credit to William Fiset https://www.youtube.com/watch?v=udEe7Cv3DqU&t=186s for explaining the DP approach

float TSP::calcDistance(int first, int second, vector<Node*> v){
    return fabs(v[first]->getX() - v[second]->getX()) + fabs(v[first]->getY() - v[second]->getY()) + fabs(v[first]->getZ() - v[second]->getZ());
}

//creates the adjacency matrix for dp
vector<vector<float>> TSP::createADJMatrix(vector<Node*> cities){
    vector<vector<float>> c;
    vector<float> inner;
    for(int i = 0; i < cities.size(); i++){
        inner.clear();
        for(int j = 0; j < cities.size(); j++){
            inner.push_back(calcDistance(i,j,cities)); //calculates the distance between first node and all others, pushes into vector
        }
        c.push_back(inner); //push into outer vector
        /*example final format:
        { {0, 13.4, 22, 94}
          {13.4, 0, 90, 21} etc...}
        */
    }
    return c;
}




//DYNAMIC...ORIGINAL CALLING FUNCTION
pair<vector<int>, float> TSP::dynamic(vector<Node*> cities){
    if(cities.size() == 1){
        vector<int> p;
        p.push_back(cities[0]->getData());
        return make_pair(p, 0);
    }
    vector<vector<float>> distance = createADJMatrix(cities); //adjmatrix of distances between nodes
    int n = cities.size(); //number of nodes
    int start = 0; //starting node is always first node, which is index 0

    float ** memo = new float*[n];
    for(int i = 0; i < n; i++){
        memo[i] = new float[1<<n];
    }


    //initializes memo table with -1
    for(int end = 0; end < n; end++){
        if(end==start)
            continue;
        memo[end][(1<<start)| (1<<end)] = -1; 
    }


    //solve(vector<vector<float>> distance, vector<vector<int>> memo, int s, int n, int start)
    pair<vector<int>, float> p(solve(distance, memo, 0, n, 0));
    
    //free allocated memory from adjmatrix
    for(int i = 0 ; i < n ; i++ ){
        delete[] memo[i]; // delete array within matrix
    }
    // delete actual matrix
    delete[] memo;

    return p;
 
}//end DYNAMIC(VECTOR<NODE*>)



//NOTIN
bool TSP::notIn(int element, int subset){
    //checks to see if the bit has been flipped on this element, meaning it has been put in subset or not
    //returns true if element is unvisted in subset, false if not
    return ((1<<element) & subset) == 0;
}//END NOTIN(INT,INT)


//COMBINATIONS
//returns all possible subsets with r bits set to 1
vector<int> TSP::combinations(int r, int n){
    vector<int> subsets;
    combinations_r(0,0,r,n,subsets);
    return subsets;
}//END COMBINATIONS(INT,INT)


//COMBINATIONS
void TSP::combinations_r(int set, int at, int r, int n, vector<int> & subsets){
   int elementsToPick = n-at; 

   if(elementsToPick < r) //base case
       return; 

    if(r == 0){
        subsets.push_back(set); //we found a valid subset
       // return subsets;
    }else{
        for(int i = at; i < n; i++){
            set |= 1 << i; //flip on the ith bit
            combinations_r(set,i+1, r-1, n, subsets); 

            //backtrack and flip off ith bit
            set &= ~(1<<i);
        }
    }
}//END COMBINATIONS(INT,INT,INT,INT,VECTOR<INT>)


//SOLVE
//adjacency matrix of distances, lookup table, current set (...000010), and number of nodes
pair<vector<int>, float> TSP::solve(vector<vector<float>> distance, float ** memo, int s, int n, int start){
    int END_STATE = (1<<n)-1; //what all nodes visited would look like -- all bits set to 1. example 1111
    float minTourCost = numeric_limits<float>::max();

    //memo table setup
    // equivalent to : float[][] memo = new float[n][1<<n]; //memo table of size n by 2^n
    //step 1
    for(int end = 0; end < n; end++){
        if(end==start)
            continue;
        float d = distance[start][end];    
        memo[end][(1<<start)| (1<<end)] = distance[start][end]; 
        //enters distance of all nodes into memo lookup table
    }
    

    //r is number of nodes in partially completed tour
    for(int r = 3; r <= n; r++){
        for(int subset : combinations(r,n)){ //loop through all subsets with r bits set produced by our combinations function
            
            if(notIn(start,subset)) //make sure node is in subset to create a valid tour
                continue;

            for(int next = 0; next < n; next++){ //next target node

                if(next==start || notIn(next, subset)) //can't go back to start yet, make sure the starting node is in the subset
                    continue;

                int subsetWithoutNext = subset ^ (1<<next);//this is the partially completed tour without the "next" node...flip OFF the next node
                float minDist = numeric_limits<float>::max(); 
                
                //for every possible end node that isn't the start, current node and is in our subset...
                for(int end = 0; end < n; end++){
                    if((end == start || end == next) || notIn(end, subset) ) 
                        continue;

                    //calculate new distance from n node to next node    
                    float newDistance = memo[end][subsetWithoutNext] + distance[end][next]; //calculate new distance from end node using subset and to end node using our "next" node
                    if(newDistance < minDist)
                        minDist = newDistance;
                    
                }
                memo[next][subset] = minDist; //cache in memo table
            }
        }
    }//end outermost for loop

    //finds the minimum cost/distance of a tour
    for(int i = 0; i < n; i++){
        if(i == start) //skip over starting node
            continue;
        float tourCost = memo[i][END_STATE] + distance[i][start]; //lookup in our table for start to end node + cost back to start
        if(tourCost < minTourCost){
            minTourCost=  tourCost;
        }
    }
    
    //finds the actual path of indices of the tour
    vector<int> tour;
    int lastIndex = start;
    int state = END_STATE; //start at end and work our way backwards
    tour.push_back(start);

    for(int i = 1; i < n; i++){
        int index = -1; //index of best next node
        for(int j = 0; j < n; j++){

            if(j==start || notIn(j,state))
                continue;

            if(index == -1) 
                index = j;  //first valid node we have encountered

            float prevDist = memo[index][state] + distance[index][lastIndex]; //previous index vs.
            float newDist = memo[j][state] + distance[j][lastIndex]; //current index...determine which is better
            if(newDist < prevDist)
                index = j; //j is our next best node, so update the index
        }
        tour.push_back(index); //add current index to tour
        state = state ^ (1<<index); //turn off the index bit so we don't go to it again
        lastIndex = index; //now we've backtracked to previous index
    }

    tour.push_back(start); //complete the circuit by adding the starting node at the end

    for(int i = 0; i < tour.size(); i++){
        tour[i] = tour[i] + 1; //starting node of 1 is index 0, so everything else is actually 1 higher
    }

    return make_pair(tour, minTourCost);
}//end SOLVE