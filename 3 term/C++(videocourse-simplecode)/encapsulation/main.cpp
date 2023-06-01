#include <iostream>
using namespace std;

class CoffeeGrinder{
private:

    bool VoltCheck(){
        return true;
    }

public:

    void start(){

        if( VoltCheck())
            cout << "CoffeeGrinder is work!!!" << endl;
        else cout << "It is broken" << endl;
    }
};

int main() {

    CoffeeGrinder a;
    a.start();

    return 0;
}
