#include <iostream>
#include <sstream>
#include <string>

using namespace std;


class TreeNode {
    public:
        int data; 
        TreeNode* left; 
        TreeNode* right;
};

bool isSymmetricHelper(TreeNode* left, TreeNode* right);

bool is_symmetric(TreeNode* root) { 
    if (root == NULL) {
        return true;
    }

    return isSymmetricHelper(root->left, root->right);
}


bool isSymmetricHelper(TreeNode* left, TreeNode* right) {
    //base case
    if(left == NULL && right == NULL){
        return true;
    }

    else if(left == NULL || right == NULL){ //tree is not symmetrical
        return false;
    }

    else if(left->data != right->data){ //data doesn't match
        return false;
    }

    //general case, traverse through the nodes
    bool flag = isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->left, right->right);
    return flag;
}

if(left->data == right->data){
    isSymmetricHelper(left, right);
    isSymmetricHelper(left, right);
}