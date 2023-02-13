#ifndef Ring_h
#define Ring_h
#include<iostream>
using namespace std;

template <typename T>
class Queue {

public:
    Queue();
    ~Queue();
    void push(T data);
    T pop();
    int getSize();
    T& operator[](const int index);

    void clear();
    bool isEmpty();
    T getFirst();

private:
    template <typename T1>
    class Node {
    public:

        T1 data;
        Node<T1>* next;
        Node(T1 data = T1(), Node<T1>* next = nullptr) {
            this->data = data;
            this->next = next;
        }

    };

    Node<T>* first;
    Node<T>* last;
    int size;
};

template<typename T>
int Queue<T>::getSize() {
    return size;
}

template <typename T>
Queue<T>::Queue() {
    size = 0;
    first = last = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
    this->clear();
}

template<typename T>
void Queue<T>::push(T data) {
    if (first == nullptr) {
        first = new Node<T>(data);
        last = first;
    }
    else {

        if (last->next == nullptr) {
            last->next = new Node<T>(data);
            last = last->next;
        }
    }
    size++;
}

template<typename T>

T Queue<T>::pop() {
    if (first == nullptr) {
        cout << "Queue is empty!" << endl;
        return 0;
    }
    else {
        Node<T>* item = first;
        T element = item->data;
        Node<T>* current = item->next;
        first = current;
        delete item;
        if (current == nullptr) {
            last == nullptr;
        }
        size--;
        return element;
    }
}

template <typename T>
T& Queue<T>::operator[](const int index) {
    int counter = 0;
    Node<T>* current = first;

    while (current != nullptr) {
        if (counter == index){
            return current->data;
        }

        current = current->next;
        counter++;
    }

    return current->data;
}

template<typename T>
void Queue<T>::clear() {
    Node<T>* temp;
    while (size) {
        temp = first;
        first = first->next;
        delete temp;
        size--;
    }
}

template<typename T>
bool Queue<T>::isEmpty() {
    if (this->size == 0)
        return true;
    else
        return false;
}

template<typename T>
T Queue<T>::getFirst() {
    if (this->isEmpty()) {
        cout << "Queue is empty" << endl;
    }
    else
        return first->data;
    
    return first->data;
}

#endif /* Ring_h */
