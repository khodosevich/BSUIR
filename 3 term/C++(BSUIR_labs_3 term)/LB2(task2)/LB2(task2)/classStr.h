#ifndef classStr_h
#define classStr_h
#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
private:
    char *str;

public:
    
    
    MyString(){
        str = nullptr;
    }
    
    MyString(char *str){
        int lenth = strlen(str);
        this->str = new char[lenth + 1];
        strcpy(this->str, str);
        this->str[lenth] = '\0';
    }
    
    ~MyString(){
        delete []this->str;
    }
    
    void print(){
        cout << str << endl;
    }
   
    MyString& operator =(const MyString &other){
        
        
        if(this->str != nullptr){
            delete []this->str;
        }
        
        int lenth = strlen(other.str);
        
        this->str = new char[lenth + 1];
        
        for (int i = 0; i < lenth; i++) {
            str[i] = other.str[i];
        }
        this->str[lenth] = '\0';
        
        return *this;
    }
    
    MyString operator +(const MyString &other){
        
        MyString temp;
        
        int lenth;
        lenth = strlen(this->str) + strlen(other.str);
        temp = new char[lenth + 1];
        
        for (int i = 0; i < strlen(this->str); i++) {
            temp.str[i] = this->str[i];
        }
        
        for (int i = 0; i < strlen(other.str); i++) {
            temp.str[i + strlen(this->str)] = this->str[i];
        }
        
        temp.str[lenth] = '\0';
        
        return temp;
    }
    
    MyString& operator +=(const MyString &other){
    
        char *temp;
        int lenth;
        lenth = strlen(this->str) + strlen(other.str);
        temp = new char[lenth + 1];
        
        for (int i = 0; i < strlen(this->str); i++) {
            temp[i] = this->str[i];
        }
        
        for (int i = 0; i < strlen(other.str); i++) {
            temp[i + strlen(this->str)] = this->str[i];
        }
        
        delete []this->str;
        
        this->str = temp;
        
        return *this;
    }
    
    bool operator ==(const MyString &other){
        
        if(strlen(this->str) == strlen(other.str)){
            for(int i = 0; i < strlen(this->str); i++){
                this->str[i] == other.str[i];
            }
            return 1;
        }else return 0;
    }
    
    bool operator !=(const MyString &other){
        
        if(strlen(this->str) == strlen(other.str)){
            for(int i = 0; i < strlen(this->str); i++){
                this->str[i] == other.str[i];
            }
            return 0;
        }else return 1;
    }
    
    char & operator [](int index){
        return  this->str[index];
    }
    
    MyString operator ()(int a,int b) {
        
        char * s = new char[b-a+2];
        for(int i = a; i <= b; i++){
            s[i-a] = str[i];
        }
        s[b-a+1] = '\0';
        
        
        delete []str;
        
        str = new char[strlen(s)];
        for (int i = 0; i < strlen(s); i++) {
            str[i] = s[i];
        }
        delete[]s;
        
        return str;
        }
    
};

#endif /* classStr_h */
