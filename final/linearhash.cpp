#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class HashTable {
private:
    struct Bucket {
        string id;
        bool occupied;
        bool is_active; // True if the bucket is currently occupied, false if it was deleted
        Bucket() : id(""), occupied(false), is_active(false) {}
    };

    Bucket* table;
    int capacity; // Current size of the table
    int count; // Number of elements currently stored in the table

    bool isPrime(int n);
    int getNextPrime(int n);
    void resize();
    int get_hash_index(const std::string& id);

public:
    HashTable(int initial_capacity);
    ~HashTable();
    bool insert(const std::string& id);
    bool search(const std::string& id);
    bool remove(const std::string& id);
};


bool HashTable::insert(const string& id){
    //resize if needed

    //get the index 
    int hash_index = get_hash_index(id) % capacity;
    //iterate through the hash indices to get a hash index nearby
    while(table[hash_index].occupied && table[hash_index].is_active){
        //occupied is for buckets that have been apart of the hash's lifecycle at some point
        //is active is if the bucket is currently populated 
        hash_index = (hash_index+1) % capacity;
    }

    //insert the value
    table[hash_index] = {id,true, true};
    count ++;
    return true;
}

bool HashTable::remove(const string& id){
    int idx = get_hash_index(id) % capacity;
    int startIdx = idx;

    do{
        if(table[idx].occupied && table[idx].id == id && table[idx].is_active){
            table[idx].is_active = false;
            count--;
            //delete table[idx];
            return true;
        }

        idx = (idx+1) % capacity;

    } while(idx != startIdx && table[idx].occupied);
}

bool HashTable::resize(){

}