#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void reverseArray(int* array, int left, int right) {
    if(right == left){ //base case
        return;
    }

    else{ //general case 
        //need a temp value when we swap them
        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        reverseArray(array, left+1, right-1);
    }
}