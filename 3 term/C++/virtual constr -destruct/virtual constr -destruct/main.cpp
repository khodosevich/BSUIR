#include <iostream>
using namespace std;

class A{
public:
    A(){
        cout << "Выделение динамической памяти А" << endl;
    }
    
    virtual ~A(){
        cout << "Очистка динамической памяти А" << endl;
    }
};

class B:public A{
public:
    B(){
        cout << "Выделение динамической памяти B" << endl;
    }
    
    ~B() override{
        cout << "Очистка динамической памяти В" << endl;
    }
};


int main() {
    
    A *b = new B;
    
    delete b;
    
    return 0;
}

