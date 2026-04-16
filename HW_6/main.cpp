#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "PH.h"

using namespace std;

// Функция для явного вычисления хеша (для верификации)
int explicit_hash(const char* s, int len, const PH& ph) {
    // Создаём временный объект PH с той же длиной, но это неэффективно.
    // В тестах мы просто используем ph.Hash(s).
    return ph.Hash(s);
}

// Тщательное тестирование класса PH
void testPH() {
    cout << "=== Testing PH class ===\n";
    const int MAX_LEN = 80;
    string base;
    // Генерируем случайную строку длиной MAX_LEN
    srand((unsigned)time(nullptr));
    for (int i = 0; i < MAX_LEN; ++i) {
        base.push_back(rand() % 256);  // случайный байт
    }

    bool all_ok = true;
    // Проверяем для всех длин от 1 до MAX_LEN-1
    for (int L = 1; L < MAX_LEN; ++L) {
        PH ph(L);
        // Вычисляем хеш для первого фрагмента
        int h = ph.Hash(base.c_str());
        // Проверяем все сдвиги
        for (int i = 0; i + L < MAX_LEN; ++i) {
            // Хеш для фрагмента, начинающегося с i
            int h_direct = ph.Hash(base.c_str() + i);
            // Хеш, полученный сдвигом из предыдущего
            int h_shift = (i == 0) ? h : ph.Shift(h_shift, base[i-1], base[i+L-1]);
            if (i == 0) {
                if (h != h_direct) {
                    cout << "Error at L=" << L << ", i=0: h=" << h << ", direct=" << h_direct << endl;
                    all_ok = false;
                }
                h_shift = h; // запомним для следующего шага
            } else {
                if (h_shift != h_direct) {
                    cout << "Error at L=" << L << ", i=" << i
                         << ": shift=" << h_shift << ", direct=" << h_direct << endl;
                    all_ok = false;
                }
            }
        }
    }
    if (all_ok)
        cout << "All tests passed successfully!\n";
    else
        cout << "Tests detected errors.\n";
}

// Поиск одного образца в тексте
vector<int> search(const string& text, const string& pattern) {
    vector<int> indices;
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) return indices;

    PH ph(m);
    int hash_pat = ph.Hash(pattern.c_str());
    int hash_win = ph.Hash(text.c_str());

    for (int i = 0; i <= n - m; ++i) {
        if (i > 0) {
            hash_win = ph.Shift(hash_win, text[i-1], text[i+m-1]);
        }
        if (hash_win == hash_pat) {
            // Проверка на коллизию (посимвольное сравнение)
            bool match = true;
            for (int j = 0; j < m; ++j) {
                if (text[i+j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                indices.push_back(i);
        }
    }
    return indices;
}

// Поиск нескольких образцов одинаковой длины
vector<int> searchMultiple(const string& text, const vector<string>& patterns) {
    if (patterns.empty()) return {};
    int m = patterns[0].length();
    for (const auto& p : patterns) {
        if ((int)p.length() != m) {
            throw invalid_argument("All patterns must have the same length");
        }
    }

    vector<int> indices;
    int n = text.length();
    if (m == 0 || m > n) return indices;

    PH ph(m);
    // Вычисляем хеши всех образцов
    vector<int> pattern_hashes;
    for (const auto& p : patterns) {
        pattern_hashes.push_back(ph.Hash(p.c_str()));
    }

    int hash_win = ph.Hash(text.c_str());
    for (int i = 0; i <= n - m; ++i) {
        if (i > 0) {
            hash_win = ph.Shift(hash_win, text[i-1], text[i+m-1]);
        }
        // Сравниваем с каждым хешем образца
        for (size_t idx = 0; idx < pattern_hashes.size(); ++idx) {
            if (hash_win == pattern_hashes[idx]) {
                // Проверка на коллизию
                bool match = true;
                for (int j = 0; j < m; ++j) {
                    if (text[i+j] != patterns[idx][j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    indices.push_back(i);
                    // Можно прервать, если не нужно искать все совпадения для всех образцов
                    // Но мы продолжаем, чтобы найти все вхождения всех образцов
                }
            }
        }
    }
    return indices;
}

int main() {
    cout << "=== Rabin-Karp Algorithm ===\n";

    // 1. Тестирование класса PH
    testPH();

    // 2. Поиск одного образца
    cout << "\n=== Single pattern search ===\n";
    string text = "ABRACADABRA";
    string pattern = "ABRA";
    vector<int> res = search(text, pattern);
    cout << "Text: " << text << "\nPattern: " << pattern << "\nFound at positions: ";
    for (int pos : res) cout << pos << " ";
    cout << endl;

    // 3. Поиск нескольких образцов одинаковой длины
    cout << "\n=== Multiple patterns search ===\n";
    vector<string> patterns = {"ABRA", "CADA", "BRAC"};
    vector<int> multi_res = searchMultiple(text, patterns);
    cout << "Text: " << text << "\nPatterns: ";
    for (const auto& p : patterns) cout << p << " ";
    cout << "\nFound occurrences (positions in text): ";
    for (int pos : multi_res) cout << pos << " ";
    cout << endl;

    // Дополнительный тест с длинным текстом
    cout << "\n=== Additional test ===\n";
    string long_text = "The quick brown fox jumps over the lazy dog";
    string short_pattern = "fox";
    auto found = search(long_text, short_pattern);
    cout << "Text: " << long_text << "\nPattern: " << short_pattern << "\nFound at position: ";
    for (int p : found) cout << p << " ";
    cout << endl;

    return 0;
}