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
        Count++;
        id = Count;
    }
    //лучше сделать через GET
    int GetCount(){
        return  this->id;
    }
    
    static int GetCount(apple &apple){
        return Count;
    }
    
    static void ChangColor(apple &apple, string color){
        apple.color = color;
    }
    
private:
    static int Count;
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
//    apple c(150,"green");
//    apple q(150,"green");
//    apple w(150,"green");
//
//    cout << a.GetCount() << endl;
//    cout << c.GetCount() << endl;
//    cout << q.GetCount() << endl;
//    cout << w.GetCount() << endl;
    
    human b;
    
    b.takeapple(a);
    
    a.ChangColor(a, "red");
    
    b.takeapple(a);
    
    return 0;
}
