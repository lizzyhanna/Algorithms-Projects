//Lizzy Hanna, Lab 4, CS 3353, SMU ID 47358250
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>
using namespace std;

class Algorithm{
	public:
		virtual ~Algorithm(){}; //virtual destructor

		//virtual functions
		virtual void stats(){};
		virtual void save(){};
		
		//pure virtual functions (must be overridden)
		virtual void select(int) = 0;	
		virtual void execute() = 0;

};

#endif