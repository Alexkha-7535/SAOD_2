#include <iostream>
#include "Test.h"
#include "Child.h"
#include "Aggregate.h"
#include "AggregateT.h"
using namespace std;

// Глобальный объект
Test globalTest(1000);

// Функция для демонстрации передачи по значению
void foo(Test t) {
    cout << "foo is running. Получен объект с ID = " << t.GetId() << endl;
}

int main()
{
    cout << "=== Задание 5: Время жизни объектов ===" << endl;
    cout << "main() начал работу" << endl;

    // Шаг 1-2: Локальный объект
    cout << "\n1. Локальный объект:" << endl;
    Test localTest;
    cout << "До завершения блока" << endl;

    // Шаг 3: Статическое поле уже работает (счетчик)
    cout << "\n2. Еще один локальный объект:" << endl;
    Test anotherTest(200);

    // Шаг 5-6: Динамический объект
    cout << "\n3. Динамический объект:" << endl;
    Test* p = new Test(300);
    cout << "Динамический объект создан" << endl;
    delete p;  // без delete деструктор не вызовется
    cout << "Динамический объект удален" << endl;

    // Шаг 7: Динамический массив
    cout << "\n4. Динамический массив:" << endl;
    Test* arr = new Test[3];
    cout << "Массив создан" << endl;
    delete[] arr;
    cout << "Массив удален" << endl;

    // Шаг 8-9: Передача по значению
    cout << "\n5. Передача по значению (конструктор копирования):" << endl;
    Test copyTest(400);
    cout << "До вызова foo" << endl;
    foo(copyTest);
    cout << "После вызова foo" << endl;

    // Шаг 10: Наследование
    cout << "\n6. Наследование (порядок создания предка и потомка):" << endl;
    Child childObj(500);

    // Шаг 11: Агрегация
    cout << "\n7. Агрегация (порядок создания полей и агрегата):" << endl;
    Aggregate aggObj;

    // Шаг 12: Шаблон-агрегат
    cout << "\n8. Шаблон-агрегат с Test:" << endl;
    AggregateT<Test> aggT1(Test(600));

    cout << "\n9. Шаблон-агрегат с Child:" << endl;
    AggregateT<Child> aggT2(Child(700));

    cout << "\nmain() завершает работу" << endl;
    return 0;
}