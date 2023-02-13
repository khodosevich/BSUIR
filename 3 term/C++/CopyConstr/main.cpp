#include <iostream>
using namespace std;

class Array {
    int *arr;
    int size;

public:

    Array(int size){
        this->size = size;
        arr = new int[size];

        for (int i = 0; i < size; ++i) {
            arr[i] = i;
        }
    }

    Array(const Array& CopyArr){

        this->size = CopyArr.size;
        this->arr = new int[size];

        for (int i = 0; i < size; ++i) {
            this->arr[i] = CopyArr.arr[i];
        }
    }

    ~Array(){
        delete []arr;
    }

    void print(){
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

};

int main() {

    Array array1(10);
    Array array2(array1);

    array1.print();
    array2.print();

    return 0;
}
