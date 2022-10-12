#include <iostream>
#include "classStr.h"
using namespace std;

int main() {
    
    MyString q("helloqqwe");
    MyString w("hello");
    
    q.print();
    w.print();
    
    cout << endl << endl;
    w = q;
    cout << "operator = : ";
    w.print();
    
    cout << endl << endl;
    
    MyString a;
    
    a = q + w;
    
    
    cout << "operator + : ";
    a.print();
    
    cout << endl << endl;
    
    
    
    cout << "operator += : ";
   
    q += w;
    q.print();
    
    cout << endl << endl;
    
    
    
    bool result = q == w;

    if(result){
        cout << "Elements similar" << endl;
    }else cout << "Elements is not similar" << endl;

    cout << endl << endl;

    bool result2 = q != w;

    if(result2){
        cout << "Elements !=" << endl;
    }else cout << "Elements ==" << endl;
    
    cout << endl << endl;
    
    
    cout << "operator [i] : ";
    
    cout << q[3];
    
    cout << endl << endl;
    
    
    
    cout << "operator ( )(0,4) : ";
    
    q(0,4);
    q.print();
    
    cout << endl << endl;
    

    
    
    return 0;
}
