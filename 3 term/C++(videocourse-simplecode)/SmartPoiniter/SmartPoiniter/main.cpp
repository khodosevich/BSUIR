#include <iostream>
using namespace std;

template<typename T>
class SmartPointer{

public:

    SmartPointer(T *ptr){
        this->ptr = ptr;
        cout << "Construct" << endl;
    }
    
    ~SmartPointer(){
        delete this->ptr;
        cout << "Destruct" << endl;
    }
    
    T& operator *(){
        return *ptr;
    }
    
private:
    T *ptr;
};


int main() {
    
    SmartPointer<int> pointer = new int('5');
    
    *pointer = 555;
    
    cout << *pointer << endl;
    
    return 0;
}
