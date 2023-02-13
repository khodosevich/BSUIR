#include <iostream>
using namespace std;

class Point{
private:
    int x;
    int y;
public:

    int GetX(){
        return x;
    }

    void SetX(int value){
        x = value;
    }


    int GetY(){
            return y;
    }

    void SetY(int value){
        y = value * 2;
    }

    void Prinf(){
        cout << "X = " << x << "\tY = " << y << endl << endl;
    }
};


int main() {

    Point a;

    a.SetX(55);
    a.SetY(99);
    a.Prinf();

    int res = a.GetX();
    int res1 = a.GetY();

    cout << "X = " << res << "\tY = " << res1 << endl << endl;




    return 0;
}
