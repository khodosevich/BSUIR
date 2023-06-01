#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
using namespace std;


template<class T>
void PrintList(const list<T> &lst){

    for(auto i = lst.begin(); i != lst.end(); i++){
        cout << *i << " ";
    }

}

int main() {

    list<int> list1;

    for (int i = 0; i < 5; ++i) {
        list1.push_front(i);
    }

    int x;

    while (1){
        cout<< endl << "1 - push_front" << endl;
        cout << "2 - push_back" << endl;
        cout << "3 - pop_front" << endl;
        cout << "4 - pop_back" << endl;
        cout << "5 - напечать лист" << endl;
        cout << "6 - size" << endl;
        cout << "7 - reverse" << endl;
        cout << "8 - remove" << endl;
        cout << "9 - insert" << endl;
        cout << "10 - erase" << endl;
        cout << "11 - clear" << endl;
        cout << "0 - конец" << endl;

        cout << "->";
        cin >> x;
        cout << endl << endl;

        switch (x) {

            case 1: {
                int x;
                cout << "Введите элемент:";
                cin >> x;
                list1.push_front(x);
                break;
            }

            case 2: {
                int x;
                cout << "Введите элемент:";
                cin >> x;
                list1.push_back(x);
                break;
            }

            case 3: {
               list1.pop_front();
                break;
            }


            case 4: {
               list1.pop_back();
                break;
            }
            case 5: {
                PrintList(list1);
                break;
            }

            case 6:{
              cout<<"Size: " << list1.size() << endl;
                break;
            }

            case 7:{
                list1.reverse();
                PrintList(list1);
                break;
            }

            case 8:{
                int x;
                cout << "Введите элемент для удаления:";
                cin >> x;
                list1.remove(x);
                break;
            }

            case 9:{
                int x;
                cout << "Введите число для смещения:";
                cin >> x;
                int y;
                cout << "Введите число для вставки:";
                cin >> y;

                auto iter = list1.begin();

                advance(iter,x);
                list1.insert(iter,y);
                PrintList(list1);
                break;
            }

            case 10:{
                int x;
                cout << "Введите число для смещения:";
                cin >> x;
                cout << "Erase" << endl;
                auto iter1 = list1.begin();
                advance(iter1,x);
                list1.erase(iter1);
                PrintList(list1);
                break;
            }
            case 11:{
                list1.clear();
                cout << "Size: " << list1.size()<< endl;
                break;
            }

            case 0:{
                return 0;
            }


        }


    }


//    list1.push_back(555);
//    list1.push_front(999);
//
//    cout << list1.size() << endl;
//    PrintList(list1);
//
//    cout << endl << endl;
//
//    cout << "pop_back and pop_front"<<endl;
//    list1.pop_back();
//    list1.pop_front();
//
//    cout << "size:"<<endl;
//    cout << list1.size() << endl;
//    PrintList(list1);
//
//    cout << endl << endl;
//
//    cout << "reverse"<<endl;
//    list1.reverse();
//    PrintList(list1);
//
//
//    cout << endl << endl;
//
//    cout << "Insert" << endl;
//    auto iter = list1.begin();
//
//    advance(iter,3);
//    list1.insert(iter,66);
//    PrintList(list1);
//
//    cout << endl << endl;
//
//    cout << "Erase" << endl;
//    auto iter1 = list1.begin();
//
//    advance(iter1,3);
//    list1.erase(iter1);
//    PrintList(list1);
//
//    cout << endl << endl;
//
//
//    cout << "Remove"<<endl;
//    list1.remove(9);
//    PrintList(list1);
//
//    cout << endl << endl;
//
//
//    cout << "Assign"<<endl;
//    list1.assign(3,99999);
//    PrintList(list1);
//
//    cout << endl << endl;
//    cout << "clear"<<endl;
//    list1.clear();
//    cout << "size: "<<list1.size() << endl;


    return 0;
}
