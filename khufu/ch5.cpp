#include <iostream>
 using namespace std;
 #include <sstream>
 #include <string>
 #include <fstream>
using namespace std;

//class definitions 
class Follower {
 private:
  string name;
  int age;

 public:
  Follower(const string& _name, int _age) {
    name = name_;
    age = age_;
  }
  string get_name() const { return name; }
  int get_age() const { return age; }
};

class Vtuber {
 private:
  // Vtuber Name
  string name;
  // Follower array with a variable size, each element should be a dynamically
  // allocated object of class Follower.
  Follower** followers;
  // The size of follower array.
  int follower_max;
  // Number of followers
  int follower_num;

 public:
  Vtuber(const string& _name); //constructor
  ~Vtuber(); //destructor
  void insert_follower(const string& follower_name, int follower_age);
  void remove_follower(const string& follower_name);
};

Vtuber::Vtuber (const string& _name) {
  name = _name;
  follower_max = 2;
  follower_num = 0;
  followers = new Follower* [follower_max];

  for(int i = 0; i<follower_max; i++){
    followers[i] = NULL;
  }
}

void Vtuber::insert_follower(const string& follower_name, int follower_age) {
  follower_num++; //we are adding one new;
  
  //search for the first empty location 
  for(int i = 0; i < follower_max; i++){
    if(followers[i] != NULL){
      //insert follower here
      followers[i] = new Follower (follower_name, follower_age);
      return;
    }
  }

  //if the array is full, double follower max, allocate a new follower array, move all data into this array, and insert the new follower 
  Follower** followers_2 = new Follower* [follower_max*2];

  follower_max*=2;
  follower_num = follower_max*2;

  for(int i = 0; i < follower_max; i++){
      //copy the contents from the old follower array
    followers_2[i] = followers[i];
  }
  delete[] followers; //free up the old array
  followers_2[follower_max] = new Follower (follower_name, follower_age);

  //make the unused indices NULL
  for(int i = (follower_max+1); i < follower_num; i++){
    followers_2[i] = NULL;
  }

  followers = followers_2;

}

void Vtuber::remove_follower(const string& follower_name) {
  for(int i = 0; i<follower_num; i++){
    if(followers[i] == NULL){
      continue;
    }
    if(followers[i]->get_name() == follower_name){
      delete followers[i];
      followers[i] = NULL;
      follower_num--;
      return;
    }
  }

  cout << "Follower name not found!";

}

Vtuber::~Vtuber() {
  //delete every index in the array, and then delete the array itself 
  for(int i = 0; i< follower_max; i++){
    if(followers[i] != nullptr){
      delete followers[i];
      followers[i] = NULL;
    }
  }

  delete[] followers;
}

