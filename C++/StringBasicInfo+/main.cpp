#include <iostream>
using namespace std;


int main() {
    // hello world\0
    char *string = "hello world";

    cout << string << endl;

    int size;
    size = strlen(string);
    cout << size << endl;

    for (int i = 0; i < size; ++i) {
        cout << string[i] ;
    }
    cout << endl;

    char *strArr[] = {"hello" , "world" , "test"};

    for (int i = 0; i < 3; ++i) {
        cout << strArr[i] << endl;
    }
    return 0;
}
