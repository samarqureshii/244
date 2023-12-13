#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void prefixsum(int* arr, int left, int right, int psum){
    int n = right;
    if(left > right){ //base case
        //print the array:
        for(int i = 0; i<=n; i++){
            //printing here
        }
        return; //end
    }

    else{
        psum += arr[left];
        arr[left] = psum;
        prefixsum(arr, left+1, right, psum);
    }
    
}