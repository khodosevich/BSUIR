#include <iostream>
using namespace std;

class IBicycle{

public:
    void virtual TwistTheWheel() = 0;
    void virtual Ride() = 0;
};


class SimpleBasic:public IBicycle{
public:
    
    void TwistTheWheel() override{
        cout << "Method TwistTheWheel() class SimpleBasic" << endl << endl;
    }
    
    void Ride() override{
        cout << "Method Ride() class SimpleBasic" << endl << endl;
    }
    
};


class SportBasic:public IBicycle{
public:
    
    void TwistTheWheel() override{
        cout << "Method TwistTheWheel() class SportBasic" << endl << endl;
    }
    
    void Ride() override{
        cout << "Method Ride() class SportBasic" << endl << endl;
    }
    
};

class Human{
public:
    void RideOn(IBicycle &bicycle){
        cout << "Twist Wheel " << endl ;
        bicycle.TwistTheWheel();
        cout << "Ride" << endl;
        bicycle.Ride();
        
    }
};


int main() {
    
    SimpleBasic sb;
    SportBasic spb;
    Human h;
    
    h.RideOn(sb);
    h.RideOn(spb);
    
    
    return 0;
}
