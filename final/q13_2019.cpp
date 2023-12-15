using namespace std;
#include <iostream>
#include <sstream>
#include <string>

class TreeNode {
    public:
        int key;
        TreeNode* left;
        TreeNode* right;

};

TreeNode* root;

void secondSmallest(TreeNode* myroot, int& c){ //pointer to the root of the tree and integer that can be used to store stuff 
    c = myroot->key; //start off with c as the parent node key
    //recursive non member function 
    //prints cout to second smallest key value  in a given binary search tree

    //let c be the second smallest 

    //base case
    if(left == NULL || right == NULL){
        cout << c << endl;
        return;
    }

    //general case

    //traverse through the left side of the tree, get the smallest value there
    if(myroot->key < c){
        //if right is bigger than the left, go right
        c = myroot->key;
    }

    //traverse through both sides of the tree
    secondSmallest(myroot->left, c);
    secondSmallest(myroot->right, c);
    
}

int main(){
    int c = 0;
    secondSmallest(root,c);
}