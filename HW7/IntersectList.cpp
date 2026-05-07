#include <iostream>
#include <list>
#include <string>
#include <chrono>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

using namespace std;

// 3.c. Функция генерации случайных строк (исправлен typo из задания)
string getRandom(int len) {
    static const char ab[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    static const int aLen = sizeof(ab) - 1;
    string s(len, ' ');
    for (int i = 0; i < len; ++i)
        s[i] = ab[rand() % aLen];
    return s;
}

// 3. Подготовка данных
void prepareData(int N, list<string>& list1, list<string>& list2, list<string>& common) {
    common.clear(); list1.clear(); list2.clear();
    
    // 3.c. Заполняем каждую половину списка уникальными строками
    for (int i = 0; i < N / 2; ++i) {
        common.push_back(getRandom(7));
        list1.push_back(getRandom(7));
        list2.push_back(getRandom(7));
    }
    
    // 3.d. Вставляем общие элементы в случайные позиции
    for (const auto& c : common) {
        int i = rand() % list1.size();
        for (auto it = list1.begin(); it != list1.end(); ++it, --i)
            if (i == 0) { list1.insert(it, c); break; }
            
        i = rand() % list2.size();
        for (auto it = list2.begin(); it != list2.end(); ++it, --i)
            if (i == 0) { list2.insert(it, c); break; }
    }
}

// 4. Подход "в лоб"
list<string> intersectNaive(const list<string>& l1, const list<string>& l2) {
    list<string> result;
    for (const auto& s1 : l1) {
        for (const auto& s2 : l2) {
            if (s1 == s2) {
                result.push_back(s1);
                break; // Одно совпадение достаточно
            }
        }
    }
    return result;
}

// 5-6. Продвинутый подход с предобработкой
// Обоснование: std::unordered_set хранит элементы в хеш-таблице.
// Поиск в среднем выполняется за O(1), что снижает общую сложность с O(N²) до O(N).
list<string> intersectAdvanced(const list<string>& l1, const list<string>& l2) {
    list<string> result;
    unordered_set<string> lookup(l2.begin(), l2.end()); // Предобработка
    
    for (const auto& s1 : l1) {
        if (lookup.count(s1)) {
            result.push_back(s1);
        }
    }
    return result;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    
    // 8. Изменяйте N для тестов: 10, 1000, 5000
    const int N = 5000; 
    list<string> list1, list2, common;
    prepareData(N, list1, list2, common);

    // 7. Измерение времени "в лоб"
    auto start = chrono::steady_clock::now();
    auto resNaive = intersectNaive(list1, list2);
    auto stop = chrono::steady_clock::now();
    auto dtNaive = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    // 7. Измерение времени "продвинутого"
    start = chrono::steady_clock::now();
    auto resAdv = intersectAdvanced(list1, list2);
    stop = chrono::steady_clock::now();
    auto dtAdv = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "N = " << N << "\n";
    cout << "Naive:     " << dtNaive << " us, elements: " << resNaive.size() << "\n";
    cout << "Advanced:  " << dtAdv  << " us, elements: " << resAdv.size() << "\n";
    
    return 0;
}