#ifndef AGGREGATE_H
#define AGGREGATE_H

#include "Test.h"

class Aggregate
{
private:
    Test m_objTest;

public:
    Aggregate() : m_objTest(999) {
        cout << "Aggregate() конструктор агрегата" << endl;
    }

    ~Aggregate() {
        cout << "~Aggregate() деструктор агрегата" << endl;
    }
};

#endif