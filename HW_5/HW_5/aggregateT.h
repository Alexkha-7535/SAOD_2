#ifndef AGGREGATET_H
#define AGGREGATET_H

#include <iostream>
using namespace std;

template <typename T>
class AggregateT
{
private:
    T m_obj;

public:
    AggregateT() : m_obj() {
        cout << "AggregateT<T>() конструктор шаблона-агрегата" << endl;
    }

    AggregateT(const T& obj) : m_obj(obj) {
        cout << "AggregateT<T>(const T&) конструктор шаблона-агрегата" << endl;
    }

    ~AggregateT() {
        cout << "~AggregateT<T>() деструктор шаблона-агрегата" << endl;
    }
};

#endif