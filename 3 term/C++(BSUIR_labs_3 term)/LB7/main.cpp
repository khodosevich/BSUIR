#include <iostream>
#include "List.h"
using namespace std;


int main() {

    List<int> list;

    for (int i = 0; i < 10; ++i) {
        list.push(i);
    }


    int x;

    while (true) {

        cout<< endl << "1 - пройтись по списку с головы" << endl;
        cout << "2 - вывести голову" << endl;
        cout << "3 - вывести хвост" << endl;
        cout << "4 - пройтись с хвоста" << endl;
        cout << "5 - вывести n элемент" << endl;
        cout << "6 - push" << endl;
        cout << "7 - pop" << endl;
        cout << "8 - size" << endl;
        cout << "0 - конец" << endl;

        cin >> x;

        switch (x) {

            case 1: {
                for (Iterator<int> x = list.begin(); x != list.end(); ++x) {
                    cout << *x << " ";
                }
                break;
            }

            case 2: {
                Iterator<int> x = list.begin();
                cout << *x << endl;
                break;
            }

            case 3: {
                Iterator<int> y = list.end();
                cout << *y << endl;
                break;
            }


            case 4: {
                for (Iterator<int> x = list.end(); x != list.begin(); --x) {
                    cout << *x << " ";
                }
                break;
            }
            case 5: {
                int n;
                cout << "Введите число n: ";
                cin >> n;
                Iterator<int> x = list.begin();
                x = x + n;
                cout << "Нужный элемент: " << *x << endl;
                break;
            }

            case 6:{
                int a;
                cout << "Введите число:" << endl;
                cin >> a;
                list.push(a);
                break;
            }

            case 7:{
                list.pop();
                cout << "Pop выполнился" << endl;
                break;
            }

            case 8:{
                cout << "Size = " << list.size()<< endl;
                break;
            }
            case 0:{
                return 0;
            }

        }
    }

}
