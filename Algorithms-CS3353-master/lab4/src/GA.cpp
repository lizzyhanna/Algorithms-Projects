//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 4
#include "GA.h"
#include "Node.h"
#include "math.h"
#include <vector>
#include <utility>
#include <time.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <random>
#include <unordered_set>

using namespace std;

GA::GA(){ //default (best) config
    this->bestDistance = numeric_limits<float>::max();
    this->popSize = 50;
    this->timer = 1600;
    this->mutationRate = 10; //mutate 10% of time
    this->mutationTechnique = 1;
    this->selectionTechnique = 2;
    this->crossoverTechnique = 1;
    this->targetD = -1;
    srand(time(NULL)); //seed the random number generator with time
}

GA::GA(int popSize, int timer, int mutationRate, int mutationTechnique, int selectionTechnique, int crossoverTechnique, float targetD){
    this->bestDistance = numeric_limits<float>::max();
    this->popSize = popSize;
    this->timer = timer;
    this->mutationRate = mutationRate; 
    this->mutationTechnique = mutationTechnique;
    this->selectionTechnique = selectionTechnique;
    this->crossoverTechnique = crossoverTechnique;
    this->targetD = targetD;
    srand(time(NULL)); //seed the random number generator with time
}


pair<vector<int>, float> GA::gaSearch(vector<Node*> cities){
    std::cout<< "Beginning gaSearch. . ." <<endl;
    //Edge Cases
    if(cities.size() == 1){         //if there is only one city
        vector<int> p;
        p.push_back(cities[0]->getData());
        return make_pair(p,0);
    }else if(cities.size() <= 0){   //if there are 0 or fewer nodes
        exit(1);
    }

    //creates an adjacency matrix so we don't have to continually recalculate distances between singular nodes
    vector<vector<float>> c = createADJMatrix(cities); 

    //create the initial population
    vector<int> fitnesses;
    vector<vector<int> > population;
    vector<int> path;
    
    for(int i = 0; i < cities.size(); i++){
        path.push_back(cities[i]->getData());
    }

    for(int i = 0; i < this->popSize; i++){
        intenseShuffle(path);
        population.push_back(path);
    }

    int startTime = clock();
    int currentTime = 0;

    ofstream myfile;
    // myfile.open("GA100Tech5.txt");
    // if(!myfile){
    //     std::cout << "error opening file"; 
    //     exit(1);
    // }
    // ofstream bestfile;
    // bestfile.open("GA100Tech5Best.txt");
    // if(!bestfile){
    //     exit(1);
    // }
    this->currentDistance = 0;
    int count = 0; //generation
    float lastDistance = this->bestDistance;
    int lastTime = 0;
    while(currentTime <= this->timer){ 
        if(this->bestDistance <= this->targetD){
            bestEver.push_back(bestEver[0]);
            return make_pair(bestEver,bestDistance);
        }

        currentTime = (clock() - startTime) / CLOCKS_PER_SEC;
        if(currentTime > lastTime){
            lastTime = currentTime;
           // myfile << currentTime << "," << this->currentDistance << endl;
        }
         //cout << count<< "," << this->currentDistance << endl;
        //myfile << count<< "," << this->currentDistance << endl;
        fitnesses = calculateFitness(population, c); //calculates fitness score of pop
        normalizeFitness(fitnesses); //normalizes fitnesses
        nextGeneration(population, fitnesses); //generates a new population
        count++;
        if(lastDistance != this->bestDistance){
           std::cout << "NEW BEST! " << this->bestDistance << endl; 
           //bestfile << count << "," << this->bestDistance << endl;
           lastDistance = this->bestDistance;
        }
        count++;
    }

    //bestfile.close();
    //myfile.close();
    bestEver.push_back(bestEver[0]); //loop the circuit back
    //returns best tour and best distance found
    return make_pair(bestEver,bestDistance);
}

float GA::calcDistance(int first, int second, vector<Node*> v){
    return fabs(v[first]->getX() - v[second]->getX()) + fabs(v[first]->getY() - v[second]->getY()) + fabs(v[first]->getZ() - v[second]->getZ());
}

float GA::calcDistance(vector<int> tour, vector<vector<float>> c){
    int dist = 0;
    for(int j = 0; j < tour.size()-1; j++){
        dist += c[tour[j]-1][tour[j+1]-1]; 
    }
    dist += c[tour[0]-1][tour[tour.size()-1]-1];
    return dist;
}


vector<vector<float>> GA::createADJMatrix(vector<Node*> cities){
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


void GA::myswap(vector<int> & population, int indexA, int indexB){
    int temp = population[indexA];
    population[indexA] = population[indexB];
    population[indexB] = temp;
}


//creates initial population via random swapping
void GA::shuffle(vector<int> & order){
    int indexA = rand() % (order.size()-1) + 1;
    int indexB = rand() % (order.size()-1) + 1;
    myswap(order, indexA, indexB);   
}


//super shuffles an order around
void GA::intenseShuffle(vector<int>& order){
     for(int i = 0; i < 100; i++){
        int indexA = rand() % (order.size()-1) + 1;
        int indexB = rand() % (order.size()-1) + 1;
        myswap(order, indexA, indexB); 
        std::reverse(order.begin() + (rand()% (order.size()-1) + 1), order.end());
    }
}


//turns a measurement of distance into a fitness value
vector<int> GA::calculateFitness(vector<vector<int> > & population, vector<vector<float>> & c){
    vector<int> fitness;
    this->distances.clear();
    float currentD = numeric_limits<float>::max();
    float largestD = 0;
    for(int i = 0; i < population.size(); i++){
        float dist = 0;
        dist = calcDistance(population[i], c);
        this->distances.push_back(dist); //in case dist = 0

        //check if this is the best we've found so far
        if(dist < this->bestDistance && dist > 0){
            this->bestDistance = dist;
            this->lastBest = this->bestEver;
            this->bestEver = population[i];
        }
        if(dist < currentD && dist > 0){
            currentD = dist;
            this->currentBest = population[i];
        }
        if(dist > largestD)
            largestD = dist;
        
    }
    for(int i = 0; i < distances.size(); i++){
        fitness.push_back(largestD - this->distances[i] + 1);      
    }
    return fitness;
}


//turn the fitness values into a distributed array
void GA::normalizeFitness(vector<int> & fitnesses){
    float sum = 0;
    for (int i = 0; i < fitnesses.size(); i++){
        sum += fitnesses[i];
        fitnesses[i] = sum;
    }
}

//mutation...technique is handled here
void GA::mutate(vector<int> & order){
    if(this->mutationTechnique==1){
        crossover(order);
    }else{
        intenseShuffle(order);
    }
}


//create the next generation, using the techniques provided by the class
void GA::nextGeneration(vector<vector<int> > & population, vector<int> & fitness){
    vector<vector<int> > newPop;
    int m = 0; //used mutation 
    //crossover technique 1, two parents...
    if(this->crossoverTechnique == 1){
        vector<int> parent1;
        vector<int> parent2;
        //tecnique 1 for finding parents...roulette wheel selection
        if(this->selectionTechnique==1){
            int index1 = roulette(population, fitness);
            parent1 = population[index1];
            int index2 = roulette(population, fitness, parent1);
            parent2 = population[index2];

            this->currentDistance = this->distances[index1];
        }else{
        //technique 2 for finding parents...just choose best 2 fitness scores
            int topFitness = 0;
            int topIndex = 1;
            int secondIndex= 0;

            for(int i = 0; i < fitness.size(); i++){
                if(fitness[i] > topFitness){
                    secondIndex = topIndex;
                    topFitness = fitness[i];
                    topIndex = i;
                }
            }
            parent1 = population[topIndex];
            parent2 = population[secondIndex];

            this->currentDistance = this->distances[topIndex];
        }
            //top 2 performers
            int topfit = 0;
            int top1 = 0;
            int top2 = 0;
            for(int i = 0; i < fitness.size(); i++){
                if(fitness[i] > topfit){
                    top2 = top1;
                    topfit= fitness[i];
                    top1 = i;
                }
            }
            vector<int> sub = lcs(population[top1], population[top2]);
            int choice = rand() % 2 + 1;
            for(int i = 0; i < population.size(); i++){
                if(i==population.size() - 1){
                    sub.clear();
                    sub = lcs(this->lastBest, this->bestEver);
                }
                choice = rand() % 2 + 1;
                vector<int> order;
                //generate new child
                if(choice == 1)
                    order = crossoverLCS(parent1, sub);
                else
                    order = crossoverLCS(parent2, sub);
            
                //mutate the child according to rate
                m = rand()%100 +1;
                if(m <= this->mutationRate)
                    mutate(order);

                //add child to population
                newPop.push_back(order);
                
            }

    //crossover technique 2...only one parent 
    }else{
        vector<int> parent;
        if(this->selectionTechnique==1){
            int index = roulette(population, fitness);
            parent = population[index];
            this->currentDistance = this->distances[index];
        }else{
        //technique 2 for finding parents...just choose best fitness score
            int topFitness = 0;
            int topIndex = 0;
        
            for(int i = 0; i < fitness.size(); i++){
                if(fitness[i] > topFitness){
                    topFitness = fitness[i];
                    topIndex = i;
                }
            }
            parent = population[topIndex];
            this->currentDistance = this->distances[topIndex];
        }
        for(int i = 0; i < population.size(); i++){
            //generate new child
            vector<int> order = crossover(parent);

            //mutate the child according to rate
            m = rand()%100 +1;
            if(m <= this->mutationRate){
                mutate(order);
            }

            //add child to population
            newPop.push_back(order);
        }

    }

    for(int i = 0; i < population.size(); i++){ //replace old population
        population[i] = newPop[i];
    }
}

//roulette function
int GA::roulette(vector<vector<int> > population, vector<int> & fitness){
    int index = 0;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int>distribution(0, fitness[fitness.size()-1]); 
    int r = distribution(generator); 
    while(true){
        if(r <= fitness[index++])
            break;
    }
    index--;    

    if(index < 0 || index > fitness.size()-1){
        return rand()%(fitness.size()-1) + 1;
    }
    
    return index;
}

//roulette function but prevents duplicate parents by removing parent1 from the population before selection
int GA::roulette(vector<vector<int> > population, vector<int> fitness, vector<int> & otherParent){
    int index = 0;

    //remove the other parent from the equation
    for(int i = population.size()-1; i > 0; i--){
        if(population[i] == otherParent){
            population.erase(population.begin() + i);
            fitness.erase(fitness.begin() + i);
            break;
        }
    }

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int>distribution(0, fitness[fitness.size()-1]); 
    int r = distribution(generator); 
  
    
    while(true){
        if(r <= fitness[index++])
            break;
    }
    index--;    
    if(index < 0 || index > fitness.size()-1){
        return rand()%(population.size()-1) + 1;
    }
  
    return index;  
}


//crossover technique 2...swapping 2 random elements of parent
vector<int> GA::crossover(vector<int> a){
    shuffle(a);
    return a;
}


//Credit to https://stackoverflow.com/questions/39379411/c-remove-elements-that-are-in-one-vector-from-another
template<typename T>
void remove_intersection(std::vector<T>& a, std::vector<T>& b){
    std::unordered_multiset<T> st;
    st.insert(a.begin(), a.end());
    st.insert(b.begin(), b.end());
    auto predicate = [&st](const T& k){ return st.count(k) > 1; };
    a.erase(std::remove_if(a.begin(), a.end(), predicate), a.end());
}

vector<int> GA::crossoverLCS(vector<int>& a, vector<int> & sub){
    vector<int> child;

    if(sub.size() <= 1){ //no substring
        child = a;
        intenseShuffle(child);
        return child;
    }


    //subtract substring from a
    vector<int> difference = a;
    remove_intersection(difference, sub);
 
    int randStart = rand() % (a.size() - sub.size()) + 1;
   
    if(sub[0] == 1){
         for(int i = 0; i < sub.size(); i++){
             child.push_back(sub[i]);
         }
         randStart = -1;
    }else{
        child.push_back(1);
    }
    if(!difference.empty()){
        if(difference[0] == 1){
            difference.erase(difference.begin());
        }
    }

    for(int i = 0;  i < a.size(); i++){
        if(i==randStart){
            //copy substring into array
            randStart = -1;
            if(!sub.empty()){
                for(int j = 0; j < sub.size(); j++){
                    child.push_back(sub[j]);
                    i++;
                    if(child.size() >= a.size()){
                        return child;
                    }
                }
            }
        }else{
                if(!difference.empty()){
                    int choice = rand() % (difference.size()) + 1;
                    choice -= 1;
                    child.push_back(difference[choice]);
                    difference.erase(difference.begin() + choice);
                }
        }
    }
    return child;
}

vector<int> GA::lcs(vector<int> & a, vector<int> & b){
    vector<int> sub; 
    int** longest = new int* [a.size()+1];
    for(int i = 0; i < a.size() + 1; i++){
        longest[i] = new int[b.size()+1];
        for(int j = 0; j < a.size(); j++){
            longest[i][j] = 0;
        }
    }
    
    int min_index = 0;
    int max_index = 0;

    for(int i = 0; i < a.size(); i++){
        for(int j = 0 ; j < b.size(); j++){
            int temp_max = j;
            int temp_min = j;
            int temp_offset = 0;
            
            if(a[i]==b[j]){
                while(temp_offset <= i && temp_offset <= j 
                    && a[i-temp_offset] == b[j-temp_offset]){
                        temp_min--;
                        temp_offset++;
                    }
            }
            temp_min++;
            int length = temp_max - temp_min + 1;
            int temp_max_length = max(longest[i][j], max(longest[i+1][j], longest[i][j+1])); 
            if(length > temp_max_length){
                min_index = temp_min;
                max_index = temp_max;
                longest[i+1][j+1] = length;
            }else{
                longest[i+1][j+1] = temp_max_length;
            }
        }
    }
    int stop = max_index+1;
    if(max_index >= b.size()-1){
        stop = b.size() -1;
    }
    for(int i = min_index; i < stop; i++){
        sub.push_back(b[i]);
    }
    return sub;
}

//crossover technique 1...copying a random part of parent a into child, then adding rest of parent b
vector<int> GA::crossover(vector<int> & a, vector<int> & b){
    vector<int> c;
    c.push_back(a[0]); //always start at first node
    int start = rand() % (a.size()-2) + 1; //random index between 1 and size of array
    int end = rand() % (a.size()-1-start) + start;  //second random index between end of array and starting point
    //add the random section of a to the new array
    for(int j = start; j < end; j++){
        c.push_back(a[j]);
    }
  
    for(int j = 0; j < b.size(); j++){
        std::vector<int>::iterator it = std::find(c.begin(), c.end(), b[j]);
        if(it == c.end()){
            c.push_back(b[j]);
        }    
    }
    return c;
}