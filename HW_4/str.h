#ifndef STR_H
#define STR_H

#include <iostream>
#include <cstring>
using namespace std;

class Str
{
private:
    char* m_pszText;  // динамический массив символов

public:
    // Конструктор по умолчанию
    Str() {
        m_pszText = new char[1];
        m_pszText[0] = '\0';
        cout << "Str() конструктор по умолчанию" << endl;
    }

    // Конструктор инициализации C-строкой
    Str(const char* sz) {
        int len = strlen(sz);
        m_pszText = new char[len + 1];
        strcpy(m_pszText, sz);
        cout << "Str(const char*) конструктор инициализации: " << sz << endl;
    }

    // Конструктор копирования
    Str(const Str& s) {
        int len = strlen(s.m_pszText);
        m_pszText = new char[len + 1];
        strcpy(m_pszText, s.m_pszText);
        cout << "Str(const Str&) конструктор копирования: " << m_pszText << endl;
    }

    // Деструктор
    ~Str() {
        cout << "~Str() деструктор: " << m_pszText << endl;
        delete[] m_pszText;
    }

    // Оператор присваивания
    Str& operator=(const Str& s) {
        cout << "operator=(const Str&) для: " << m_pszText << " = " << s.m_pszText << endl;
        if (this != &s) {  // защита от самоприсваивания
            delete[] m_pszText;
            int len = strlen(s.m_pszText);
            m_pszText = new char[len + 1];
            strcpy(m_pszText, s.m_pszText);
        }
        return *this;
    }

    // Оператор преобразования к const char*
    operator const char* () const {
        return m_pszText;
    }

    // Оператор += (присоединение C-строки)
    Str& operator+=(const char* sz) {
        cout << "operator+=(const char*) для: " << m_pszText << " + " << sz << endl;
        int newLen = strlen(m_pszText) + strlen(sz);
        char* temp = new char[newLen + 1];
        strcpy(temp, m_pszText);
        strcat(temp, sz);
        delete[] m_pszText;
        m_pszText = temp;
        return *this;
    }

    // Оператор + (конкатенация с C-строкой)
    Str operator+(const char* sz) const {
        cout << "operator+(const char*) const: " << m_pszText << " + " << sz << endl;
        int newLen = strlen(m_pszText) + strlen(sz);
        char* temp = new char[newLen + 1];
        strcpy(temp, m_pszText);
        strcat(temp, sz);
        Str result(temp);
        delete[] temp;
        return result;
    }

    // Дружественная функция для вывода
    friend ostream& operator<<(ostream& os, const Str& s) {
        os << s.m_pszText;
        return os;
    }
};

#endif