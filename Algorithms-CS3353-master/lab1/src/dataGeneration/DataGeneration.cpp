//Lizzy Hanna, CS 3353, SMU ID 47358250
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;

void DataGeneration(){
   srand(time(NULL));

   // RANDOM ORDER FILES
    ofstream fileAA;
    fileAA.open("random10.txt");
    for(int i = 10; i > 0; i--){
        fileAA << (rand()%1000) << endl;
    }
    fileAA.close();

    ofstream fileBB;
    fileBB.open("random1000.txt");
    for(int i = 1000; i > 0; i--){
        fileBB << (rand()%1000) << endl;
    }
    fileBB.close();

    ofstream fileCC;
    fileCC.open("random10000.txt");
    for(int i = 10000; i > 0; i--){
        fileCC << (rand()%1000) << endl;
    }
    fileCC.close();

    ofstream fileDD;
    fileDD.open("random100000.txt");
    for(int i = 100000; i > 0; i--){
        fileDD << (rand()%1000) << endl;
    }
    fileDD.close();





//====================================================
    //REVERSE SORTED ORDER FILES
    ofstream fileA;
    fileA.open("rso10.txt");
    for(int i = 10; i > 0; i--){
        fileA << i << endl;
    }
    fileA.close();

    ofstream fileB;
    fileB.open("rso1000.txt");
    for(int i = 1000; i > 0; i--){
        fileB << i << endl;
    }
    fileB.close();

    ofstream fileC;
    fileC.open("rso10000.txt");
    for(int i = 10000; i > 0; i--){
        fileC << i << endl;
    }
    fileC.close();

    ofstream fileD;
    fileD.open("rso100000.txt");
    for(int i = 100000; i > 0; i--){
        fileD << i << endl;
    }
    fileD.close();






//====================================================
   // 20% UNIQUE VALUES
  //  collect an array full of the 20% values and then randomize indices to put in

    ofstream fileE;
    fileE.open("unique10.txt");
    int list[2];
    int num;
    //stores the random values in array
    for(int i = 0; i < 2; i++){
            num = rand()%1000;
            fileE << num << endl;
            list[i] = num;
    }
    //chooses randomly from the values for rest of file
     for(int i = 0; i < 8; i++){
         fileE << list[rand()%2] << endl;
     } 
    fileE.close();
  


    ofstream fileF;
    fileF.open("unique1000.txt");
    int list1[200];
    //stores the random values in array
    for(int i = 0; i < 200; i++){
            num = rand()%1000;
            fileF << num << endl;
            list1[i] = num;
    }
    //chooses randomly from the values for rest of file
     for(int i = 0; i < 800; i++){
         fileF << list1[rand()%199] << endl;
     } 
    fileF.close();

 
    ofstream fileG;
    fileG.open("unique10000.txt");
    int list2[2000];
    //stores the random values in array
    for(int i = 0; i < 2000; i++){
            num = rand()%1000;
            fileG << num << endl;
            list2[i] = num;
    }
    //chooses randomly from the values for rest of file
     for(int i = 0; i < 8000; i++){
         fileG << list2[rand()%1999] << endl;
     }   
    fileG.close();
  
    ofstream fileH;
    fileH.open("unique100000.txt");
    int list3[20000];
    //stores the random values in array
    for(int i = 0; i < 20000; i++){
            num = rand()%1000;
            fileH << num << endl;
            list3[i] = num;
    }
    //chooses randomly from the values for rest of file
     for(int i = 0; i < 80000; i++){
         fileH << list3[rand()%19999] << endl;
     } 
    fileH.close();
   




//====================================================
   // 30% RANDOMIZED 
    int thirds = 1;
    ofstream fileI;
    fileI.open("30random10.txt");
    for(int i = 0; i < 10; i++){
        if(thirds == 3){
            thirds = 1;
            fileI << (rand()%1000) <<endl; //random value
            continue;
        }else
            fileI << i << endl;
        thirds++;
        
    }
    fileI.close();
    thirds =1;
    ofstream fileJ;
    fileJ.open("30random1000.txt");
    for(int i = 0; i < 1000; i++){
          if(thirds == 3){
            thirds = 1;
            fileJ << (rand()%1000) <<endl; //random value
            continue;
        }else
            fileJ << i << endl;
        thirds++;
    }
    fileJ.close();

    thirds = 1;
    ofstream fileK;
    fileK.open("30random10000.txt");
    for(int i = 0; i < 10000; i++){
          if(thirds == 3){
            thirds = 1;
            fileK << (rand()%1000) <<endl; //random value
            continue;
        }else
            fileK << i << endl;
        thirds++;
    }
    fileK.close();

    thirds = 1;
    ofstream fileL;
    fileL.open("30random100000.txt");
    for(int i = 0; i < 100000; i++){
          if(thirds == 3){
            thirds = 1;
            fileL << (rand()%1000) <<endl; //random value
            continue;
        }else
            fileL << i << endl;
        thirds++;
    }
    fileL.close();
}

