#include <iostream>
#include <fstream>
using namespace std;


class Point{

public:

    Point(){
    x = y = z = 0;
    }

    Point(int x,int y,int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Print(){
        cout << "X= "<< x << "\tY= " << y  << "\tZ= "<< z << endl;
    }


    int x;
    int y;
    int z;
};


int main() {



//    Point a(77,88, 99);
//
//    a.Print();
//
//    string path = "Text.txt";
//
//
//    ofstream obj;
//
//    obj.open(path,ofstream::app);
//
//    if (!obj.is_open()){
//        cout << "Error" ;
//    }else{
//        cout << "good" ;
//        obj.write((char*)&a,sizeof(Point) );
//    }
//
//    obj.close();

    string path = "Text.txt";

    ifstream fin;


    fin.open(path);

    if(!fin.is_open()){
        cout << "error";
    }
    else{
       cout << "Good" << endl;
       Point pnt;

       while(fin.read((char*)&pnt,sizeof (Point)))
       {
           pnt.Print();
       }

    }

    fin.close();



    return 0;
}
