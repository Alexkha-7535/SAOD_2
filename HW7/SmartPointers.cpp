#include <iostream>
#include <memory>

using namespace std;

// 1-3. Класс Test
class Test {
public:
    int Val;
    Test() : Val(0) { cout << "  Test created\n"; }
    ~Test() { cout << "  Test destroyed\n"; }
};

int main() {
    cout << "=== ЧАСТЬ 2: Умные указатели ===\n";

    // 4. Проблема shared_ptr с массивом (раскомментируйте, чтобы увидеть UB/утечку)
    /*
    cout << "\n--- ПРОБЛЕМА: shared_ptr<Test> sp(new Test[3]) ---\n";
    {
        shared_ptr<Test> sp(new Test[3]); // Вызовет delete вместо delete[]
    } // Разрушится только 1 объект, остальные утекут
    */

    // 5. Решение 1: специализация для массива
    cout << "\n--- РЕШЕНИЕ 1: shared_ptr<Test[]> ---\n";
    {
        shared_ptr<Test[]> sp(new Test[3]);
        // 7. Доступ к элементам через get()
        for (int i = 0; i < 3; ++i) sp.get()[i].Val = (i + 1) * 10;
        
        cout << "Values: ";
        for (int i = 0; i < 3; ++i) cout << sp.get()[i].Val << " ";
        cout << "\n";
    } // Корректно вызовется delete[] для всех 3 объектов

    // 6. Решение 2: кастомный удалитель
    cout << "\n--- РЕШЕНИЕ 2: shared_ptr с default_delete<Test[]> ---\n";
    {
        shared_ptr<Test> sp(new Test[3], default_delete<Test[]>());
        for (int i = 0; i < 3; ++i) sp.get()[i].Val = (i + 1) * 20;
        
        cout << "Values: ";
        for (int i = 0; i < 3; ++i) cout << sp.get()[i].Val << " ";
        cout << "\n";
    }

    // 8. unique_ptr для массива
    cout << "\n--- unique_ptr<Test[]> p(new Test[3]) ---\n";
    {
        unique_ptr<Test[]> p(new Test[3]);
        // 8. Оператор [] доступен напрямую
        for (int i = 0; i < 3; ++i) p[i].Val = (i + 1) * 30;
        
        cout << "Values: ";
        for (int i = 0; i < 3; ++i) cout << p[i].Val << " ";
        cout << "\n";

        // 9. Демонстрация reset()
        cout << "---------\n";
        p.reset(new Test[2]); // Старые 3 объекта удаляются, создаются 2 новых
        cout << "---------\n";
    } // Оставшиеся 2 объекта удаляются при выходе из блока

    return 0;
}