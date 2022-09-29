#include <iostream>
using namespace std;

class Myclass{
    int *data;
public:
    Myclass(int value){
        data = new int[value];
        for(int i = 0; i < value; i++){
            data[i] = i;
        }
        
        for(int i = 0; i < value; i++){
            cout << data[i] << " ";
        }
       
       
    }
    
    ~Myclass(){
        delete []data;
        cout << "Value = " << data << "\tDestructor" << endl;
    }
    
};

void Foo(){
    cout << "start program" << endl;
    Myclass a(5);
    cout << endl;
    cout << "end program" << endl;
}

int main() {
    
    Foo();
  
    return 0;
}
