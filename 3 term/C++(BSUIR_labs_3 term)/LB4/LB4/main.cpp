#include <iostream>
#include "Ring.h"
using namespace std;

int main() {

    Queue<int> queue;
    queue.push(5);
    queue.push(10);
    queue.push(11);
    queue.push(12);

    int a =  queue.pop();
    cout << a <<endl<<endl << endl;


    for (int i = 0; i < queue.getSize(); i++) {
        cout << queue[i] << endl;
    }

    cout << endl << queue.getFirst()<<endl;

}
