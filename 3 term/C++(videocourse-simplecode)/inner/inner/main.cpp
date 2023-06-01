#include <iostream>
using namespace std;

class Img{
    
public:
    void GetImgInfo(){
        for(int i = 0; i < 5; i++){
            cout << pixels[i].GetPixel() << endl;
        }
    }
    
private:
    //inner class
    class Pixel{
    private:
        int r;
        int g;
        int b;
        
    public:
        Pixel(int r,int g,int b){
            this->r = r;
            this->g = g;
            this->b = b;
        }
        
        string GetPixel(){
            return "R = " + to_string (r) + "\tG = " + to_string(g) + "\tB = " + to_string(b);
        }
    };
    
   
    Pixel pixels[5]{
        Pixel (1,2,3),
        Pixel (0,-2,322),
        Pixel (100,44,3),
        Pixel (12,55,3),
        Pixel (88,2,10)
    };
    
    
};


int main() {
   
    Img a;
    
    a.GetImgInfo();
    
    return 0;
}
