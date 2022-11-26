#ifndef LinkedList_h
#define LinkedList_h
using namespace std;

template<class T>
class Node{
    
private:
    T data;
    
public:
    Node* pNext;
    Node* pPrev;
    Node();
    Node(T data);
    T getData();
    ~Node();
    
};


template<typename T>
Node<T>::Node(){
    pNext = nullptr;
    pPrev = nullptr;
    data = 0;
}

template<typename T>
Node<T>::Node(T data){
    this->data = data;
}


template<typename T>
T Node<T>::getData(){
    return this->data;
}

template <typename T>
Node<T>::~Node(){ }

template <typename T>
class LinkedList{
private:
    T* tail;
    T* head;
    int Size;
    
public:
    LinkedList();
    void push(T *new_node);
    void PrintList();
    T* pop();
    T* getTail();
    T* getHead();
    int size(){return Size;}
    ~LinkedList();
    
};


template <typename T>
LinkedList<T>::LinkedList(){
    this->tail = nullptr;
    this->head = nullptr;
    this->Size = 0;
}

template <typename T>
void LinkedList<T>::push(T *new_node){
   
    new_node->pNext = nullptr;
    new_node->pPrev = nullptr;
    
    if(Size == 0){
        this->head = new_node;
        this->tail = this->head;
        this->Size +=1;
    }else{
        this->head->pPrev = new_node;
        new_node->pNext = this->head;
        this->head = new_node;
        this->Size +=1;
    }
    
}

template <typename T>
T* LinkedList<T>::pop(){
    T *tmp = this->head;
    
    this->head = this->head->pNext;
    this->head->pPrev = nullptr;
    this->Size -=1;
    return tmp;
    
    
}

template <typename T>
void LinkedList<T>::PrintList(){
    
    T *tmp = this->head;
    while(tmp){
        cout << tmp->getData() << "\t";
        tmp = tmp->pNext;
    }
    
}

template<typename T>
T* LinkedList<T>::getHead(){
    return this->head;
}

template<typename T>
T* LinkedList<T>::getTail(){
    return this->tail;
}

template <typename T>
LinkedList<T>::~LinkedList(){
    while(this->head){
        T* next = this->head->pNext;
        delete this->head;
        this->Size -= 1;
        this->head = next;
    }
}



#endif /* LinkedList_h */
