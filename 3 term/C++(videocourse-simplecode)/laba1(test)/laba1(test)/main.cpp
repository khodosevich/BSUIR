#include <iostream>
using namespace std;

class Array
{
private:
    int *arr;
    int size{};
public:
    Array();
    Array(int s);
    ~Array();
    void FillArr();
    void PrintArr();
    void FindMax();
    void FindMin();
    void SwapMinMax(int min,int max);
};

Array::Array()
{

    cout <<"Введите количество элементов:";
    cin >> size;

    arr = new int[size];

}
Array::Array(int s)
{
    if(s > 0)
    {
        size = s;
        arr = new int[size];

    }else cout << "Количество элементов должно быть положительно!";
}

Array::~Array()
{
    delete []arr;
}

void Array::FillArr()
{

    for(int i = 0; i < size; i++){
        cout << "Введите элемент["<<i<<"]:";
        cin >> arr[i];
    }

}
void Array::PrintArr()
{
    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";

}
void Array::FindMin()
{
    int min = arr[0],index_min;
    for (int i = 0; i < size; ++i)
    {
        if(arr[i] < min)
        {
            min = arr[i];
            index_min = i;
        }
    }

    cout <<"Min number " << min;

}
void Array::FindMax()
{
    int max = arr[0],index_max;
    for(int i = 0; i < size; i++)
    {
        if( arr[i] > max)
        {
            max = arr[i];
            index_max = i;
        }

    }
    cout <<"Max number " << max;

}

void Array::SwapMinMax(int min,int max)
{

}




int main() {


    Array arr(6);
    Array arr1(5);
    arr.FillArr();
    arr1.FillArr();
    arr.PrintArr();
    cout << "\n";
    arr.FindMin();
    cout << "\n";
    arr1.FindMax();

    return 0;
}
