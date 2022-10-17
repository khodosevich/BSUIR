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
    
    static int Count;
    
    apple(int weight, string color){
        this->weight = weight;
        this->color = color;
        Count++;
        id = Count;
    }
    //лучше сделать через GET
    void printID(){
        cout << this->id << endl;
    }
    
private:
    int weight;
    string color;
    int id;
    
};

int apple::Count = 0;

void human::takeapple(apple &Apple){
    cout << Apple.weight << "\t" << Apple.color << endl;
}

void human::changeapple(apple &Apple){
    Apple.weight = 1900;
    Apple.color = "qqqq";
}

int main() {

    apple a(150,"green");
    apple c(150,"green");
    apple q(150,"green");
    apple w(150,"green");
  
    a.printID();
    c.printID();
    q.printID();
    w.printID();
    return 0;
}
