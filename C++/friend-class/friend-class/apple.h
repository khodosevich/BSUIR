#ifndef apple_h
#define apple_h
#include "human.h"
using namespace std;


class apple{
    friend human;
    
public:
    
    apple(int weight, string color){
        this->weight = weight;
        this->color = color;
    }
    
    
private:
    int weight;
    string color;
    
};

#endif /* apple_h */
