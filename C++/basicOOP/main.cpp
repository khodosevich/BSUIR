#include <iostream>
#include <string>
using namespace std;


class Human{
public:
    string Name;
    int Age;
    int Weight;


    void Print(){
        cout << "Name: " << Name << "\nAge: " << Age << "\nWeight: " << Weight << endl << endl;
    }
};


int main() {

    Human FirstHuman;
    FirstHuman.Name = "Matvey";
    FirstHuman.Age = 19;
    FirstHuman.Weight = 84;

    FirstHuman.Print();


    Human SecondHuman;
    SecondHuman.Name = "Ivan";
    SecondHuman.Age = 18;
    SecondHuman.Weight = 76;

    SecondHuman.Print();

    return 0;
}
