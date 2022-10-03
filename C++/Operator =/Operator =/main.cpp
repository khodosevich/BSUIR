#include <iostream>
using namespace std;


class Myclass{
    
    int *arr;
    int size;
    
public:
    
    Myclass(int size){
        this->size = size;
        arr = new int[size];
        
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 100;
        }
    }
    
    Myclass(const Myclass& other){
        this->size = other.size;
        this->arr = new int[this->size];
        
        for (int i = 0; i < size; i++) {
            this->arr[i] = other.arr[i];
        }
    }
    
    Myclass & operator = (const Myclass &other){
        this->size = other.size;
        
        delete []this->arr;
        
        this->arr = new int[other.size];
        
        for (int i = 0; i < size; i++) {
            this->arr[i] = other.arr[i];
        }
        
        return *this;
    }
   
    void print(){
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    ~Myclass(){
        delete []arr;
    }
    
    
};


int main() {
   
    Myclass a(5);
    Myclass b(a);

    a.print();
    b.print();
    
    cout << endl;
    cout << endl;
    cout << "===================================="<< endl;
    cout << endl;
    cout << endl;
    
    Myclass q(1);
    Myclass w(2);
    Myclass e(2);
    Myclass r(5);
    Myclass t(2);
    Myclass y(5);
    
    q = w = e = r = t = y;
    
    q.print();
    w.print();
    e.print();
    r.print();
    t.print();
    y.print();
    
    

    return 0;
}
