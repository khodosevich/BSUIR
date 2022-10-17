#include <iostream>
#include "string.h"
using namespace std;

int main() {
   
    MyString a("helloo");
    MyString b("hello");
    
    MyString c;
    
    c = b + b;
    
    c.print();
    
    bool equal = a == b;
    
    a.print();
    a[3] = 'q';
    a.print();
    
    return 0;
}
