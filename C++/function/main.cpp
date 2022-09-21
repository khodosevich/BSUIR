#include <iostream>
using namespace std;

void foo()
{
    cout << "I am function! Hello world)" << endl;
}

int sum(int x, int y)
{
    return x + y;
}

int main() {

    for (int i = 0; i < 5; ++i)
    {
        foo();
    }

    cout << sum(6,6) << endl;

    return 0;
}
