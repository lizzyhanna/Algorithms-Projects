//Lizzy Hanna, CS 3353, SMU ID 47358250 Lab 3
#pragma once
#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>

using namespace std;
class fileLoader{
private: 
    string fileName;
    static void(*nodeAdder)(int,float,float,float);
public:
    fileLoader();
    void readCSV(string);
};

#endif