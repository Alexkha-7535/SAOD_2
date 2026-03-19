#ifndef TEST_H
#define TEST_H

#include <iostream>
using namespace std;

class Test
{
private:
    int m_id;
    static int nCount;  // статическое поле - счетчик объектов

public:
    // Конструктор по умолчанию
    Test() {
        m_id = ++nCount;
        cout << "Test() конструктор по умолчанию. ID = " << m_id
            << ", Всего объектов: " << nCount << endl;
    }

    // Конструктор с параметром
    Test(int id) {
        m_id = id;
        nCount++;
        cout << "Test(int) конструктор с параметром. ID = " << m_id
            << ", Всего объектов: " << nCount << endl;
    }

    // Конструктор копирования
    Test(const Test& other) {
        m_id = other.m_id + 100;  // чтобы отличать копии
        nCount++;
        cout << "Test(const Test&) конструктор копирования. ID = " << m_id
            << " (копия " << other.m_id << "), Всего объектов: " << nCount << endl;
    }

    // Деструктор
    ~Test() {
        cout << "~Test() деструктор. ID = " << m_id
            << ", Осталось объектов: " << --nCount << endl;
    }

    int GetId() const { return m_id; }
};

#endif
