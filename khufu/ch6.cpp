#include <iostream>
 using namespace std;
 #include <sstream>
 #include <string>
 #include <fstream>
using namespace std;

class Foo {
 private:
  int priv;

 public:
  Foo(int pv) { priv = pv; }
  Foo(const Foo& src) { priv = src.priv; }
  Foo& operator=(const Foo& rhs) {
    priv = rhs.priv;
    return* this;
  }
  int getPriv() const { return priv; }
  void setPriv(int pv) { priv = pv; }
};

class vector_2d {
 private:
  double x;
  double y;

 public:
  vector_2d() {
    x = 0;
    y = 0;
  }
  vector_2d(double x_, double y_) {
    x = x_;
    y = y_;
  }
  double get_x() const { return x; }
  double get_y() const { return y; }

  vector_2d& operator+=(const vector_2d& rhs){
    x+=rhs.x;
    y+=rhs.y;

    return *this;
  }


};


#include <iostream>
using namespace std;
class Fraction {
 private:
  int numerator;
  int denominator;

 public:
  Fraction(int num, int denm);
  int getNumerator();
  int getDenominator();
  void setNumerator(int num);
  void setDenominator(int denm);
  void print();
};
Fraction::Fraction(int num, int denm) {
  numerator = num;
  // Should check that denm is not 0, but ignore for now
  denominator = denm;
}
int Fraction::getNumerator() {
  return (numerator);
}
int Fraction::getDenominator() {
  return (denominator);
}
void Fraction::setNumerator(int num) {
  numerator = num;
}
void Fraction::setDenominator(int denm) {
  // Should check that denm is not 0, but ignore for now
  denominator = denm;
}

//function should return a new fraction member 
Fraction& Fraction::operator*(Fraction& rhs){
    Fraction w = (numerator*rhs.numerator, denominator*rhs.denominator);
    return w;
}

Fraction& Fraction::operator*(int& num){
    return(numerator*num, denominator);
}























/// SALMA REVIEW LECTURE 
void Fraction::print() {
  cout << numerator << "/" << denominator << endl;
}

Fraction& Fraction::operator*(const Fraction& rhs){ //we want to pass the RHS by reference
    Fraction w(numerator*rhs.numerator, denominator*rhs.denominator);
    return w;

}

ostream& operator<<(ostream& os, Fradtion& x){
    os <<x.numerator << "/" << x.denominator;
    return os;
}
//operator << cannot be a member of fraction because the LHS is not a fraction, it is ostream type 
//friend function needed because ostream is not a member, but friend functions can still access the member functions