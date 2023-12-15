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
    //recursive non member function 
    //prints cout to second smallest key value  in a given binary search tree

    //let c be the element counter

    //base case
    if(myroot == NULL){
        return;
    }

    //general case
    secondSmallest(myroot->left, c); //look through the left subtree

    c++; //increment the counter 
    if(c == 2){ //if it is the second element (in-order traversal)
        cout << myroot->key << endl;
        return;
    }

    secondSmallest(myroot->right, c); //look through the right subtree 
    
}

int main(){
    int c = 0;
    secondSmallest(root,c);
}