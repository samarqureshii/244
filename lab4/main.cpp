#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <climits>
#include <cfloat>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:
double maxWait(QueueList* doneList);
double averageWait(QueueList* doneList);
double standardDeviation(QueueList* doneList, double averageWait);
void systemUpdate(double timeElapsed);
void departReadyCustomers();
bool isReadyToDepart(Customer* customer);
void departCustomer(Register* reg, Customer* customer);
void queueWaitingCustomers();
void queueCustomerToRegister(Register* reg, Customer* customer);
void processSingleQueueMode();

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is up to customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes 

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);

// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList; // holding the list of customers served
QueueList *singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation
bool isSingle;

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;

    //sysUpdate(expTimeElapsed, isSingle); 
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  } 


  //end statistics
  cout << "Finished at time " << expTimeElapsed << " Statistics:" << endl;
  cout << "Maximum wait time: " << maxWait(doneList) << endl;
  cout << "Average wait time: " << averageWait(doneList) << endl;
  cout << "Standard Deviation of wait time: " << standardDeviation(doneList, averageWait(doneList)) << endl;

  // You have to make sure all dynamically allocated memory is freed 
  // before return 0
  delete registerList;
  registerList = nullptr;
  delete doneList;
  doneList = nullptr;

  if(mode == "single"){
    delete singleQueue;
    singleQueue = nullptr;
  }

  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
    isSingle = true;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
    isSingle = false;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
    int items;
    double timeElapsed;
    if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
        cout << "Error: too few arguments." << endl;
        return;
    }
    if (foundMoreArgs(lineStream)) {
        cout << "Error: too many arguments." << endl;
        return;
    }

    systemUpdate(timeElapsed); 

    Customer* newCustomer = new Customer(expTimeElapsed, items);
    cout << "A customer entered" << endl;

    if(!isSingle){ //multiple mode

        Register* min = registerList->get_min_items_register();
        if (min==nullptr) {
            cout << "Error: No registers are open" << endl;
        }

        else {
            min->get_queue_list()->enqueue(newCustomer);
            cout << "Queued a customer with quickest register " << min->get_ID() << endl;
        } 
    }

    else{ //multiple mode 
        Register* free = registerList->get_free_register();
        if (free == nullptr) {
            singleQueue->enqueue(newCustomer);
            cout << "No free registers" << endl;
        }
        else {
            free->get_queue_list()->enqueue(newCustomer);
            //double departureTime = free->calculateDepartTime();
            //newCustomer->set_departureTime(departureTime);
            //free->set_availableTime(departureTime);
            cout << "Queued a customer with free register " << free->get_ID() << endl;
        } 
    } 
}

void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
    int ID;
    double secPerItem, setupTime, timeElapsed;
    if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
        !getDouble(lineStream, setupTime) || !getDouble(lineStream, timeElapsed)) {
        cout << "Error: too few arguments." << endl;
        return;
    }
    if (foundMoreArgs(lineStream)) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    if (registerList->foundRegister(ID)) {
        cout << "Error: register " << ID << " is already open" << endl;
        return;
    }

    systemUpdate(timeElapsed);

    Register* newReg = new Register(ID, secPerItem, setupTime, expTimeElapsed);
    registerList->enqueue(newReg);
    //newReg->set_availableTime(expTimeElapsed + setupTime);
    cout << "Opened register " << ID << endl;

    if (isSingle && singleQueue->get_head() != nullptr) {
        Customer* customer = singleQueue->dequeue();
        newReg->get_queue_list()->enqueue(customer);
        // double departureTime = expTimeElapsed + customer->get_numOfItems() * newReg->get_secPerItem() + newReg->get_overheadPerCustomer();
        // customer->set_departureTime(departureTime);
        // newReg->set_availableTime(departureTime);
        cout << "Queued a customer with free register " << ID << endl;
    }
}


void closeRegister(stringstream &lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message 

  systemUpdate(timeElapsed);
  Register* closedRegister = registerList->dequeue(ID);

  if(closedRegister!=nullptr){
    cout << "Closed register " << ID << endl;
    //cout << "Register ID " << ID << " closed at time: " << expTimeElapsed << endl;
    delete closedRegister;
  }

  else{
    cout << "Error: register " << ID << " is not open" << endl;
  }
  
}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}

double maxWait(QueueList* doneList){
  Customer* curr = doneList->get_head();
  double maxTime = 0;
  double time;

  while(curr!=nullptr){
    time = curr->get_departureTime() - curr->get_arrivalTime();
    if(maxTime < time){
      maxTime = time;
    }
    curr = curr->get_next();
  }

  return maxTime;
}


double averageWait(QueueList* doneList) {
    Customer* curr = doneList->get_head();
    double totalWait = 0;
    int counter = 0;
    
    while(curr != nullptr) {
        totalWait += curr->get_departureTime() - curr->get_arrivalTime();
        counter++;
        curr = curr->get_next();
    }
    
    if(counter == 0) {
        return 0;
    } else {
        return totalWait / counter;
    }
}

double standardDeviation(QueueList* doneList, double averageWait) {
    Customer* curr = doneList->get_head();
    double squareSum = 0;
    int counter = 0;
    
    while(curr != nullptr) {
        double waitTime = curr->get_departureTime() - curr->get_arrivalTime();
        squareSum += pow((waitTime - averageWait), 2);
        counter++;
        curr = curr->get_next();
    }
    
    if(counter == 0) {
        return 0;
    } else {
        return sqrt(squareSum / counter);
    }
}

void systemUpdate(double timeElapsed) {
    expTimeElapsed += timeElapsed; //increment global time

    if(registerList->get_head() == nullptr) {
        return;
    }

    //depart the registers in order 
    Register* currentReg;
    double departureTime;
    
    for (currentReg = registerList->calculateMinDepartTimeRegister(expTimeElapsed); 
         currentReg != nullptr; 
         currentReg = registerList->calculateMinDepartTimeRegister(expTimeElapsed)) {

        departureTime = currentReg->calculateDepartTime();

        // common to both modes 
        if (departureTime > 0 && departureTime <= expTimeElapsed) {
            cout << "Departed a customer at register ID " << currentReg->get_ID()
                 << " at " << departureTime << endl;
            currentReg->departCustomer(doneList);
        }

        // single mode only
        if (isSingle) {
            processSingleQueueMode();
        }
    }
}


// void systemUpdate(double timeElapsed) {
//     expTimeElapsed += timeElapsed;

//     // depart customers ready to leave
//     departReadyCustomers();

//     // in single queue mode, queue waiting customers to free registers
//     if (isSingle) {
//         queueWaitingCustomers();
//     }
// }

void processSingleQueueMode() {
    Register* freeRegister = registerList->get_free_register();
    if (freeRegister) {
        Customer* nextCustomer = singleQueue->get_head();
        if (nextCustomer) {
            nextCustomer = singleQueue->dequeue();
            freeRegister->get_queue_list()->enqueue(nextCustomer);
            cout << "Queued a customer with free register " << freeRegister->get_ID() << endl;
        }
    }
}


void departReadyCustomers() {
    Register* currentReg = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
    while (currentReg) {
        Customer* customerToDepart = currentReg->get_queue_list()->get_head();
        if (isReadyToDepart(customerToDepart)) {
            departCustomer(currentReg, customerToDepart);
        }
        currentReg = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
    }
}

bool isReadyToDepart(Customer* customer) {
    return customer && customer->get_departureTime() > 0
           && customer->get_departureTime() <= expTimeElapsed;
}

void departCustomer(Register* reg, Customer* customer) {
    cout << "Departed a customer at register ID " << reg->get_ID()
         << " at " << customer->get_departureTime() << endl;
    reg->departCustomer(doneList);
}

void queueWaitingCustomers() {
    Register* freeReg = registerList->get_free_register();
    while (freeReg && singleQueue->get_head()) {
        Customer* nextCustomer = singleQueue->dequeue();
        queueCustomerToRegister(freeReg, nextCustomer);
        freeReg = registerList->get_free_register();
    }
}

void queueCustomerToRegister(Register* reg, Customer* customer) {
    double nextAvailableTime = expTimeElapsed + (customer->get_numOfItems() * reg->get_secPerItem()) 
                               + reg->get_overheadPerCustomer();
    customer->set_departureTime(nextAvailableTime);
    reg->get_queue_list()->enqueue(customer);
    cout << "Queued a customer with newly freed register " << reg->get_ID() << endl;
}




// void systemUpdate(double timeElapsed) {
//     expTimeElapsed += timeElapsed;

//     // Process departure for all registers
//     bool customersToDepart;
//     do {
//         customersToDepart = false;
//         double earliestDepartureTime = DBL_MAX;
//         Register* regToDepartCustomer = nullptr;

//         // Find the register with the next customer to depart
//         for (Register* currReg = registerList->get_head(); currReg != nullptr; currReg = currReg->get_next()) {
//             Customer* headCustomer = currReg->get_queue_list()->get_head();
//             if (headCustomer != nullptr && headCustomer->get_departureTime() <= expTimeElapsed &&
//                 headCustomer->get_departureTime() < earliestDepartureTime) {
//                 earliestDepartureTime = headCustomer->get_departureTime();
//                 regToDepartCustomer = currReg;
//                 customersToDepart = true;
//             }
//         }

//         // Depart the customer with the earliest departure time
//         if (regToDepartCustomer != nullptr) {
//             cout << "Departed customer at register ID " << regToDepartCustomer->get_ID() 
//                  << " at " << earliestDepartureTime << endl;
//             regToDepartCustomer->departCustomer(doneList);

//             // If in single mode, immediately try to queue a customer to the freed register
//             if (isSingle && singleQueue->get_head() != nullptr) {
//                 Customer* nextCustomer = singleQueue->dequeue();
//                 regToDepartCustomer->get_queue_list()->enqueue(nextCustomer);
//                 double nextAvailableTime = expTimeElapsed + (nextCustomer->get_numOfItems() * regToDepartCustomer->get_secPerItem()) +
//                                            regToDepartCustomer->get_overheadPerCustomer();
//                 nextCustomer->set_departureTime(nextAvailableTime);
//                 regToDepartCustomer->set_availableTime(nextAvailableTime);
//                 cout << "Queued a customer with newly freed register " << regToDepartCustomer->get_ID() << endl;
//             }
//         }
//     } while (customersToDepart); // Repeat if there are more customers ready to depart at this time

//     // In multiple queue mode, each register handles its own queue without any additional logic needed here
// }







