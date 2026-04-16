#include <iostream>
#include "array.h"

using namespace std;

int main()
{
    cout << "=== Вариант 7: Матрица с подсчетом ссылок и view ===" << endl;
    
    // Инициализация данных
    int v[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    // 1. Создание массива 2x3 (используем только первые 6 элементов)
    cout << "\n--- Создание массива 2x3 ---" << endl;
    Array t(2, 3, v);
    cout << "t (2x3):" << endl << t;
    cout << "Количество ссылок на данные: " << (int)t << endl;
    
    // 2. Проверка метода Reshape
    cout << "\n--- Проверка Reshape (3x2) ---" << endl;
    Array view = t.Reshape(3, 2);
    cout << "view (3x2):" << endl << view;
    cout << "Количество ссылок на данные (t): " << (int)t << endl;
    cout << "Количество ссылок на данные (view): " << (int)view << endl;
    
    // 3. Изменение элемента через оригинал
    cout << "\n--- Изменение t.Item(1,1) = 2 * t.Item(1,1) ---" << endl;
    cout << "До изменения: t[1][1] = " << t.Item(1, 1) << endl;
    t.Item(1, 1) = 2 * t.Item(1, 1);
    cout << "После изменения: t[1][1] = " << t.Item(1, 1) << endl;
    
    // 4. Проверка, что изменилось и в оригинале, и во view
    cout << "\n--- Проверка совместного изменения данных ---" << endl;
    cout << "t (2x3):" << endl << t;
    cout << "view (3x2):" << endl << view;
    
    // 5. Проверка, что копия является view, а не независимой матрицей
    cout << "\n--- Проверка копии (конструктор копирования) ---" << endl;
    Array copy = t;  // копия
    cout << "copy (2x3):" << endl << copy;
    cout << "Количество ссылок на данные (t): " << (int)t << endl;
    cout << "Количество ссылок на данные (copy): " << (int)copy << endl;
    
    // Изменение через копию должно отразиться на оригинале
    cout << "\nИзменение copy.Item(0,0) = 100" << endl;
    copy.Item(0, 0) = 100;
    cout << "t после изменения copy:" << endl << t;
    cout << "copy после изменения:" << endl << copy;
    
    // 6. Проверка обработки исключений
    cout << "\n--- Проверка исключений ---" << endl;
    
    // Проверка выхода за границы
    try {
        cout << "Попытка доступа t.Item(10, 10): ";
        t.Item(10, 10);
    } catch (const out_of_range& e) {
        cout << "Исключение: " << e.what() << endl;
    }
    
    // Проверка неверного Reshape
    try {
        cout << "Попытка Reshape(5,5): ";
        Array badView = t.Reshape(5, 5);
    } catch (const invalid_argument& e) {
        cout << "Исключение: " << e.what() << endl;
    }
    
    // 7. Проверка времени жизни объектов
    cout << "\n--- Проверка времени жизни ---" << endl;
    {
        Array local(2, 2, nullptr);
        cout << "Создан локальный массив 2x2, ссылок: " << (int)local << endl;
        cout << "Выход из блока..." << endl;
    }
    cout << "После выхода из блока (локальный массив уничтожен)" << endl;
    
    cout << "\n--- Конец программы ---" << endl;
    return 0;
}