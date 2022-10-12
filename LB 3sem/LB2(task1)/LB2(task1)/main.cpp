#include <iostream>
#include "array.h"
using namespace std;


int main() {

    int size1,size2;
    cout << "Enter n first array : " ;
    cin >> size1;
    
    cout << "Enter n second array : " ;
    cin >> size2;
    
    Array array1(size1);
    Array array2(size2);

    cout << "Enter first array : " ;
    array1.fillarray();
    cout << "Enter second array: ";
    array2.fillarray();

    cout << endl;
    cout << endl;


    cout << "Overload operator '+' : " << endl;

    Array c = array1 + array2;

    c.print();

    cout << endl;
    cout << endl;


    cout << "Overload operator '&' : " << endl;

    Array e = array1 & array2;

    e.print();

    cout << endl << endl;
    
    
    return 0;
}
