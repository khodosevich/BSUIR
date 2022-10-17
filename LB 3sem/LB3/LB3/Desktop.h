#ifndef Desktop_h
#define Desktop_h
#include "computer.h"

class Desktop:public Computer{
protected:
    char *corpus;

public:
    
    char* GetCorpus(){
        return corpus;
    }
    
    void SetCorpus(char* corp){
        int len = strlen(corp);
        corpus = new char[len + 1];
        
        for (int i = 0 ; i < len; i++) {
            corpus[i] = corp[i];
        }
        
        corpus[len] = '\0';
    }
    
};

#endif /* Desktop_h */
