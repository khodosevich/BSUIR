#include <iostream>
using namespace std;

class Constr{
private:
    int x;
    int y;
    
public:
    Constr(int valueX, int valueY){
        x = valueX;
        y = valueY;
    }
    
    void start(){
        cout << "X = " << x << "\tY = " << y << endl << endl;
    }
    
};

int main() {
    
    Constr a(2,12);
    a.start();
    
    
    Constr b(44,77);
    b.start();
    
    return 0;
}
