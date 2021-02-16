#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
    Vector<int> vec;
    for (int i = 0; i < 100; ++i)
    {
        vec.push_back(i);
    }
    for (auto n : vec)
    {
        cout << n << endl;
    }
}
