//Lizzy Hanna, CS 3353, SMU ID 47358250
#include "SortAlgo.h"
#include <vector>
#include <chrono>

using namespace std;


    //BUBBLE:
    void swap(int * x,int * y){ //part of bubble sort
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    double SortAlgo::bubble(vector<int>* unsorted, int numElements){
        //start timing
         chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

         //start the sort
        int temp;
        for(int i = 0; i < numElements-1; i++){
            for(int j = 0; j < numElements-i-1; j++){
                if(unsorted->at(j) > unsorted->at(j+1)){
                        //swap
                        swap(unsorted->at(j), unsorted->at(j+1));
                }
            }
        }
        //end timing
         chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
         return chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    }//end bubble




    //INSERTION:
    double SortAlgo::insertion(vector<int>* unsorted, int numElements){
        //start timing
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
         
        //begin the insertion sort
        int val, ip = 0;
       
        for (int i = 0; i < unsorted->size(); i++){
            val = unsorted->at(i);         
            ip = i - 1;
            while(ip >= 0 && (unsorted->at(ip) > val)){ //while j isn't at beginning, and value of j > val
                unsorted->at(ip+1) = unsorted->at(ip); 
                ip -= 1; //decrement ip
            }
            unsorted->at(ip+1) = val;
        }

        //end timing
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    }//end insertion





    //MERGE:
    void mergeAll(vector<int>* unsorted, int start, int mid, int end){
        int p = start;
        int q = mid+1;
        vector<int> sorted;

        for(int i = start ;i <= end ;i++) {
            if(p > mid)         //have we reached end of first half?
                sorted.push_back(unsorted->at(q++));
            else if (q > end)   //have we reached end of second half?
                sorted.push_back(unsorted->at(p++));
            else if(unsorted->at(p) < unsorted->at(q)) //compare for smaller element
                sorted.push_back(unsorted->at(p++));
            else
                sorted.push_back(unsorted->at(q++));
        }
    }

    void merge_sort(vector<int>*unsorted, int start, int end){
        if(start < end){
            int mid = (start + end)/ 2; //find mid point

            //recursive calls
            merge_sort(unsorted, start, mid); //mid becomes new end
            merge_sort(unsorted, mid+1, end); //mid+1 becomes new start
            mergeAll(unsorted, start, mid, end);
        }
        
    }

    double SortAlgo::merge(vector<int>* unsorted, int numElements){
        //begin timing
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

        //begin the merge sort (recursive function)
        merge_sort(unsorted, 0, numElements-1);

        //end timing
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    }//end merge


    

