#include <iostream>
#include <memory>

/*
 auto_ptr
 unique_ptr
 shared_ptr
 */


int main() {

    
    
    int SIZE;
    std::cout << "Enter number: ";
    std::cin >> SIZE;
    
    std::shared_ptr<int[]> ptr(new int[SIZE]);
    
    for (int i = 0; i < SIZE; i++) {
        ptr[i] = rand() % 15;
        std::cout << ptr[i] << "\t";
    }
    
    std::cout <<std::endl;
    
    return 0;
}
