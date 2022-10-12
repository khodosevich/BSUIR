#include <iostream>
using namespace std;

class Array
{
public:
    int* arr;
    int size;

public:

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

    int getSize() {
        return size;
    }

    int* getArray() {
        return this->arr;
    }

    void setArr(int index, int value) {
        this->arr[index] = value;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }


    static int findMinIndex(Array element) {
        int minIndex = 0;
        int minValue = element.getArray()[minIndex];

        for (int i = 1; i < element.getSize(); i++) {
            if (minValue > element.getArray()[i]) {
                minIndex = i;
                minValue = element.getArray()[i];
            }
        }

        return minIndex;
    }

    static int findMaxIndex(Array element) {
        int maxIndex = 0;
        int maxValue = element.getArray()[maxIndex];

        for (int i = 1; i < element.getSize(); i++) {
            if (maxValue < element.getArray()[i]) {
                maxIndex = i;
                maxValue = element.getArray()[i];
            }
        }

        return maxIndex;
    }

    static void swap(Array &firstElement, Array &secondElement) {
        int minIndexInFirstElement = Array::findMinIndex(firstElement);
        int maxIndexInSecondElement = Array::findMaxIndex(secondElement);

        int temp = firstElement.getArray()[minIndexInFirstElement];
        firstElement.setArr(minIndexInFirstElement, secondElement.getArray()[maxIndexInSecondElement]);
        secondElement.setArr(maxIndexInSecondElement, temp);
    }
};


int main() {


    int size1,size2;
    cout << "Enter amount of first array: ";
    cin >> size1;
    cout << "Enter amount of second array: ";
    cin >> size2;


    Array array1 =  Array(size1);
    Array array2 =  Array(size2);

    cout << "Enter first array: ";
    array1.fillarray();
    cout << "Enter second array: ";
    array2.fillarray();

    cout << "=====================================" << endl;
    cout << "Array after fill: "<< endl;
    cout <<"First array: ";
    array1.print();
    cout <<"Second array: ";
    array2.print();

    cout << "=====================================" << endl;
    cout << "Min element in first array: " << array1.getArray()[Array::findMinIndex(array1)] << endl;
    cout << "Max element in second array: " << array2.getArray()[Array::findMaxIndex(array2)] << endl;
    cout << "=====================================" << endl;
    Array::swap(array1, array2);
    cout << "Array after change fill: "<< endl;

    cout <<"First array: ";
    array1.print();
    cout <<"Second array: ";
    array2.print();

    return 0;
}

