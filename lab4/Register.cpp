
// Created by Salma Emara on 2023-06-02.
#include "Register.h"

#include <iostream>
using namespace std;

Register::Register(int id, double timePerItem, double overhead,
                   double entryTime) {
  ID = id;
  secPerItem = timePerItem;
  overheadPerCustomer = overhead;
  availableTime = entryTime;
  next = nullptr;           // no other registers yet
  queue = new QueueList();  // no customers in line yet, but has to initialize a
                            // queue
}

Register::~Register() {  //destructor
  delete queue;
}

QueueList* Register::get_queue_list() { 
  return queue;
}

Register* Register::get_next() { 
  return next;
}

int Register::get_ID() {  
  return ID;
}

double Register::get_secPerItem() {  
  return secPerItem;
}

double Register::get_overheadPerCustomer() {  
  return overheadPerCustomer;
}

double Register::get_availableTime() {  
  return availableTime;
}

void Register::set_next(Register* nextRegister) {  
  next = nextRegister;
}


void Register::set_availableTime(double availableSince) {
  availableTime = availableSince;
}

double Register::calculateDepartTime() {
  Customer* curr = queue->get_head();
  if (curr == nullptr || queue == nullptr) {
    //cout << "Queue is empty, cannot calculate departure time." << endl;
    return -1;
  }

  else if(curr->get_arrivalTime() < availableTime){
    return (curr->get_numOfItems() * secPerItem) + overheadPerCustomer + availableTime;
  }

  else {
    return (curr->get_numOfItems() * secPerItem) + overheadPerCustomer+  curr->get_arrivalTime();
  }


  //cout << "Calculated departure time: " << departureTime << " for customer with " << curr->get_numOfItems() << " items." << endl;

}


void Register::departCustomer(QueueList* doneList) {
  availableTime = calculateDepartTime();
  Customer* customerToDepart = queue->dequeue();
  customerToDepart->set_departureTime(availableTime);
  doneList->enqueue(customerToDepart);
}

void Register::print() {
  std::cout << "Register ID: " << ID << std::endl;
  std::cout << "Time per item: " << secPerItem << std::endl;
  std::cout << "Overhead per customer: " << overheadPerCustomer << std::endl;
  if (queue->get_head() != nullptr) {
    std::cout << "Queue has customers: \n";
    queue->print();
  }
}
