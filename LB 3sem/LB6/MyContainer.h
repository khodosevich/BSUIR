#ifndef LB6_MYCONTAINER_H
#define LB6_MYCONTAINER_H

#include <iostream>
using namespace std;


using namespace std;

template <typename T>
class List {

public:

    List();
    ~List();
    void push_back(T data);
    int getSize();
    T& operator[](const int index);
    void clear();
    bool isEmpty();


private  :

    template<typename T1>
    class Node {

    public:
        Node* next;
        T1 data;
        Node(T1 data = T(), Node* next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };

    int size;
    Node<T>* first;
    Node<T>* last;

};

template <typename T>
List<T>::List() {
    size = 0;
    first = last = nullptr;
}

template <typename T>
void List<T>::push_back(T data) {
    if (first == nullptr) {
        try {
            first = new Node<T>(data);
            last = first;
        }
        catch (bad_alloc& e) {
            cout << e.what() << endl;
        }
    }
    else {

        if (last->next == nullptr) {
            try {
                last->next = new Node<T>(data);
                last = last->next;
            }
            catch (bad_alloc& e) {
                cout<<e.what()<<endl;
            }
        }
    }
    size++;
}


template <typename T>
int List<T>::getSize() {
    return size;
}

template<typename T>
T& List<T>::operator[](const int index) {
    int counter = 0;
    Node<T>* current = this->first;
    while (current != nullptr) {

        if (counter == index) {
            return current->data;
        }
        current = current->next;
        counter++;
    }

    return current->data;
}

template<typename T>
void List<T>::clear() {
    Node<T>* temp;
    while (size) {
        temp = first;
        first = first->next;
        delete temp;
        size--;
    }
}

template<typename T>
bool List<T>::isEmpty() {
    if (this->size == 0)
        return true;
    else
        return false;

}




template<typename T>
List<T>::~List() {
    this->clear();
}




#endif //LB6_MYCONTAINER_H

