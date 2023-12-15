using namespace std;
#include <iostream>
#include <sstream>
#include <string>

class ListNode { 
    public:
        ListNode(const string& name_) { 
        name = name_;
        next = NULL;
    };

    string name;
    ListNode* next; 
};

class LinkedList { 
    private:
        ListNode* head; 
    public:
        // Default constructor: initialize the head to NULL. 
        LinkedList();

    //Return true if and only if the list is empty, bool is_empty();
    // Insert the given node to the head of the list. // Time complexity: 0(1)
    void insert(ListNode* node);

    // Traversing from the head. Remove the first node found with the given // name from the list. The removed node is NOT deallocated.
    // Returns this node (or NULL if the name is not found).
    // Time complexity: 0(n)
    ListNode* remove(const string name);

    // Return true if there exists at least one node with the given name. // Time complexity: 0(n)
    bool find(const string& name);

    // Remove the current head node from the linked list, // and return it.
    // Move the head one node forward.
    // Time complexity: 0(1)
    ListNode* pop_head();
    // Destructor: Properly deallocate all the nodes.
    ~LinkedList();

};

//two strings may return the same number, in that case, we must allocate multiple VTubers to the same hash index by increasing the 
//Linked List size at that location
int string_hash(const string& name); //turns the given string into a non-negative integer value 

#define INIT_CAPACITY 32

class HashTable { 
    private:
        // Array of Linked List: resolving collisions by chaining
        LinkedList** table;
        // The length of the table array,
        int table_slot_size;
        int num_elements;
        // Keep track of how many elements (names) are in the hash table int num_elements;
        int get_hash_index(const string& name) {
            return string_hash(name) % table_slot_size;
        }
    public:
        // Constructors and destructors.
        HashTable();
        ~HashTable();
        // Hash table method,
        bool exist(const string& name);
        bool insert(const string& name);
        bool remove(const string& name);
        bool change_name(const string& old_name, const string& new_name);

};
//class implementation (HashTable.cpp)
HashTable::HashTable() {
    table = new LinkedList*[INIT_CAPACITY]; 
    table_slot_size= INIT_CAPACITY; 
    int num_elements = 0;

    for (int i = 0; i < table_slot_size; ++i) { 
        //initially each hash index has 32 NULL spots 
        table[i] = NULL;
    } 

}

bool HashTable::exist(const string& name) { 
    int idx = this->get_hash_index(name);
    if (table[idx] == NULL) {
        return false;
    }
    return table[idx]->find(name);
}

bool HashTable::insert(const string& name){ 
    //maintain the unique name property
    //if the name already exists in the hash table, return false
    if(this->exist(name)){ //we use this because we are referring to this HashTable
        return false;
    }

    

    num_elements+=1; //this is the total number of elements in the hash table
    //check the load factor and resize if necessary 
    if(num_elements > table_slot_size/2){ //table slot size is the number of unique hash elements. 
    //we dont want too many collisions or it'll degrade performance, which is why we cant just infinitely add on nodes at a single index 
    //when you try to insert a new name but the value of num_elements will become larger than table_slot_size/2, 
    //double table_slot_size and allocate table with the new updated size 
        table_slot_size*=2;
        //initialize everything to nullptr
        LinkedList** new_list = new LinkedList*[table_slot_size]; //generate an array of LinkedList pointers 
        for(int i = 0; i<table_slot_size && new_list; i++){
            new_list[i] = nullptr;
        }

        //then, move all existing items from the old table into the new table
        for(int i = 0; i<table_slot_size/2; i++){ //we only have to iterate table_slot_size/2 times bc its the size of the old list 
            if(table[i]!=NULL){ //if the current pointer at the current hash index is not null (i.e., there is a node there)
            //if it is not empty, then we have something to hash there
                ListNode* curr = table[i]->pop_head(); //to get the head of the list
                while(curr!=NULL){ //now traverse through the linked list 
                    int hash_index = get_hash_index(name);
                    if(new_list[hash_index]==NULL){ //if there is no linkedlist at the current hash, then create one 
                        new_list[hash_index] = new LinkedList; //to address collision, it should dynamically grow at run time
                    }

                    //insert the node into the new list 
                    new_list[i]->insert(curr); //insert the current node from the old list 
                    curr = table[i]->pop_head();
                }
                delete table[i]; //delete the current 
            }   
        }

        delete [] table; //free memory of the smaller list 
        table = new_list;

    }

    //now let's actually add the node
    int hash_index = get_hash_index(name);

    if(table[hash_index]==NULL){
        table[hash_index] = new LinkedList;
    }

    ListNode* newNode = new ListNode(name); //finally make the new node
    table[hash_index]->insert(newNode);
    return true;

}

bool HashTable::remove(const string& name) {
    if(this->exist(name)){ //check if the name is acc valid first
        int hash_index = this->get_hash_index(name); //index of where the node to remove is living
        //now find the node within the linkedlist
        ListNode* nodeToRemove = table[hash_index]->remove(name);
        delete  nodeToRemove;
        num_elements--;
        return true;
    }

    return false; //we cant remov it cuz it doesnt exist
}  

bool HashTable::change_name(const string& old_name, const string& new_name) {
    //remove old name and insert new name
    //return true if successful
    //return false when the old name doesnt exist, or if the new name is the existing name 
    if(this->exist(old_name) || old_name == new_name){
        return false;
    }

    else{
        remove(old_name);
        insert(new_name);
    }
}
