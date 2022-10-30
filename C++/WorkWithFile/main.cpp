#include <iostream>
#include <fstream>

using namespace std;

int main() {


    string path = "MyFlie.txt";

    ofstream fout;
    fout.open(path , ofstream::app);

    if (!fout.is_open()){
        cout << "Error" << endl;
    }
    else{
        cout << "Enter number:" << endl;
        int a;
        cin >> a;
        fout << "\n";
        fout << a;
    }

    fout.close();

    return 0;
}
