#ifndef string_h
#define string_h
#include <iostream>
using namespace std;

class MyString{
private:
    char *str;
    
public:
    MyString(){
        str = nullptr;
    }
    
    MyString(char *str){
        int len = strlen(str);
        this->str = new char[len + 1];
        
        for (int i = 0; i < len; i++) {
            this->str[i] = str[i];
        }
        
        this->str[len] = '\0';
    }
    

    
    ~MyString(){
        delete []this->str;
    }
    
    MyString(const MyString &other){
        
        int len = strlen(other.str);
        this->str = new char[len + 1];
        
        for (int i = 0; i < len; i++) {
            this->str[i] = other.str[i];
        }
        
        this->str[len] = '\0';
    }
    
    MyString& operator = (const MyString &other){
        
        int len = strlen(other.str);
        delete []this->str;
        
        this->str = new char[len + 1];
        
        for (int i = 0; i < len; i++) {
            this->str[i] = other.str[i];
        }
        
        this->str[len] = '\0';
        
        return *this;
    }
    
    MyString operator + (const MyString &other){
        
        MyString temp;
        
        int len1 = strlen(this->str);
        int len2 = strlen(other.str);
        int len = len1 + len2;
        
        
        temp.str = new char[len + 1];
        
        for (int i = 0; i < len1; i++) {
            temp.str[i] = this->str[i];
        }
        
        for (int i = 0; i < len2; i++) {
            temp.str[i + len1] = other.str[i];
        }
        
        temp.str[len] = '\0';
        
        return temp;
    }
    
    
    void print(){
        
        for (int i = 0; i < strlen(this->str); i++) {
            cout << this->str[i];
        }
        cout << endl;
    }
    
    
    bool operator ==(const MyString& other){
        int len1 = strlen(this->str);
        int len2 = strlen(other.str);
        
        if (len1 != len2) {
            return 0;
        }
    
        for (int i = 0; i < len1; i++) {
            if(this->str[i] != other.str[i]){
                return 0;
            }
            else return 1;
        }
        
     
        return 1;
    }
    
    char& operator [](int index){
        return this->str[index];
    }
    
};


#endif /* string_h */
