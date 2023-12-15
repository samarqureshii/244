#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class ListNode { 
    ListNode* next; 
    int data;

    public:
        ListNode(int data_) {
        data = data_; next = NULL;
    }

    ListNode* get_next() { 
        return next; 
    }

    void set_next(ListNode* next_) { 
        next = next_; 
    } 

    int get_data() { 
        return data; 
    }

};
// Return the head of the merged list.
// Feel free to use the next page. 

ListNode* merge(ListNode* a, ListNode* b) {
    //base cases, we have to assume that the size of the two lists are not identical
    if(a == NULL){
        return b;
    }
    if(b == NULL){
        return a;
    }

    //general case
    else{
        if(a->get_data() > b->get_data()){ 
            b->set_next(merge(a, b->get_next())); //traverse to the next node in b, keep a as is 
            return b; //
        }

        else{ //if b is larger than a, or if they are the same, we don't care 
            a->set_next(merge(a->get_next(), b)); //traverse to the next node in a, keep b as is
            return a;
        }
    }

    //general case 

}