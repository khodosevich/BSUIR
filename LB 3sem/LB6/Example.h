#ifndef LB6_EXAMPLE_H
#define LB6_EXAMPLE_H
#include <iostream>
using namespace std;

class Person{

private:
    string Name;
    int Age;
    string LastName;

public:

    Person (){}

    Person(string _name,int _age, string _lastname){

        Name = _name;
        Age = _age;
        LastName = _lastname;

    }

    void PrintPerson(){

        cout << Name << "\t" << LastName << "\t" << Age << endl;

    }

    friend ostream& operator << (std::ostream &os, Person &p);
    friend istream& operator >> (std::istream& in, Person& p);

};

std::ostream& operator << (std::ostream &os, Person &p)
{
    os <<"\n"<< p.Name << " " << p.LastName << " " << p.Age;

    return os ;
}

std::istream& operator >> (std::istream& in, Person& p)
{
    in >> p.Name >> p.LastName >>  p.Age;

    return in;
}

#endif //LB6_EXAMPLE_H
