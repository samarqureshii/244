#include <iostream>
using namespace std;

class Int {
  private:
    int* p;

  public:
    Int(int i) {
      p = new int;
      *p = i;
    }
    void set_val(int i) { 
        *p = i; 
    }
    int get_val() { 
        return *p; 
    }

    virtual ~Int(){
        delete p;
    }
    
    virtual void print() = 0;
};

class SuperInt : public Int {
  private:
    int* q;
  public:
    SuperInt(int i) : Int(i) {
      q = new int;
      *q = i;
    }

    ~SuperInt() { 
        delete q; 
    }

    void set_val(int i) {
      Int::set_val(i);
      *q = i;
    }

    void print() { cout << Int::get_val() << " " << *q << endl; }
};

int main() {
  // Don't change anything here!
  Int* s = new SuperInt(3);
  s->set_val(4);
  s->print();
  delete s;
  return 0;
}


void reverseArray(int* array, int left, int right) {
    //base case
    if(left >= right){ //if they cross
        return;
    }   

    //general case
    else{
        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        if(right - left > 1){ //if the left and right indices have not "crossed" yet 
            reverseArray(array, left+1, right-1);
        }
    }
}

class Node {
  public:
    int data;
    Node* next;

  public:
    Node(int d) {
        data = d;
        next = NULL;
    }
};

class List {
  private:
    Node* head;

  public:
    List() ;
    List( const List& ) ;
   ~List() ;
   // Assume constructor, destructor, and copy constructor are correctly implemented

    List* operator+( const List& ) ;
    // other functions . . .
};


List* List::operator+( const List& rhs ) {
    List* addition = new List ;
    Node* pLHS = head ;          //ptr to walk through LHS
    Node* pRHS = rhs.head ;      // ptr to walk through RHS
    Node* n = NULL ;             // ptr to newly allocated nodes
    Node* ptr ;                  // ptr to last node in new list

    while ( pLHS != NULL  ||  pRHS != NULL ) {
        int dataLHS = (pLHS) ? pLHS->data : 0 ;
        int dataRHS = (pRHS) ? pRHS->data : 0 ;

        n = new Node( dataLHS + dataRHS ) ;
        if (addition->head == NULL) {
            addition->head = n ;
            ptr = addition->head ;
        } else {
            ptr->next = n ;
            ptr = n ;
        }
        if( pLHS) pLHS = pLHS->next ;
        if( pRHS )pRHS = pRHS->next ;
    }
    return addition ;
 }
