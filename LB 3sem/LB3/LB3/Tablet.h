#ifndef Tablet_h
#define Tablet_h
#include "Portable.h"

class Tablet:public Portable {
    char *modem;
    
public:
    
    char* GetTablet(){
        return modem;
    }
    
    void SetTablet(char *type){
        
        int len = strlen(type);
        modem = new char[len + 1];
        
        for (int i = 0 ; i < len; i++) {
            modem[i] = type[i];
        }
        
        modem[len] = '\0';
    }

};

#endif /* Tablet_h */
