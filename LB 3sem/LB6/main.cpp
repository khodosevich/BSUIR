#include <iostream>
#include "FileBin.h"
#include "FileTxt.h"
#include "Example.h"
#include "MyContainer.h"

using namespace std;

int main() {





    List<Person> person;

    Person p("kirill",91,"kirillovich");
    Person x("maksim",19,"maksimovich");
    Person y("vasya",18,"vasiliy");

    person.push_back(p);
    person.push_back(x);
    person.push_back(y);

    FileBin bin;

    cout << endl << endl << "BINARY" << endl << endl;

    bin.WriteToBinFile(person);
    bin.ShowBinFile();

    cout << endl << endl << "BINARY";

    FileTxt txt;

    cout << endl << endl << "TXT" << endl << endl;

    txt.WriteToTxtFile(person);
    txt.ShowTxtFile();

    cout  << endl << endl<< "TXT";

    return 0;
}
