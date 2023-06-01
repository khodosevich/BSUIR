#ifndef array_h
#define array_h
#include <iostream>
using namespace std;

class Array
{
    int* arr;
    int size;

public:
    Array() {
        size = 0;
        arr = new int[size];
    }

    Array(int size) {
        if (size > 0) {
            this->arr = new int[size];
            this->size = size;
        }
        else {
            cout << "Invalid capacity!!!";
        }
    }


    Array(const Array& copyArr) {

        this->size = copyArr.size;
        this->arr = new int[size];

        for (int i = 0; i < this->size; i++) {
            this->arr[i] = copyArr.arr[i];
        }
    }

    void fillarray() {
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

    ~Array() {
        delete[]arr;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }


    Array operator +(const Array &other){

        Array temp;
        int length = this->size + other.size;
        temp.arr = new int[length];
        temp.size = length;

        
        for (int i = 0; i < this->size; ++i) {
               temp.arr[i] = this->arr[i];
           }
        
        for (int i = 0; i < other.size; i++) {
            temp.arr[i + this->size] = other.arr[i];
        }

        return temp;
       }
    
    Array operator &(const Array &other){

        Array temp;
        int length;
        
        if(this->size > other.size){
            length = this->size;
        }else length = other.size;
        
        temp.arr = new int[length];
        temp.size = length;

        
        for (int i = 0; i < this->size; ++i) {
               temp.arr[i] = this->arr[i] & other.arr[i];
           }
        
        return temp;
       }

};


#endif /* array_h */
