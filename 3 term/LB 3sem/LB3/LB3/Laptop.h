#ifndef Laptop_h
#define Laptop_h
#include "Portable.h"

class Laptop:public Portable {
    int keyboard;
    
public:
    int GetKeyboard(){
        return keyboard;
    }
    
    void SetKeyboard(int number){
        keyboard = number;
    }
    
};

#endif /* Laptop_h */
