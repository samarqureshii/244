#include "QueueList.h"

#include "Customer.h"
#include <iostream>
#include <sstream>
using namespace std;


QueueList::QueueList() { 
  head = nullptr;
}

QueueList::QueueList(Customer* customer) { 
  head = customer; 
}

QueueList::~QueueList() { //destructor
//safely deallocate any dynamic memory to prevent memory leaks
//iterate through all the Customer nodes and delete them
  while(head!=nullptr){
    Customer* curr = head;
    head = head -> get_next();
    delete curr;
  }
  
}

Customer* QueueList::get_head() {  
  return head;
}

void QueueList::enqueue(Customer* customer) {
  //cout << "Attempting to enqueue customer with items: " << customer->get_numOfItems() << endl;

  if (head == nullptr) {
    head = customer;
    //cout << "Queue was empty, customer is now the head of the queue." << endl;
  } else {
    Customer* curr = head;
    while (curr->get_next() != nullptr) {
      curr = curr->get_next();
    }
    curr->set_next(customer);
    //cout << "Customer enqueued behind existing customers." << endl;
  }
}


Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  // and return a pointer to it
  
  //when the list is empty return nullptr
  //when there's at least one customer adjust head to the next customer in the list 
  if(head == nullptr){
    return nullptr;
  }

  else{
    Customer* curr = head;
    head = head ->get_next();
    curr->set_next(nullptr);
    return curr;
  }
  
}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  //iterate through each customer in the list, summing up the number of items each customer has, return total count at the end
  int total = 0;
  Customer* curr = head;

  while(curr!=nullptr){
    total += curr->get_numOfItems();
    curr = curr->get_next();
  }

  return total;
}

bool QueueList::empty_queue() {
  // if the queue is empty, return false
  if(head == nullptr){
    return false;
  }

  else{ 
    // if the queue is not empty, delete all customers
    // and return true
    while(head!=nullptr){
      Customer* curr = head;
      head = head->get_next();
      delete curr;
    }
    return true;
  }
  
}

void QueueList::print() {
  // print customers in a queue
  Customer* curr = head;

  while (curr != nullptr) {
    curr->print();
    curr = curr->get_next();
  }
}
