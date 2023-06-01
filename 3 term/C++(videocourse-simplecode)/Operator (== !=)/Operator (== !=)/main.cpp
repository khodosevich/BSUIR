#include <iostream>
using namespace std;

class Point{
    int x;
    int y;
    
public:
    Point(int a,int b){
        x = a;
        y = b;
    }
    
    bool operator == (const Point & other){
        return this->x == other.x && this->y == other.y;
    }
    bool operator != (const Point & other){
        return !(this->x == other.x && this->y == other.y);
    }
};

int main() {
    
    Point a(5,6);
    Point b(5,6);
    
    bool result = a == b;
    
    if(result){
        cout << "Elements is equal" << endl;
    }else cout << "Elements is not equal" << endl;
    
    
    bool result1 = a != b;
    
    if(result1){
        cout << "Program work!" << endl;
    }else cout << "Program dont work" << endl;
    
    return 0;
}
