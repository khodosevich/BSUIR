#include <iostream>
using namespace std;

class Point{
    int x;
    int y;
    
public:
    Point(){
        this->x = 0;
        this->y = 0;
    }
    
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    
    Point operator +(const Point & other){
        Point temp;
        
        temp.x = this->x + other.x;
        temp.y = this->y + other.y;
        
        return temp;
    }
    
    Point operator -(const Point & other){
        Point temp;
        
        temp.x = this->x - other.x;
        temp.y = this->y - other.y;
        
        return temp;
    }
    
    Point operator *(const Point & other){
        Point temp;
        
        temp.x = this->x * other.x;
        temp.y = this->y * other.y;
        
        return temp;
    }
    
    Point operator /(const Point & other){
        Point temp;
        
        temp.x = this->x / other.x;
        temp.y = this->y / other.y;
        
        return temp;
    }
    
    
    
    
    
    void print(){
        cout <<"X = " << this->x << "\tY = " << this->y << endl;
    }

    
};


int main() {
    Point a(12,44);
    Point b(5,6);
    
    Point c = a + b;
    
    c.print();
    
    Point q(5,3);
    Point w(5,6);
    
    Point e = q - w;
    
    e.print();
    
    Point qq(5,3);
    Point ww(5,6);
    
    Point ee = qq * ww;
    
    ee.print();
    
    Point qqq(25,36);
    Point www(5,6);
    
    Point eee = qqq / www;
    
    eee.print();
    
    return 0;
}
