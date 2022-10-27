#include <iostream>
using namespace std;

class Component{
public:
    Component(string companyName){
        cout << "Component" << endl;
        this->companyName = companyName;
    }
    string companyName;
};

class GPU:public Component{
public:
    GPU(string GPUName):Component(GPUName){
        cout << "GPU" << endl;
    }
};

class memory:public Component{
public:
    memory(string memory):Component(memory){
        cout << "Memory" << endl;
    }
};


class GraphicCard:public GPU,public memory{
public:
    GraphicCard(string GraphicGPU,string GraphicMemory):GPU(GraphicGPU),memory(GraphicMemory)
    {
        cout << "GraphicCard" << endl;
    }
};


class Character{
public:
    Character(){
        cout << "Charecter" << endl;
    }
    int HP;
};


class Orc:public virtual Character{
public:
    Orc(){
        cout << "Orc" << endl;
    }
};



class Warior:public virtual Character{
public:
    Warior(){
        cout << "Warior" << endl;
    }
};

class OrcWarrior:public Orc, public Warior{
public:
    OrcWarrior(){
        cout << "OrcWarrior" << endl;
    }
};



int main(){
  
    cout << "Without virtual:"<< endl;
    GraphicCard("AMD","Samsung");
    cout << endl << endl;
    
    cout << "With virtual:"<< endl;
    OrcWarrior();
    cout << endl << endl;
    
    return 0;
}
