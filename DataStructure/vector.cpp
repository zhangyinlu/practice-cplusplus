#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class vector
{
private:
    void *mData = nullptr;
    long mSize = 0;
    long mCapacity = 8;
    int mItemSize;
    int (*mEqualFunc)(const void *, const void *, size_t);

    void resize(long newCapacity)
    {
        void *tmpData = realloc(mData, newCapacity * mItemSize);
        if (NULL == tmpData)
        {
            cout << "realloc failed!!" << endl;
            exit(-1);
        }
        mData = tmpData;
        mCapacity = newCapacity;
    }

public:
    vector(int nIterSize, int (*equalFunc)(const void *, const void *, size_t) = memcmp)
        : mItemSize(nIterSize), mEqualFunc(equalFunc)
    {
        mData = calloc(mCapacity, mItemSize);
    }
    ~vector()
    {
        if (nullptr != mData)
        {
            free(mData);
            mData = nullptr;
        }
    }

    long size() { return mSize; }
    long capacity() { return mCapacity; }
    bool empty() { return mSize == 0; }
    void *at(long index)
    {
        if (mSize <= index || index < 0)
        {
            return nullptr;
        }
        return (char *)mData + index * mItemSize;
    }

    void push(void *item)
    {
        if (mSize + 1 > mCapacity)
        {
            resize(mCapacity * 2);
        }
        memcpy((char *)mData + mSize * mItemSize, item, mItemSize);
        mSize += 1;
    }

    void erase(long index)
    {
        if (index >= mSize || index < 0)
        {
            return;
        }
        memmove(((char *)mData + index * mItemSize), ((char *)mData + (index + 1) * mItemSize), (mSize - index) * mItemSize);
        mSize -= 1;
        if (mCapacity >= mSize * 4)
        {
            resize(mCapacity >> 1);
        }
    }

    long find(void *item)
    {
        for (long i = 0; i < size(); ++i)
        {
            if (0 == mEqualFunc((char *)mData + i * mItemSize, item, mItemSize))
            {
                return i;
            }
        }
        return -1;
    }

    long remove(void *item)
    {
        long index = find(item);
        erase(index);
        return index;
    }
};

int equalDouble(const void *n1, const void *n2, size_t size)
{
    if (*((double *)n1) - *((double *)n2) > 1e-6)
    {
        return 1;
    }
    else if (*((double *)n2) - *((double *)n1) > 1e-6)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    vector vecDouble(sizeof(double), equalDouble);

    for (int i = 0; i < 10000; ++i)
    {
        double tmp = i * 0.01;
        vecDouble.push(&tmp);
    }
    cout << "size:" << vecDouble.size() << "\tcapacity:" << vecDouble.capacity() << endl;
    for (int i = 0; i < vecDouble.size(); ++i)
    {
        double tmp = *((double *)vecDouble.at(i));
        if (abs(i * 0.01 - tmp) > 1e-6)
        {
            cout << "error at:" << i << "\t" << tmp << endl;
        }
    }
    for (int i = 0; i < 9980; ++i)
    {
        vecDouble.erase(rand() % vecDouble.size());
    }
    cout << "size:" << vecDouble.size() << "\tcapacity:" << vecDouble.capacity() << endl;

    cout << "index:" << vecDouble.find(vecDouble.at(15)) << endl;

    for (int i = 0; i < vecDouble.size(); ++i)
    {
        cout << *(double *)vecDouble.at(i) << "\t";
    }
    cout << endl;

    cout << "item index:" << vecDouble.remove(vecDouble.at(15)) << endl;

    for (int i = 0; i < vecDouble.size(); ++i)
    {
        cout << *(double *)vecDouble.at(i) << "\t";
    }
    cout << endl;

    cout << "size:" << vecDouble.size() << "\tcapacity:" << vecDouble.capacity() << endl;

    return 0;
}
