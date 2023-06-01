#ifndef Exception_h
#define Exception_h
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

class MyException:public exception {
    
public:
    
    static void isEmpty(){
        cout<< endl << "LinkedList is empty" << endl;
    }
 
    static void LinkedListHasThisEl(){
        cout << endl << "Not this index in this List" << endl;
    }
    
    static void Error(){
        cout << endl << "Что-то пошло не так.." << endl;
        exit(1);
    }
 
};



#endif

