#include <iostream>
using namespace std;

int strlenth(char *arr){

    int sizeStr = 0;

    for (int i = 0; i < arr[i] != '\0'; ++i) {
        sizeStr++;
    }

    return sizeStr;
}

int main() {

    char arr[] = "hello world!";

    int size =  strlenth(arr);

    cout << size << endl;

    return 0;
}
