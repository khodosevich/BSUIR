#include <iostream>
using namespace std;

class Gun{
  
public:
    virtual void Shoot(){
        cout << "Bang" << endl;
    }
};

class SubmachineGun:public Gun{
public:
    void Shoot() override{
        cout << "Bang bang bang" << endl;
    }
};

class Bazooka:public Gun{
    void Shoot() override{
        cout << "Badaboom!" << endl;
    }
};

class Player{
public:
    void Shoot(Gun *gun){
        gun->Shoot();
    }
};

int main() {
  
    Bazooka gun;
    
    Player player;
    player.Shoot(&gun);
    
    return 0;
}
