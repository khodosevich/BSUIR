#include <iostream>
using namespace std;


class A{
    int a;
    int b;

public:

    A(){
    }

    A(int x,int y){
        a = x;
        b = y;
    }

    void sum(){
        int res;

        res = a + b;

        cout << res << endl;
    }

    void SetB(int b){
        this->b = b;
    };

    void SetA(int a){
        this->a = a;
    };

};



int main() {

    A a;
    a.SetA(9);
    a.SetB(9);
    a.sum();

    return 0;
}
