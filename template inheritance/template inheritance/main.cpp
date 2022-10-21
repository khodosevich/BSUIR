#include <iostream>
//#include <typeinfo>
using namespace std;


template<class T1>
class Myclass{
public:
    
    Myclass(T1 value){
        this->value = value;
    }
    
    void print(){
        cout << sizeof(value) << endl;
    }
    
  
    
protected:
    T1 value;
};

template <class T1>
class TypeInfo : public Myclass<T1>{
    
public:
    
    TypeInfo(T1 value) : Myclass<T1>(value){
        
    }
    
    void ShowName(){
        cout << "Type name : "<< sizeof(value) << endl;
    }

    
private:
    T1 value;
};

int main() {
    
    double b = 9.5;
    
    TypeInfo <double> a(b);
    
    a.ShowName();
    
    return 0;
}
