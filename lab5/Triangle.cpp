//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Constructor
Triangle::Triangle(string n, float x1, float y1, float x2, float y2, float x3, float y3) 
    : Shape(n, (x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {
}

// Destructor
Triangle::~Triangle() {
    // Nothing to do
}

// Accessors
float Triangle::getX1() const { return x1; }
float Triangle::getY1() const { return y1; }
float Triangle::getX2() const { return x2; }
float Triangle::getY2() const { return y2; }
float Triangle::getX3() const { return x3; }
float Triangle::getY3() const { return y3; }

// Mutators
void Triangle::setX1(float x) { x1 = x; }
void Triangle::setY1(float y) { y1 = y; }
void Triangle::setX2(float x) { x2 = x; }
void Triangle::setY2(float y) { y2 = y; }
void Triangle::setX3(float x) { x3 = x; }
void Triangle::setY3(float y) { y3 = y; }

// Draw the shape
void Triangle::draw() const {
    cout << fixed;
    cout << setprecision(2);

    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre << " "
         << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " "
         << computeArea()
         << endl;
}

// Compute the area of the triangle
float Triangle::computeArea() const {
    float a = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    float b = sqrt((x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3));
    float c = sqrt((x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1));
    float s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c)); 
}

// Clone the shape
Shape* Triangle::clone() const {
    return (new Triangle(*this));
}