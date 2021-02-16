#pragma once

#include <algorithm>

template <typename Object>
class List
{
private:
    struct Node
    {
        Object data;
        Node *prev;
        Node *next;
        Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr)
            : data{d}, prev{p}, next{n} { ; }
        Node(Object &&d = Object{}, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} { ; }
    };

public:
    class const_iterator
    {
    public:
        const_iterator() : current{nullptr}
        {
        }
        const Object &operator*() const
        {
            return current->data;
        }
        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }
        bool operator!=(const const_iterator &rhs) const
        {
            return !((*this) == rhs);
        }

    protected:
        Node *current = nullptr;
        const_iterator(Node *p) : current{p}
        {
        }

        friend class List<Object>;
    };
    class iterator : public const_iterator
    {
    public:
        iterator() {}

        Object &operator*()
        {
            return current->data;
        }
        const Object &operator*() const
        {
            return const_iterator::operator*();
        }

        iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }
    protected:
        iterator(Node *p) : const_iterator{p}
        {
        }
        friend class List<Object>;
    };

public:
    List()
    {
    }
    List(const List &rhs)
    {
    }
    List &operator=(const List &rhs)
    {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    List(List &&rhs)
        : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    List &operator=(List &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }
    ~List()
    {
        //TODO:clear mList
    }


private:
    int theSize = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
};
