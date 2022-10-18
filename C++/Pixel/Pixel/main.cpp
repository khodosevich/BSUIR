#include <iostream>
using namespace::std;

class Pixel{
private:
    int r;
    int g;
    int b;
public:
    Pixel(){
        r = g = b = 0;
    }
    
    Pixel(int r,int g,int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    string GetPixel(){
        return "Pixel: R = " + to_string(r) +  "\tG = " + to_string(g) +  "\tB = " + to_string(b);
    }
    
};

int main() {
    
    int len = 5;
    Pixel *arr = new Pixel [len];
    
    cout << arr[0].GetPixel() << endl;
    arr[0] = Pixel(12,13,14);
    cout << arr[0].GetPixel() << endl;
    
    delete []arr;
    
    
    return 0;
}
