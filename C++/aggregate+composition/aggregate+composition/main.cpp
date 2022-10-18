#include <iostream>
using namespace std;

class Cap{
public:
    
    string GetColor(){
        return color;
    }
    
private:
    string color = "red";
};

class Human{
private:
    class Brain{
    public:
        void Think(){
            cout << "I think!" << endl;
        }
    };
    
    Brain brain;
    Cap cap;
public:
    
    void Think(){
        brain.Think();
    }
    
    void InspectTheCap(){
        cout << "Cap color is " << cap.GetColor() << endl;
    }
    
};

int main() {
  
    Human human;
    
    human.Think();
    
    human.InspectTheCap();
   
    
    //cout << cap.GetCap() << endl;
    
    return 0;
}
