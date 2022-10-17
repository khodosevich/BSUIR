#include <iostream>
using namespace std;

class apple;

class human{
public:
    void takeapple(apple &Apple);
    void changeapple(apple &Apple);
};


class apple{
    friend human;
    
public:
    
    apple(int weight, string color){
        this->weight = weight;
        this->color = color;
    }
    
    
private:
    int weight;
    string color;
    
};


void human::takeapple(apple &Apple){
    cout << Apple.weight << "\t" << Apple.color << endl;
}

void human::changeapple(apple &Apple){
    Apple.weight = 1900;
    Apple.color = "qqqq";
}

int main() {

    apple a(150,"green");
    
    human b;
    
    b.takeapple(a);
    b.changeapple(a);
    b.takeapple(a);
    
    return 0;
}
