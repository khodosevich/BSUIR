#include <iostream>
using namespace std;

//simple code lesson 8 hometask

int main() {

    int a,b,c,x,y;
    double z;

    cout << "Enter 3 number: ";
    cin >> a >> b >> c;

    x = a + b + c;
    cout << "Amount of a,b,c = " << x << endl ;

    y = a * b * c;
    cout << "mult of a,b,c = " << y << endl ;

    z = (double)(a + b + c) / 3;
    cout << "middle of a,b,c = " << z ;


    return 0;
}
