#ifndef Monoblock_h
#define Monoblock_h
#include "desktop.h"

class Monoblock:public Desktop{
protected:
    double screen;
 
public:
    int GetSceen(){
        return screen;
    }
    
    void SetScreen(double dm){
        screen = dm;
    }
    
};

#endif /* Monoblock_h */
