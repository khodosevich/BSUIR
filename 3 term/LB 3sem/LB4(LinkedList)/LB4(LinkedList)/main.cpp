#include <iostream>
#include "LinkedList.h"

int main()
{
    
    int a;
    cout << "int - 1 , str - 2: " ;
    cin >> a;
   
    cout << endl << endl;
    
        switch (a) {
            case 1:{
                CreateListOfInts();
                break;
            }
        
            case 2:{
                CreateListOfStrings();
                break;
            }
       
            default:
                break;
            }
    
  return 0;
}
