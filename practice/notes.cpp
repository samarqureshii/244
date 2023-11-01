// #include <iostream>
// #include <string>
// using namespace std;
// class Node{
//     private:
//         int data;
//         Node* next;
//     public:
//         Node(){data = 0; next = NULL;}
//         Node(int d){data =d; next = NULL;}
//         Node(int d, Node* n){data = d; next=n;}
//         ~Node(){delete next;}
//         int getData(){return data;}
//         Node* getNext(){return next;}
//         void setData(int d){data = d;}
//         void setNext(Node* n){next = n;}
// };

// class Stack{
//     private:
//         Node* head;
//     public:
//         Stack(){head = NULL;}
//         ~Stack(){delete head;}
//         void push(int d){
//             Node* p = new Node(d, head);
//             head = p;
//         }

//     int pop(){
//         if(head == NULL)
//             return -1;
//         Node* p = head;
//         int d = p -> getData();
//         head p -> getNext();
//         p -> setNext(NULL);
//         delete p;
//         return d;
//     }
// };

// class Queue{
//     private:
//         Node* head;
//         Node* tail;
//     public:
//         Queue(){
//             head = NULL;
//             tail = NULL;
//         }

//         ~Queue(){
//             delete head;
//         }

//         void enqueue(int d){
//             Node* p = new Node(d, NULL);
//             tail -> setNext(p);
//             tail = p;
//             if(head == NULL) head = p;
//         }

//         int dequeue(){
//             if(head == NULL) return -1;
//             Node* p = head;
//             head = p -> getNext();
//             int d = p -> getData();
//             p -> setNext(NULL);
//             delete p;
//             return d;
//         }
// };

// ///////
// Queue q;
// q.enqueue(1);
// q.enqueue(2);
// q.enqueue(3);

// cout << q.dequeue() << q.dequeue() << endl;
// //output 1 2 3




// #include "Node.h"

// class List{
//     private:
//         Node* head;
//     public:
//         List() {head = NULL;}
//         ~List(){double head;}
//         void insertData(int d);
//         bool dataExists(int d);
//         bool deleteData(int d);
//         List(const List&); //copy consutrctor
//         List& operator=(const List&);
// };

// bool dataExists(int d){
//     Node* p = head;
//     while(p != NULL && p-> getData() < d){
//         if(p->getData == d){
//             return true;
//         }
//         else{
//             p = p -> getNext();
//         }
//     }

//     return false;
// }

// bool List::insertData(int d){
//     Node* n = new Node(d);
//     Node* p = head, *prev = NULL;

//     if(p == NULL){
//         head = n ;
//     }

//     while(p != NULL && p -> getData() < d){
//         prev = p;
//         p = p -> getNext();
//     }

//     n->setNext(p);

//     if(prev == NULL){
//         head = n;
//     }

//     else{
//         prev -> setNext(n);
//     }
// }

// bool List:: deleteData(int d){
//     Node* p = head, *prev = NULL;

//     while(p!=NULL && p-> getData()!=d){
//         if(p->getData() > d){
//             return false;
//         }

//         prev = p;
//         p = p->getNext();
//     }

//     if(p == NULL){
//         return false;
//     }

//     if(prev == NULL){ //delete at front
//         head = p-> getNext();
//     }

//     else{
//         prev ->setNext(p->getNext()); //delete at middle or tail 
//     }

//     p->setNext(NULL);
//     delete p;
// }


// //copy constructor 
// List::List(const List& original){
//     Node* p = original.head;
//     Node* np = NULL;

//     head = NULL;

//     while(p!=NULL){
//         Node*n = new Node(p->getData(), NULL);
        
//         if(np == NULL){
//             head = n;
//         }

//         else{
//             np ->setNext(n);
//         }

//         p = p ->getNext();
//         np = n;
//     }
// }

// List& List::operator=(const List& original){
//     if(&original == this){
//         return *this;
//     }

//     if(head!=NULL){
//         delete head;
//         head = NULL;
//     }

//     Node* p = original.head;
//     Node* np = NULL;

//     head = NULL;

//     while(p!=NULL){
//         Node*n = new Node(p->getData(), NULL);
        
//         if(np == NULL){
//             head = n;
//         }

//         else{
//             np ->setNext(n);
//         }

//         p = p ->getNext();
//         np = n;
//     }

//     return *this;
// }



