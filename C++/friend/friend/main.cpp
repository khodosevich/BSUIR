#include <iostream>
using namespace std;

class Apple;

class Human{
public:
    void TakeApple(Apple &apple);
};


class Apple{
    
    friend void Human::TakeApple(Apple &apple);
    
public:
    int weight;
    string color;
    
    

public:
    Apple(int weight,string color){
        this->weight = weight;
        this->color = color;
    }
    
    void print();
    
};

void Apple::print(){
    cout << weight << "\t" <<color << endl;
}

int main() {

    Apple a(15,"green");

    a.print();
    
    Human n;
    n.TakeApple(a);
    return 0;
}


void Human::TakeApple(Apple &apple){
    cout << apple.color << "\t" << apple.weight << endl;
}
