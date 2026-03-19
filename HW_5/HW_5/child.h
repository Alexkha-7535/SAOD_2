#ifndef CHILD_H
#define CHILD_H

#include "Test.h"

class Child : public Test
{
public:
    Child() : Test() {
        cout << "Child() конструктор потомка. ID = " << GetId() << endl;
    }

    Child(int id) : Test(id) {
        cout << "Child(int) конструктор потомка с параметром. ID = " << GetId() << endl;
    }

    ~Child() {
        cout << "~Child() деструктор потомка. ID = " << GetId() << endl;
    }
};

#endif