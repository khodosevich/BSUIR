#include <iostream>
#include <string>
using namespace std;

int main() {
//конкатенация язык си
    char arr[] = "hello";
    char arr1[] = "world";
    char arr2[] = "!!!";
    strcat(arr,arr1);

    cout << arr << endl;

    strcat(arr,arr2);

    cout << arr << endl;

//конкатенация язык си++
    string str1 = "hello";
    string str2 = "world";

    string str3;

    str3 = str1 + " " + str2;

    cout << str3 << endl;
    return 0;
}
