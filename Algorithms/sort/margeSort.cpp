#include <iostream>
#include <vector>

using namespace std;

void marge(vector<int> &vec, vector<int> &tmp, int start, int center, int end)
{
    int left = start, right = center;
    int cur = left, leftEnd = center - 1;
    while (left <= leftEnd && right <= end)
    {
        if (vec[left] >= vec[right])
        {
            tmp[cur++] = std::move(vec[left++]);
        }
        else
        {
            tmp[cur++] = std::move(vec[right++]);
        }
    }
    while (left <= leftEnd)
    {
        tmp[cur++] = std::move(vec[left++]);
    }
    while (right <= end)
    {
        tmp[cur++] = std::move(vec[right++]);
    }

    for (int i = start; i <= end; ++i)
    {
        vec[i] = tmp[i];
    }
}

void margeSort(vector<int> &vec, vector<int> &tmp, int start, int end)
{
    if (start < end)
    {
        int center = start + (end - start) * 0.5;
        margeSort(vec, tmp, start, center);
        margeSort(vec, tmp, center + 1, end);
        marge(vec, tmp, start, center + 1, end);
    }
}
void margeSort(vector<int> &vec)
{
    vector<int> tmpArray(vec.size(), 0);
    margeSort(vec, tmpArray, 0, vec.size() - 1);
}

int main()
{
    vector<int> vec = {5, 8, 6, 4, 37, 45, 47, 566, 41, 23};
    margeSort(vec);
    for (auto i : vec)
    {
        cout << i << endl;
    }
    return 0;
}
