#include <iostream>
using namespace std;

class Weapon{
public:
    virtual void Show() = 0;
};


class Gun : public Weapon{
public:
    void Show() override{
        cout << "Bang" << endl;
    }
};

class SubmachineGun : public Gun{
public:
    void Show() override{
        cout << "Bang bang bang" << endl;
    }
};


class Bazooka : public Weapon{
public:
    void Show() override{
        cout << "Badaboom" << endl;
    }
};

class Knife : public Weapon{
public:
    void Show() override{
        cout << "Vjuh" << endl;
    }
};

class Player{
public:
    void Show(Weapon *weapon){
        weapon->Show();
    }
};

int main() {
    
    Gun gun;
    SubmachineGun subman;
    Bazooka bz;
    Knife knife;
    
    Player play;
    
    play.Show(&bz);
    
    return 0;
}
