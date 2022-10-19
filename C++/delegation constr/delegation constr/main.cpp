#include <iostream>
using namespace std;

class A{
  
private:
    int age;
    string name;
    int a;
    
public:
    A(string name)
    {
        this->name = name;
    }
    
    A(int age,string name) :A(name)
    {
        this->age = age;
    }
    
    A(int age,string name , int a) :A(age,name)
    {
        this->a = a;
    }
    
    
};

int main() {
    
    return 0;
}
