#pragma once

#include <algorithm>

template <typename Object>
class Vector
{
public:
    explicit Vector(int initSize = 0)
        : theSize(initSize), theCapacity(theSize + SPACE_CAPACITY)
    {
        objects = new Object[theCapacity];
    }
    Vector(const Vector &rhs)
        : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(nullptr)
    {
        objects = new Object[theCapacity];
        for (int i = 0; i < theSize; ++i)
        {
            objects[i] = rhs.objects[i];
        }
    }
    Vector &operator=(const Vector &rhs)
    {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    Vector(Vector &&rhs)
        : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(rhs.objects)
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
    Vector &operator=(Vector &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);
        return *this;
    }
    ~Vector()
    {
        if (nullptr != objects)
        {
            delete[] objects;
        }
    }

    void reserve(int newCapacity)
    {
        if (newCapacity < theCapacity)
        {
            return;
        }
        Object *newArray = new Object[newCapacity];
        for (int i = 0; i < theSize; ++i)
        {
            newArray[i] = std::move(objects[i]);
        }
        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;
    }
    void resize(int newSize)
    {
        if (newSize > theCapacity)
        {
            reserve(newSize);
        }
        theSize = newSize;
    }

    Object &operator[](int index) { return objects[index]; }
    const Object &operator[](int index) const { return objects[index]; }

    int size() const { return theSize; }
    int capacity() const { return theCapacity; }
    bool empty() const { return size() == 0; }

    void push_back(const Object &x)
    {
        if (theSize == theCapacity)
        {
            reserve(2 * theCapacity + 1);
        }
        objects[theSize++] = x;
    }
    void push_back(Object &&x)
    {
        if (theSize == theCapacity)
        {
            reserve(2 * theCapacity + 1);
        }
        objects[theSize++] == std::move(x);
    }
    void pop_back() { --theSize; }

    Object &back() { return objects[theSize - 1]; }
    const Object &back() const { return objects[theSize - 1]; }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin() { return &objects[0]; }
    const_iterator begin() const { return &objects[0]; }

    iterator end() { return &objects[size()]; }
    const_iterator end() const { return &objects[size()]; }

private:
    static constexpr int SPACE_CAPACITY = 16;

    int theSize = 0;
    int theCapacity = 0;
    Object *objects = nullptr;
};
