#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Str.h"
using namespace std;

// Функция для демонстрации передачи по значению
void Test(Str s) {
    cout << "Test function is running" << endl;
}

int main()
{
    cout << "=== Задание 4: Класс Str ===" << endl;

    // Шаг 1-3: Создание и вывод
    cout << "\n1. Создание и вывод объекта:" << endl;
    Str s1 = "Hello";
    cout << "s1 = " << s1 << endl;
    cout << "Длина s1 = " << strlen(s1) << endl;

    // Шаг 4-5: Передача по значению и конструктор копирования
    cout << "\n2. Передача по значению (нужен конструктор копирования):" << endl;
    cout << "До вызова Test" << endl;
    Test(s1);
    cout << "После вызова Test" << endl;

    // Шаг 6-7: Присваивание
    cout << "\n3. Оператор присваивания:" << endl;
    {
        Str t;
        t = s1;
        cout << "t = " << t << endl;
    }

    // Шаг 8: Оператор +=
    cout << "\n4. Оператор +=:" << endl;
    Str s2 = "World";
    cout << "s2 = " << s2 << endl;
    s2 += "!";
    cout << "s2 += \"!\" = " << s2 << endl;

    // Можно добавлять и объекты Str благодаря преобразованию
    s2 += Str("!!!");  // неявное преобразование Str -> const char*
    cout << "s2 += Str(\"!!!\") = " << s2 << endl;

    // Шаг 9: Оператор +
    cout << "\n5. Оператор +:" << endl;
    Str s3 = "Hello";
    Str s4 = s3 + " World";
    cout << "s3 = " << s3 << endl;
    cout << "s4 = s3 + \" World\" = " << s4 << endl;

    // Демонстрация цепочки присваиваний
    cout << "\n6. Цепочка присваиваний:" << endl;
    Str a = "A", b = "B", c = "C";
    a = b = c;
    cout << "a = b = c: a = " << a << ", b = " << b << ", c = " << c << endl;

    return 0;
}