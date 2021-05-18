#ifndef VECTORNODE_H
#define VECTORNODE_H
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
struct VectorNode
{
    T data;
    int count;


    VectorNode();
    VectorNode(T d, int c=1);
    VectorNode<T>& operator=(const VectorNode<T> &other);
    ~VectorNode();

    template<typename U>
    friend
    ostream& operator<<(ostream& out, VectorNode<U> &n);

    template<typename U>
    friend
    istream& operator>>(istream& in, VectorNode<U> &n);

    template<typename U>
    friend
    bool operator<(VectorNode<U> a, VectorNode<U> b);

    template<typename U>
    friend
    bool operator>(VectorNode<U> a, VectorNode<U> b);


    template<typename U>
    friend
    bool operator==(VectorNode<U> a, VectorNode<U> b);


    template<typename U>
    friend
    bool operator<=(VectorNode<U> a, VectorNode<U> b);


    template<typename U>
    friend
    bool operator>=(VectorNode<U> a, VectorNode<U> b);


    template<typename U>
    friend
    bool operator!=(VectorNode<U> a, VectorNode<U> b);
};

template<typename T>
VectorNode<T>::VectorNode()
{
    count = 0;
}

template<typename T>
VectorNode<T>::VectorNode(T d, int c)
{
    data=d;
    count=c;
}

template<typename T>
VectorNode<T>& VectorNode<T>::operator =(const VectorNode<T> &other)
{
    if(this != &other)
    {
        data = other.data;
        count = other.count;
    }
    return *this;
}

template<typename T>
VectorNode<T>::~VectorNode()
{
    count=0;
}

template<typename U>
ostream& operator<<(ostream& out, VectorNode<U> &n)
{
    out<<n.data<<"["<<n.count<<"] ";
    return out;
}

template<typename U>
istream& operator>>(istream& in, VectorNode<U> &n)
{
    char junk;
    U data;
    int count;
    if(in>>data>>junk>>count>>junk)
    {
        n.data = data;
        n.count = count;
    }
    return in;
}

template<typename U>
bool operator<(VectorNode<U> a, VectorNode<U> b)
{
    return a.data < b.data;
}

template<typename U>
bool operator>(VectorNode<U> a, VectorNode<U> b)
{
    return a.data > b.data;
}

template<typename U>
bool operator==(VectorNode<U> a, VectorNode<U> b)
{
    return a.data == b.data;
}


template<typename U>
bool operator<=(VectorNode<U> a, VectorNode<U> b)
{
    return a.data <= b.data;
}


template<typename U>
bool operator>=(VectorNode<U> a, VectorNode<U> b)
{
    return a.data >= b.data;
}


template<typename U>
bool operator!=(VectorNode<U> a, VectorNode<U> b)
{
    return a.data != b.data;
}


#endif // VECTORNODE_H
