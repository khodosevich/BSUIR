#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
   
    int *arr;
 
    arr = new int[5];
    
    cout << "Enter 5 number: ";
    
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }
    
    int min = arr[0], max = arr[0];
   
    
    for (int i = 0 ; i < 5; i++) {
        if(arr[i] < min){
            min = arr[i];
           
        }
    }
    
    for (int i = 0 ; i < 5; i++) {
        if(arr[i] > max){
            max = arr[i];
           
        }
    }
    
    cout <<"Min value: "<<min;
    printf("\n");
    cout <<"Max value: "<<max;
    printf("\n");
    delete [] arr;
    
    return 0;
}
