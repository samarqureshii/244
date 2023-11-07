//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

void createShape(Shape** shapesArray, const string& name, const string& type, int loc_x, int loc_y, int size_x, int size_y);
Shape* findShape(Shape** shapesArray, const string& name);
void moveShape(Shape** shapesArray, const string& name, int loc_x, int loc_y);
void rotateShape(Shape** shapesArray, const string& name, int angle);
void drawShape(Shape** shapesArray, const string& name);
void drawShapes(Shape** shapesArray);
void deleteShape(Shape** shapesArray, const string& name);
void deleteShapes(Shape** shapesArray);

bool isValidCommand(const string& command);
bool isValidIntArg(const string& arg, int& val);
bool isValidStringArg(const string& arg, string& val);
bool isReservedName(const string& n);
bool shapeNameExists(Shape** shapesArray, const string& n);
bool shapeNotFound(Shape** shapesArray, const string& n);
bool isValidShapeType(const string& type);
bool areValidValues(int loc_x, int loc_y, int size_x, int size_y, int angle, string type);
bool isArrayFull(Shape** shapesArray);
int finalErrorCheck(stringstream& ss);

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        /****************************************************************************************/

        if(isValidCommand(command)){ //passed this check
            if(command == "maxShapes"){
                string arg;
                int val;
                
                lineStream >> arg;
                if(lineStream.fail()){ 
                    cout << "Error: too few arguments" << endl;
                    lineStream.clear(); 
                }

                else if(!isValidIntArg(arg, val)){ // check if argument is valid
                    cout << "Error: invalid argument" << endl;
                }

                else{
                    // too many arg check
                    if(finalErrorCheck(lineStream) == 0){
                        delete[] shapesArray; // if there was a previously allocated array
                        shapesArray = new Shape*[val]; 
                        cout << "New database: max shapes is " << val << endl; 
                        max_shapes = val; 
                        shapeCount = 0; 
                    }
                    else{ // finalErrorCheck is not 0
                        cout << "Error: too many arguments" << endl;
                    }
                }
            }
            
            else if (command == "create") {
                string name, type;
                string loc_x_str, loc_y_str, size_x_str, size_y_str;

                int loc_x, loc_y, size_x, size_y;
                bool flag = false;

                //check for name
                lineStream >> name;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                    } 
                    
                    else {
                        cout << "Error: invalid argument" << endl;
                    }
                    flag = true;
                } 
                
                else if (isReservedName(name)) {
                    cout << "Error: invalid shape name" << endl;
                    flag = true;
                }

                else if(shapeNameExists(shapesArray, name)){
                    cout << "Error: shape " << name << " exists" << endl;
                    flag = true;
                }

                //check for type
                if(!flag){
                    lineStream >> type;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidShapeType(type)) {
                        cout << "Error: invalid shape type" << endl;
                        flag = true;
                    }
                }

                //check for x location
                if(!flag){
                    lineStream >> loc_x_str;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidIntArg(loc_x_str, loc_x)) {
                        cout << "Error: invalid argument" << endl;
                        flag = true;
                    }
                }

                //check for y location
                if(!flag){
                    lineStream >> loc_y_str;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidIntArg(loc_y_str, loc_y)) {
                        cout << "Error: invalid argument" << endl;
                        flag = true;
                    }
                }

                //check for x size
                if(!flag){
                    lineStream >> size_x_str;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidIntArg(size_x_str, size_x)) {
                        cout << "Error: invalid argument" << endl;
                        flag = true;
                    } 
                }

                //check for y size
                if(!flag){
                    lineStream >> size_y_str;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidIntArg(size_y_str, size_y)) {
                        cout << "Error: invalid argument" << endl;
                        flag = true;
                    } 
                }

                //now do the rest of the checks

                if(!flag){
                    if (finalErrorCheck(lineStream) != 0) { //throwing -1
                    cout << "Error: too many arguments" << endl;
                    }

                    else if (!areValidValues(loc_x, loc_y, size_x, size_y, 0, type)) { //angle doesnt matter
                        cout << "Error: invalid value" << endl;
                    }

                    else if (isArrayFull(shapesArray)) {
                        cout << "Error: shape array is full" << endl;
                    }
                    else { // mashallah tabakarallah we are good
                        createShape(shapesArray, name, type, loc_x, loc_y, size_x, size_y);
                        cout << "Created ";
                        drawShape(shapesArray, name);
                        //cout << endl;
                    }
                }
            }


            else if(command == "move"){
                string name;
                string loc1_str, loc2_str;
                int loc1,loc2;
                bool flag = false;
                // lineStream >> name >> loc1_str >> loc2_str;

                lineStream >> name;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                    } 
                    
                    else {
                        cout << "Error: invalid argument" << endl;
                    }
                    flag = true;
                } 

                else if(!shapeNameExists(shapesArray, name)){
                    cout << "Error: shape " << name << " not found" << endl;
                    flag = true;
                }

                // now for loc1

                if(!flag){
                    lineStream >> loc1_str;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidIntArg(loc1_str, loc1)) {
                        cout << "Error: invalid argument" << endl;
                        flag = true;
                    }
                }

                //now for loc2

                if(!flag){
                    lineStream >> loc2_str;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidIntArg(loc2_str, loc2)) {
                        cout << "Error: invalid argument" << endl;
                        flag = true;
                    }
                }

                //now the rest of the checks
                if(!flag){
                    if (finalErrorCheck(lineStream) != 0) { //throwing -1
                        cout << "Error: too many arguments" << endl;
                    }

                    else if (!areValidValues(loc1, loc2, 0, 0, 0, " ")) { //angle doesnt matter
                        cout << "Error: invalid value" << endl;
                    }

                    else { // mashallah tabakarallah we are good
                        Shape* sh = findShape(shapesArray, name);
                        if(sh!= NULL){
                            sh->setXlocation(loc1);
                            sh->setYlocation(loc2);
                            cout << "Moved " << name << " to " << loc1 << " " << loc2 << endl;
                        }

                        else{
                            cout << "Error: shape " << name << " not found" << endl;
                        }
                    }
                }
                
            }

            else if(command == "rotate"){
                string name;
                string angle_str;
                int angle;
                bool flag = false;
                // lineStream >> name >> angle_str;

                lineStream >> name;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                    } 
                    
                    else {
                        cout << "Error: invalid argument" << endl;
                    }
                    flag = true;
                } 

                else if(!shapeNameExists(shapesArray, name)){
                    cout << "Error: shape " << name << " not found" << endl;
                    flag = true;
                }

                //now for the angle 
                if(!flag){
                    lineStream >> angle_str;
                    if (lineStream.fail()) {
                        if (lineStream.eof()) {
                            cout << "Error: too few arguments" << endl;
                        } 
                        
                        else {
                            cout << "Error: invalid argument" << endl;
                        }
                        flag = true;
                    } 
                    
                    else if (!isValidIntArg(angle_str, angle)) {
                        cout << "Error: invalid argument" << endl;
                        flag = true;
                    }
                }



                if(!flag){

                    if (finalErrorCheck(lineStream) != 0) { //throwing -1
                        cout << "Error: too many arguments" << endl;
                    }
                    else if (!areValidValues(0,0,0,0,angle, " ")) { //angle does matter, type does not 
                        cout << "Error: invalid value" << endl;
                    }

                    else { // mashallah tabakarallah we are good
                        Shape* sh = findShape(shapesArray, name);
                        if(sh!= NULL){
                            sh->setRotate(angle);
                            cout << "Rotated " << name << " by " << angle << " degrees." << endl;
                        }

                        else{
                            cout << "Error: shape " << name << " not found" << endl;
                        }
                    }
                }

            }


            else if(command == "draw"){
                string name_or_all;
                lineStream >> name_or_all;
                bool flag = false;

                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                    } 
                    
                    else {
                        cout << "Error: invalid argument" << endl;
                    }
                    flag = true;
                } 

                else if(!shapeNameExists(shapesArray, name_or_all) && name_or_all != "all"){
                    cout << "Error: shape " << name_or_all << " not found" << endl;
                    flag = true;
                }

                if(!flag){

                    if (finalErrorCheck(lineStream) != 0) { //throwing -1
                        cout << "Error: too many arguments" << endl;
                    }

                    else { // mashallah tabakarallah we are good
                        if(name_or_all == "all"){ 
                            cout << "Drew all shapes " << endl;
                            drawShapes(shapesArray); 
                        }

                        else{
                            cout << "Drew ";
                            drawShape(shapesArray, name_or_all);
                        }

                    }
                }
            }



            else if(command == "delete"){
                string name_or_all;
                lineStream >> name_or_all;
                bool flag = false;

                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                    } 
                    
                    else {
                        cout << "Error: invalid argument" << endl;
                    }
                    flag = true;
                } 

                else if(!shapeNameExists(shapesArray, name_or_all) && name_or_all != "all"){
                    cout << "Error: shape " << name_or_all << " not found" << endl;
                    flag = true;
                }

                if(!flag){

                    if (finalErrorCheck(lineStream) != 0) { //throwing -1
                        cout << "Error: too many arguments" << endl;
                    }

                    else { // mashallah tabakarallah we are good
                        if(name_or_all == "all"){ 
                            deleteShapes(shapesArray);
                            cout << "Deleted: all shapes" << endl;
                        }

                        else{
                            deleteShape(shapesArray, name_or_all);
                        cout << "Deleted shape " << name_or_all << endl;
                        }


                    }
                }
            }
        }

        else {
            cout << "Error: invalid command" << endl;
        }

        /****************************************************************************************/
        
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

/****************************************************************HELPER FUNCTIONS****************************************************************/

void createShape(Shape** shapesArray, const string& name, const string& type, int loc_x, int loc_y, int size_x, int size_y){
    //Shape::Shape(string n, string t, int x_loc, int x_sz, int y_loc, int y_sz)
    if(!isArrayFull(shapesArray)){ // if the array is not full, we can add another shape to it
        shapesArray[shapeCount] = new Shape(name, type, loc_x, size_x, loc_y, size_y);
        // cout << "Drew ";
        // drawShape(shapesArray, name);
        // cout << endl;
        shapeCount++; 
    } 
}


Shape* findShape(Shape** shapesArray, const string& name){ //find and return a particular shape
    if(shapeNameExists(shapesArray, name)){ //if the shape exists in the array
        for(int i = 0; i<shapeCount; i++){
            if(shapesArray[i] != NULL){
                if(shapesArray[i]->getName() == name){
                    return shapesArray[i];
                }
            }
        }
    }

    return NULL;

}

void moveShape(Shape** shapesArray, const string& name, int loc_x, int loc_y){ 
    //move a particular shape 
    Shape* sh = findShape(shapesArray, name);
    if(sh!=NULL){
        sh->setXlocation(loc_x);
        sh->setYlocation(loc_y);
    }
}

void rotateShape(Shape** shapesArray, const string& name, int angle){ //rotate a particular shape
    Shape* sh = findShape(shapesArray, name);
    if(sh!=NULL){
        sh->setRotate(angle);
    }
}

void drawShape(Shape** shapesArray, const string& name){ //draw a particular shape
    Shape* sh = findShape(shapesArray, name);
    if(sh!=NULL){
        sh->draw(); //does the prints for us 
        cout << endl;
    }
}

void drawShapes(Shape** shapesArray){ //draw all shapes
    for(int i = 0; i<shapeCount; i++){
        if(shapesArray[i]!=NULL){
            shapesArray[i]->draw(); //does the prints for us
        }
    }
    cout << endl;
}

void deleteShape(Shape** shapesArray, const string& name){ //delete a particular shape
    if(shapeNameExists(shapesArray, name)){ //if the shape exists in the array
        for(int i = 0; i<shapeCount; i++){
            if(shapesArray[i]!=NULL && shapesArray[i]->getName() == name){ //we found the shape we want to delete 
                delete shapesArray[i];
                shapesArray[i] = NULL;
                shapeCount--;
                return;
            }
        }
    }

}

void deleteShapes(Shape** shapesArray){ //delete all shapes in the array
    for(int i = 0; i<shapeCount; i++){
        if(shapesArray[i]!=NULL){
            delete shapesArray[i];
            shapesArray[i] = NULL;
            shapeCount--;
        }
    }
}

/***************************************************************ERROR FUNCTIONS****************************************************************/

bool isValidCommand(const string& command){
    for(int i = 0; i< 7; i++){
        if(command == keyWordsList[i]){
            return true;
        }
    }

    return false; //The first word entered does not match one of the valid commands

}
bool isValidIntArg(const string& arg, int& val) {
    stringstream s(arg);
    
    if (!(s >> val)) {
        //couldnt read an int
        return false;
    }
    
    // check th next character
    int next_char = s.peek();
    
    if (next_char != EOF) {
        // extra character after the integer
        return false;
    }

    return true;
}


bool isValidStringArg(const string& arg, string& val){
    stringstream s(arg);

    if(s >> val){ //if we can read the argument, it is indeed a string 
        return true;
    }

    return false;
}

bool isReservedName(const string& n){
    //The name used for a shape is a reserved word (e.g., a command name or a shape type)
    //returns true if the name is reserved and is therefore invalid

    for(int i = 0; i<7; i++){
        if(n == keyWordsList[i]){
            return true;
        }
    }

    for(int i = 0; i< 4; i++){
        if(n == shapeTypesList[i]){
            return true;
        }
    }

    return false;

}

bool shapeNameExists(Shape** shapesArray, const string& name) {
    for (int i = 0; i < shapeCount; ++i) {
        if (shapesArray[i] != NULL && name == shapesArray[i]->getName()) {
            return true;
        }
    }
    return false;
}


bool shapeNotFound(Shape** shapesArray, const string& n){
    //returns true if we cannot find the shape
    for(int i = 0; i < shapeCount; i++){
        if(n == shapesArray[i]->getName()){
            return false;
        }
    }

    return true;
}

bool isValidShapeType(const string& type){
    for(int i = 0; i<4; i++){
        if(type == shapeTypesList[i]){
            return true;
        }
    }

    return false;
}

bool areValidValues(int loc_x, int loc_y, int size_x, int size_y, int angle, string type){ 
    //value specified in a command is valid 
    //value less than 0 for location or size argument
    if(type == "circle" && size_x!=size_y){
        return false;
    }

    else if(loc_x < 0|| loc_y < 0|| size_x < 0|| size_y < 0){
        return false;
    }

    else if(angle < 0 || angle > 360){
        return false;
    }

    return true;

}


bool isArrayFull(Shape** shapesArray){
    //an attempt to create more shapes than the argument given to the maxShapes command 
    if(shapeCount == max_shapes){
        return true;
    }

    return false;
}

int finalErrorCheck(stringstream& ss) {
    // ignore leading spaces
    while(ss.peek() == ' ') {
        ss.ignore();
    }

    // anything left that is not a space 
    if (ss.eof()) {
        // we gooooood
        return 0;
    } else {
        //too many args
        return -1;
    }
}



