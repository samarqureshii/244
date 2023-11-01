#include <iostream>
 using namespace std;
 #include <sstream>
 #include <string>
 #include <fstream>

// //Question 2 in Fall 2021 Final Exam [Intermediate]
// using namespace std;

// void readInts(){
//     int a = 0 ;
//     while(!cin.fail()){ //while we keep reading numbers
//         cin >> a;
//         cout << a << endl;
//     }

//     //atp we have errored, as we've hit non integer "." or we've hit another type of non integer 
//     cin.clear(); //we don't want to ignore the failed character!
//     string c;
//     cin >> c;
//     //in the case that we are done
//     if(c == "."){
//         cout << "Done";
//     }

//     else{ //c was not a dot, and was some other thing
//         cout << "Error";
//     }
// }

//Question 3 in Fall 2018 Midterm Exam [Intermediate]

// function prototype
bool handle_count(int& intArg, stringstream& line){ //pass both by reference
    line >> intArg; 
    //assume that we have left off after command, and now the stream stream pointer is right before possible int
    
    if(line.fail()){ //next
        return false;
        //the next characters after the command were not integers
    }
    
    string c;
    line >> c;
    if(line.fail()){ //string stream failed because there is nothing else after the number, //user has correctly formatted the comand
        return true;
    }

    else{
        return false;

    }


}

int main() {
  string line;
  string command;
  int intArg;
  getline(cin, line);
  stringstream lineStream(line);
  lineStream >> command;
  if (command == "count") {
    if (handle_count(intArg, lineStream)) {
      cout << "Integer argument is " << intArg << endl;
      return (0);
    } else {
      cout << "Invalid arguments" << endl;
      return (-1);
    }
  } else {
    cout << "Invalid command" << endl;
    return (-1);
  }
}


// //Question 7 in Fall 2019 Midterm Exam [Intermediate]
// void readInts(){
//     //reads integers from the standard input using cin and outputs input integer using out)
//     //outputs one integer per line 

//     //when the end of file is reached, function pritns "End of File Reached" before returning
//     //non-integer input throws "Invalid Input", discrads rest of the stream
//     //continues reading integers 

//     int num;
//     while(!cin.eof()){
//         cin >> num;
//         if(cin.fail()){
//             cout << "Invalid Input";
//             cin.clear();
//             cin.ignore(1000, '\n');
//         }

//         else{
//             cout << num << endl;
//         }

//     }

//     cout << "End of File Reached";


// }

