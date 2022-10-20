#include <iostream>
using namespace std;

class Car{
public:
    void Use(){
        cout << "I drive" << endl;
    }
};

class Airplane{
  
public:
    void Use(){
        cout << "I fly" << endl;
    }
};

class FlyingCar : public Car , public Airplane{
    
};



int main() {
    
    
    FlyingCar a;
    
    ((Airplane)a).Use();
    
    return 0;
}
