#ifndef Portable_h
#define Portable_h
#include "computer.h"

class Portable:public Computer{
protected:
    int charge;
    double screen;
   
public:
    
    int getCharge(){
        return charge;
    }
    
    void setCharge(int procent){
        
        charge = procent;
        
    }
    
    double getScreen(){
        return screen;
    }
    
    void setScreen(double dm){
        screen = dm;
    }
   
  
};

#endif /* Portable_h */
