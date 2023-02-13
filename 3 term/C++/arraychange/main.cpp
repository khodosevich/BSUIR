#include <iostream>
using namespace std;


int main() {

    int size = 5;

    int *arr = new int[5];

    int *arr2 = new int[5];

    for (int i = 0; i < 5; ++i) {
        cin >> arr2[i];
    }

    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << "\t";
    }

    cout << "\n";

    for (int i = 0; i < 5; ++i) {
       arr[i] = arr2[i];
    }

    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << "\t";
    }

    delete []arr;
    delete []arr2;

    return 0;
}
