#ifndef computer_h
#define computer_h
#include <iostream>
using namespace std;

class Computer{
protected:
    char *brand;
    char *model;
    
public:
    
    Computer(){
        brand = nullptr;
    }
    
    Computer(char *str){
        
        int len = strlen(str);
        brand = new char[len + 1];
        
        for (int i = 0 ; i < len; i++) {
            brand[i] = str[i];
        }
        
        brand[len] = '\0';
    }
    
    ~Computer(){
        delete []brand;
    }
    
    char* getBrand(){
        return brand;
    }
    
    void setBrand(char *str){
        
        int len = strlen(str);
        brand = new char[len + 1];
        
        for (int i = 0 ; i < len; i++) {
            brand[i] = str[i];
        }
        
        brand[len] = '\0';
    }
    
    char* getModel(){
        return model;
    }
    
    void setModel(char *str){
        
        int len = strlen(str);
        model = new char[len + 1];
        
        for (int i = 0 ; i < len; i++) {
            model[i] = str[i];
        }
        
        model[len] = '\0';
    }

    
};

#endif /* computer_h */
