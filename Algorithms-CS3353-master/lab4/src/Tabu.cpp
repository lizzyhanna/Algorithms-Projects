//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 4
#include "Tabu.h"
#include "Node.h"
#include <vector>
#include <utility>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <deque>
#include <random>
#include <fstream>

using namespace std;

//technique 1 for tabuList size: 15
Tabu::Tabu(){
    this->bestDistance = numeric_limits<float>::max();
    this->listSize = 100; //default list size
    this->hoodSize = 100;
    this->neighborhoodTechnique = 0;
    this->timer = 1600;
    this->targetD = 0;
    srand (time(NULL)); //seed the random number generator with time
}

//technique 2 for tabuList size: user input
Tabu::Tabu(int size, int technique, float targetD, int timer){
    this->bestDistance = numeric_limits<float>::max();
    this->listSize = size; 
    this->hoodSize = 100;
    this->neighborhoodTechnique = technique;
    this->targetD = targetD;
    this->timer = timer;
    srand (time(NULL)); //seed the random number generator with time
}

//the algorithm
pair<vector<int>, float> Tabu::tabuSearch(vector<Node*> cities){
    cout << "Beginning Tabu Search. . ." << endl;
    //edge cases
     if(cities.size() == 1){ //if there is only one city
        vector<int> p;
        p.push_back(cities[0]->getData());
        return make_pair(p,0);
    }else if(cities.size() <= 0){   //if there are 0 or fewer nodes
        exit(1);
    } 

    this->listSize = cities.size() * 3; //automatic tabu list size

    //clock variables
    int startTime = clock();
    int currentTime = 0;
    int count = 0;

    //start at a random solution
    vector<int> current;
    for(int i = 0; i < cities.size(); i++){
       current.push_back(cities[i]->getData());
    }
   
    vector<vector<float>> c = createADJMatrix(cities); 

    vector<int> start = current;
    float startD = numeric_limits<float>::max();
    //five random starting places...select the best one
    for(int i = 0; i < 5; i++){
        restart(start);
        float d = calcDistance(start,c);
        if(d < startD){
            current = start;
            startD = d;
        }
    }
    makeTabu(current);
    this->bestEver = current;
    this->bestDistance = calcDistance(current, c);
    int currentIndex = 0; 

    ofstream myfile;
    myfile.open("tabu100current.txt");
    if(!myfile){
        cout << "error opening file"; 
        exit(1);
    }
    ofstream bestfile;
    bestfile.open("tabu100best.txt");
    if(!bestfile){
        exit(1);
    }

    int lastTime = 0;
    int nonUpdate = 0;
    

    //start the search
    while(currentTime <= timer/*seconds*/){ //clock condition...runs for 60 sec
        currentTime = (clock() - startTime) / CLOCKS_PER_SEC;
        if(bestDistance <= targetD){ //end loop if we find the optimal known solution
            bestEver.push_back(bestEver[0]);
            cout << "Best distance before return= " << bestDistance << endl;
            return make_pair(bestEver,bestDistance);
        }

        //define neighborhood based on current solution
        vector<vector<int> > neighborhood = getNeighborhood(current);

        //eliminate neighbors on tabu list and find distances of all non-tabu neighbors
        int tabuElements = 0;
        int s = neighborhood.size();
        int counter = 0;

        for(int i = neighborhood.size(); i > 0; i--){
            for(int j = 0; j > tabuList.size(); j++){
                if(neighborhood[i] == this->tabuList[i]){
                    neighborhood.erase(neighborhood.begin()+i);
                    tabuElements++;
                }
            }               
       }

        vector<float> distances;
        for(int i = 0; i < neighborhood.size(); i++){
            distances.push_back(calcDistance(neighborhood[i], c));
        }

        if(tabuElements >= this->hoodSize){ //all neighbors are tabu...random restart
            restart(current);
            continue;
        }
    
        //roulette probability to choose the next neighbor
        currentIndex = roulette(distances); 
        current = neighborhood[currentIndex];
        //add chosen neighbor to tabu list
        makeTabu(current);

        //print to file our current location in solution space
        currentTime = (clock() - startTime) / CLOCKS_PER_SEC;
        if(currentTime > lastTime){
            lastTime = currentTime;
            myfile << currentTime << "," << distances[currentIndex] << endl;
        }
        
        //update bestDistance and bestEver if necessary
        if(distances[currentIndex] < bestDistance && distances[currentIndex] > 0){
            this->bestDistance = distances[currentIndex];
            this->bestEver = current;
            bestfile << counter << "," << this->bestDistance << endl;
        }else{
            nonUpdate++;
        }

       //random restart
        if(nonUpdate > 2000){
            //if it hasn't updated score in 1000 loops, may be stuck in local minima...
            restart(current);
            nonUpdate = 0;
        }

        counter++;
    
    }//while loop

    myfile.close();

    bestEver.push_back(bestEver[0]); //adds first node back to complete circuit
    //returns best tour and best distance found
    return make_pair(bestEver,bestDistance);
}

//calculates distance between two nodes 
float Tabu::calcDistance(int first, int second, vector<Node*> v){
    return fabs(v[first]->getX() - v[second]->getX()) + fabs(v[first]->getY() - v[second]->getY()) + fabs(v[first]->getZ() - v[second]->getZ());
}

//calculates distance of an entire tour using an adjacency matrix
float Tabu::calcDistance(vector<int> tour, vector<vector<float>> c){
    float dist = 0;
    for(int j = 0; j < tour.size()-1; j++){
        dist += c[tour[j]-1][tour[j+1]-1]; 
    }
    dist += c[tour[0]-1][tour[tour.size()-1]-1];
    return dist;
}


vector<vector<float>> Tabu::createADJMatrix(vector<Node*> cities){
    vector<vector<float>> c;
    vector<float> inner;
    float d = 0;
    for(int i = 0; i < cities.size(); i++){
        inner.clear();
        for(int j = 0; j < cities.size(); j++){
            //calculates the distance between first node and all others, pushes into vector
            d = calcDistance(i,j,cities);
            inner.push_back(d); 
        }
        c.push_back(inner); //push into outer vector
        /*example final format:
        { {0, 13.4, 22, 94}
          {13.4, 0, 90, 21} etc...}
        */
    }
    return c;
}

//shuffles a given tour a random number of times
void Tabu::myshuffle(vector<int> & current){
    for(int i = 0; i < (rand()%10 +1); i++){
        int indexA = rand() % (current.size()-1) + 1;
        int indexB = rand() % (current.size()-1) + 1;
        myswap(current, indexA, indexB); 
    }
    int reverse = rand() % 2 + 1; //either 1 or 2
    if(reverse == 1){
        std::reverse(current.begin() + 1, current.end());
    }

}

void Tabu::restart(vector<int> & current){
    //more hearty shuffle function
    for(int i = 0; i < 100; i++){
        int indexA = rand() % (current.size()-1) + 1;
        int indexB = rand() % (current.size()-1) + 1;
        myswap(current, indexA, indexB); 
        std::reverse(current.begin() + (rand()% (current.size()-1) + 1), current.end());
    }
}

//swaps two elements in a tour
void Tabu::myswap(vector<int> & current, int indexA, int indexB){
    int temp = current[indexA];
    current[indexA] = current[indexB];
    current[indexB] = temp;
}

//swaps two elements in a tour but accepts the vector by value not reference
vector<int> Tabu::myswapValue(vector<int> current, int indexA, int indexB){
    int temp = current[indexA];
    current[indexA] = current[indexB];
    current[indexB] = temp;
    return current;
}

//adds a solution to the tabu list
void Tabu::makeTabu(vector<int> tour){
    if(this->tabuList.size() >= this->listSize){
        tabuList.pop_front(); //remove the oldest element
        tabuList.push_back(tour);    
    }else{
        tabuList.push_back(tour);
    }

}


//chooses an index using roulette function
int Tabu::roulette(vector<float> & distances){
    vector<double> normalized = normalizeDistance(distances);
    int index = 0;
    //best distance every time
    float bestD = INT_MAX;
    for(int i = 0; i < distances.size(); i++){
        if(distances[i] < bestD){
            bestD = distances[i];
            index = i;
        }
    }

    //1/20 of the time will do roulette
    int randomSelect= rand() % 20 + 1;
    if(randomSelect == 5){
        index =0;
          //random number gen from cpp reference
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int>dis(0, normalized[normalized.size()-1]); 
        int r = dis(gen); //random number between 0 and 1
        while(true){
            if(r <= normalized[index++])
                break;
        }
        index--;    
    }
    if(index < 0 || index > normalized.size()-1){
        return rand()%(normalized.size()-1) + 1;
    }
    return index; //index of the next neighbor
}


//turns the distances into fitness values, then distributes them across an array for roulette
vector<double> Tabu::normalizeDistance(vector<float> & distances){
    float sum = 0;
    vector<float> d;
    vector<double> fitness;
    float maxD = *max_element(distances.begin(), distances.end());
    //invert distances so larger distance = less chance of selection
    for(int i = 0; i < distances.size(); i++){
            sum += (maxD - (distances[i] + 1));
            fitness.push_back(sum);
    }
    return fitness;
}


//generates a neighborhood in 1 of 2 ways depending on chosen method
vector<vector<int> > Tabu::getNeighborhood(vector<int> current){
    vector<vector<int> > neighborhood;
    //technique 1...
    if(this->neighborhoodTechnique == 0)
        neighborhood = spotExchange(current);

    //technique 2...
    else{
        for(int i = 0; i < this->hoodSize; i++){
            vector<int> neighbor = myswapValue(current, (rand() % (current.size()-1) + 1), (rand() % (current.size()-1) + 1));
            neighborhood.push_back(neighbor);
        }
    }
    return neighborhood;
}


/*spotExchange is one way of generating a neighborhood by moving one element
at a time through each place in the tour
this should hopefully replace each neighbor in each spot
        ex. 1 2 3 4 5 would become...
        (2 in every spot)
        1 3 2 4 5
        1 4 3 2 5
        1 5 3 4 2

        (3 in every spot)
        1 2 4 3 5
        1 2 3 5 4
        ...and then some random ones bc neighborhood size is too big
        
*/
vector<vector<int> > Tabu::spotExchange(vector<int> & current){
    vector<vector<int> > neighborhood;
    //since we are starting with graphs with >4 nodes, this is fine
    int indexA = 2;
    int indexB = 1;
    for(int m = 0; m < hoodSize; m++){
        vector<int> neighbor = current;

        if(indexA <= neighbor.size()-1 && indexB <= neighbor.size()-1){
            myswap(neighbor,indexB,indexA++); 
        }else if(indexA > neighbor.size()-1 && indexB > neighbor.size()-1){
            //ran out of indices to swap, start doing random shuffles
            myshuffle(neighbor);
        }else{
            indexA = 1; // ? //indexA++;
            indexB++;
        }
        neighborhood.push_back(neighbor);    
    }
    return neighborhood;
}