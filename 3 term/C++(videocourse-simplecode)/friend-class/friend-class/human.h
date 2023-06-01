#ifndef human_h
#define human_h
#include "apple.h"
using namespace std;

class human{
public:
    void takeapple(apple &Apple);
    
    
};


void human::takeapple(apple &Apple){
    cout << Apple.weight << "\t" << Apple.color << endl;
}

#endif /* human_h */
