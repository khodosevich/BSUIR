#include <iostream>
#include <string>
using namespace std;

class Human{
public:
    int age;
    int weight;
    string name;
};

//расположение точки на осях координат
class Point{
public:
    int x;
    int y;
};

int main() {

    Human firstName;
    firstName.age = 19;
    firstName.name = "Khodosevich Matvey";
    firstName.weight = 84;
    cout << firstName.weight << endl;
    cout << firstName.age << "\n" << firstName.name << endl;

 cout << "=====================================" << endl;

    Human secondName;
    secondName.age = 17;
    secondName.name = "Champion";
    secondName.weight = 73;
    cout << secondName.weight << endl;
    cout << secondName.age << "\n" << secondName.name << endl;


    Point a;

    a.x = 2;
    a.y = 3;

    cout << "X = " << a.x << "\t" << "Y = " << a.y << endl;

    return 0;
}
