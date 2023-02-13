#include <iostream>
using namespace std;


class Point{
public:
    Point(){
        z = x = y = 0;
    }
    
    Point(double x,double y,double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    double x;
    double y;
    double z;
    string str;
    
    
};

template<typename T>
class Myclass{
public:
    
    Myclass(T value){
        this->value = value;
    }
    
    void print(){
        cout << sizeof(value) << endl;
    }
    
    T foo(){return value;}
    
private:
    T value;
};


int main() {
    
    int b = 999;
    char c = 'c';
    float f = 175.4;
    string str = "hello world";
    double d = 2;
    
    
    Myclass <int> a(b);
    Myclass <char> a1(c);
    Myclass <float> a2(f);
    Myclass <string> a3(str);
    Myclass <double> a4(d);
    
    a.print();
    int p = a.foo();
    cout <<"Int : " << p << endl;
    a1.print();
    a2.print();
    a3.print();
    string str1 = a3.foo();
    cout << str1 << endl;
    a4.print();
    
    cout << endl << endl;
    
    Point x;
    
    Myclass<Point> q(x);
    
    q.print();
    
    cout << endl << endl;
    
    
    return 0;
}
