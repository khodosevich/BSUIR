#include <iostream>
using namespace std;

class counter{

private:
 
    int x;
    int y;
    
public:
    
    counter(){
        x = y = 0;
    }
    
    counter(int x , int y){
        this->x = x;
        this->y = y;
    }
        
    void add_dist(counter ,counter);
    
    void showdist(){
        cout << x << " \t " << y << endl;
    }
};

void counter::add_dist(counter s1, counter s2){
        
    
    this->x = s1.x + s2.x;
    this->y = s1.y + s2.y;
    
}

int main() {
    
    counter s1(5,6);
    counter s2(4,6);
  
    cout << "s1: " << endl;
    s1.showdist();
    cout << "s2: " << endl;
    s2.showdist();
    
    counter s3;
    
    
    cout << "s3 = s1 + s2 " << endl;
    s3.add_dist(s1, s2);
    s3.showdist();
    
    return 0;
}
