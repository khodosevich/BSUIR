#include <iostream>
#include "LinkedList.h"
using namespace std;

int main() {
    
    int x = 5;
    char y = 'h';
  
    LinkedList<Node<char>> list;
    
    while(x != 0){
       
        list.push(new Node<char> (y));
        x--;
    }
    
    list.PrintList();
    cout << endl;
    

    
    cout << list.getHead()->getData() << endl;
    
    cout << list.getTail()->getData() << endl;
    
    cout << list.size()<< endl;
    
    return 0;
}
