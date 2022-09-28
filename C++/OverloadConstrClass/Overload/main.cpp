#include <iostream>
using namespace std;

class Name{
private:
    int x;
    int y;
    
public:
    Name(){
        x = 0;
        y = 0;
    }
    
    Name(int valueX, int valueY){
        x = valueX;
        y = valueY;
    }
    void print(){
        cout << "X = " << x << "\tY = " << y << endl << endl;
    }
};

int main() {

    Name a;
    a.print();
    
    Name b(4,77);
    b.print();
    
    return 0;
}
