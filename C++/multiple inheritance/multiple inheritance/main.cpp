#include <iostream>
using namespace std;


class Car{
  
public:
    void Drive(){
        cout << "I drive" << endl;
    }
};

class Airplan{
public:
    void Fly(){
        cout << "I fly" << endl;
    };
};

class CarFly: public Car, public Airplan{

};

int main() {
    
    CarFly a;
    
    Car *b = &a;
    Airplan *c = &a;
    
    b->Drive();
    c->Fly();
    
    
    return 0;
}
