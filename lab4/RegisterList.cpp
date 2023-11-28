#include "RegisterList.h"

#include <iostream>

#include "Register.h"
#include <climits>
#include <cfloat>

using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  while(head != nullptr){
    Register* curr = head;
    head = head->get_next();
    delete curr;
  }
}

Register* RegisterList::get_head() {  
  return head;
}

int RegisterList::get_size() { 
  // return number of registers 
  return size;
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
  if(head == nullptr){
    return nullptr;
  }

  Register* minReg = head;
  int min = head->get_queue_list()->get_items();

  // loop through the rest of the registers
  for(Register* curr = head->get_next(); curr != nullptr; curr = curr->get_next()){
    int items = curr->get_queue_list()->get_items();
    if(items < min){
      min = items;
      minReg = curr;
    }
  }

  return minReg;
}


Register* RegisterList::get_free_register() {
    Register* currReg = head; // Assume head is the start of your linked list of registers
    Register* freeReg = nullptr;

    while (currReg != nullptr) {
      if(currReg->get_queue_list()->get_head() == nullptr){
        return currReg;
      }
      currReg = currReg->get_next();
    }

    return freeReg;
}


void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 

  if(head == nullptr){
    head = newRegister;
  }
  
  else{
    Register* curr = head;
    while(curr->get_next() != nullptr){ //traverse till the end
      curr = curr->get_next();
    }
    curr->set_next(newRegister);
  }

  size ++;
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  for(Register* curr = head; curr!=nullptr; curr = curr->get_next()){
    if(curr->get_ID() == ID){
      return true;
    }
  }

  return false;

}

Register* RegisterList::dequeue(int ID) {
    // dequeue the register with given ID
    Register* curr = head;
    Register* prev = nullptr;
    while(curr!=nullptr && curr->get_ID()!=ID){
        //traverse through, keep track of the previous at all times
        prev = curr;
        curr = curr->get_next();
    }

    if(curr == nullptr){
        return nullptr;
    }

    if(prev == nullptr){
        head = curr->get_next(); //if the one to dequeue is first
    } else {
        prev->set_next(curr->get_next()); 
    }

    size--; 
    curr->set_next(nullptr);
    return curr; //return dequeued
}


// Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
//   Register* minReg = nullptr;
//   double minAvailableTime = DBL_MAX;

//   for (Register* curr = head; curr != nullptr; curr = curr->get_next()) {
//     double availableTime = curr->get_availableTime();
//     if (availableTime <= expTimeElapsed && availableTime < minAvailableTime) {
//       minAvailableTime = availableTime;
//       minReg = curr;
//     }
//   }

//   if (!minReg) {
//     // when all registers are available, find the first one that can take a customer 
//     for (Register* curr = head; curr != nullptr; curr = curr->get_next()) {
//       if (curr->get_availableTime() <= expTimeElapsed) {
//         return curr;
//       }
//     }
//   }
  
//   return minReg;
// }

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
    Register* minReg = nullptr;
    double minDepartureTime = DBL_MAX;
    double departTime;

    for (Register* curr = head; curr != nullptr; curr = curr->get_next()) {
        departTime = curr->calculateDepartTime();

        // if the departure time is in the past, and it's the smallest we've seen
        if (expTimeElapsed >= departTime && departTime != -1 && departTime < minDepartureTime) {
            minDepartureTime = departTime;
            minReg = curr;
        }
    }

    return minReg;
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
